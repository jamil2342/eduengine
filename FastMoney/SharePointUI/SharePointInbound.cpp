// SharePointInbound.cpp : Implementation of CSharePointInbound
#include "stdafx.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"

/////////////////////////////////////////////////////////////////////////////
// CSharePointInbound

#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "DiagnosticDlg.h"
#include "streamhelper.h"

#define IID_DEFINED
#include "publisher2000server_i.c"

#define IID_DEFINED
#include "SharePointCollector_i.c"

#include "objectdefs.h"
#include "pubutility.h"
#include "SvrListener.h"

/////////////////////////////////////////////////////////////////////////////
// CSharePointInbound

STDMETHODIMP CSharePointInbound::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISharePointInbound
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSharePointInbound::GetIconInfo(/*[in,out]*/VARIANT *exename, /*[in,out]*/int *resourceID)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return S_OK;
}

STDMETHODIMP CSharePointInbound::DoProperties(/*[in]*/unsigned long refnum)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	{
		CWaitCursor curs;
		IInboundSvr *pSvr = GetInboundServer();
		ASSERT(pSvr);
		if(!pSvr)
			return S_FALSE;

		VARIANT blob; VariantInit(&blob);
			
		HRESULT hRes;
		try
		{
			hRes = pSvr->GetInboundConfig(inboundSession, refnum, &blob);
		}
		catch(CException* ex)
		{
			ASSERT(FALSE);
			CatchInboundMsg(ex);
			VariantClear(&blob);
			return S_FALSE;
		}

		InitConfig(blob);
		VariantClear(&blob);

		CPropertySheet sheet1("ShareView Collector Properties");
		CPage1 pg1(this);
		sheet1.AddPage(&pg1);
		CPage2 pg2(this);
		sheet1.AddPage(&pg2);
		CPage3 pg3(this);
		sheet1.AddPage(&pg3);
		CPage4 pg4(this);
		sheet1.AddPage(&pg4);
		CDiagnosticDlg dlgDiag(this);
		sheet1.AddPage(&dlgDiag);

		if (strlen(m_base.m_szListTitle) == 0)
			sheet1.SetActivePage(2);
		if (strlen(m_base.m_szServiceUrl) == 0)
			sheet1.SetActivePage(1);

		if (m_base.m_state == ACTIVE)
			AfxMessageBox("Settings to this collector may not be \nchanged while collector is Active.  Please \nDeactivate this collector to make changes.");

		m_base.m_prevFieldCount = m_base.m_fieldCount;
		m_base.m_prevKeyCount = m_base.m_keyCount;
		m_base.m_prevTableCount = m_base.m_tableCount; 
		strncpy_s(m_base.m_szPrevListTitle, _countof(m_base.m_szPrevListTitle), (LPCTSTR)m_base.m_szListTitle, STANDARD_STRING);

		CWinThread* pThread = AfxGetThread();
		if ( pThread != NULL )
		{
			if ( pThread->m_pMessageFilter == NULL )
			{
				pThread->m_pMessageFilter = new COleMessageFilter();
				AfxOleGetMessageFilter()->Register();
				pThread->m_pMessageFilter->SetMessagePendingDelay(120000UL);

			}
		}
		int ret = sheet1.DoModal();
		if ( pThread != NULL )
		{
			if ( pThread->m_pMessageFilter != NULL )
			{
				pThread->m_pMessageFilter->SetMessagePendingDelay(5000UL); // default
				delete pThread->m_pMessageFilter;
			}
			pThread->m_pMessageFilter = NULL;
		}
		if (ret != IDOK)
			return S_FALSE;

		UpdateSvrInboundConfig();
		if (m_base.m_tableCount != m_base.m_prevTableCount || m_base.m_fieldCount != m_base.m_prevFieldCount || stricmp(m_base.m_szListTitle, m_base.m_szPrevListTitle) != 0) 
		{
			VARIANT config;
			VariantInit(&config);
			hRes = pSvr->CustomInboundFunc(inboundSession,m_base.m_refnum,PUBLISH_FIELDS,&config);
			VariantClear(&config);
		}

	}
	return S_OK;
}

#include "Wizzard1.h"
#include "Wizzard2.h"

STDMETHODIMP CSharePointInbound::DoWizard(/*[in,out]*/VARIANT *config)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	VariantClear(config);

	m_base.m_refnum = 0;
	memcpy(&m_base.m_clsid,&CLSID_SharePointCollect,sizeof(CLSID));		// the data collectors clsid
	memcpy(&m_base.m_UIclsid,&CLSID_SharePointInbound,sizeof(CLSID));		// the inbound UI clsid
	m_base.m_state = INACTIVE;				

	m_base.m_update_interval = 60;	//sec
	m_base.m_update_timeout = 300;	//sec
	m_base.m_version = SHAREPOINT_VERSION;
	
	m_base.m_fieldCount = 0;
	m_base.m_keyCount = 0;
	m_base.m_tableCount = 0;

	m_base.m_prevFieldCount = 0;
	m_base.m_prevKeyCount = 0;
	m_base.m_prevTableCount = 0;

	CRegKey regKey;
	DWORD dwCount;
	long ret;
	ret = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Symon Communications\\Symon Portal\\System\\Collectors\\ShareView"), KEY_READ);
	if (ret == ERROR_SUCCESS)
	{	
		dwCount = _MAX_PATH;
		ret = regKey.QueryStringValue(_T("ImagePath"), m_base.m_szContentFolder, &dwCount);
		if ( ret != ERROR_SUCCESS )
		{
			regKey.Close();
			ret = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Symon Communications\\Symon Portal\\System"), KEY_READ);
			if ( ret == ERROR_SUCCESS )
			{
				dwCount = _MAX_PATH;
				ret = regKey.QueryStringValue(_T("DataPath"), m_base.m_szContentFolder, &dwCount);
				strcat_s(m_base.m_szContentFolder, _countof(m_base.m_szContentFolder), "..\\Symon\\SharePointImages\\");
			}
		}
	}
	regKey.Close();
	ret = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Symon Communications\\Symon Portal\\System\\Collectors\\ShareView"), KEY_READ);
	if (ret == ERROR_SUCCESS)
	{
		dwCount = _MAX_PATH;
		ret = regKey.QueryStringValue(_T("CertPath"), m_base.m_szCertPath, &dwCount);
	}
	regKey.Close();

	CPropertySheet sheet1;
	sheet1.SetWizardMode();

	CWizzard1 pg1(this);
	CWizzard2 pg2(this);

	sheet1.AddPage(&pg1);
	sheet1.AddPage(&pg2);

	int result = sheet1.DoModal();
	if(result != ID_WIZFINISH )
	{
		return S_FALSE;	// didn't complete add
	}

	CreateInboundConfigSafeArray(config);

	ASSERT(config->vt ==  (VT_UI1 | VT_ARRAY));

	// add this object to publisher2000Server so we can get it's refnum

	IInboundSvr *m_pInboundSvr = GetInboundServer();
	ASSERT(m_pInboundSvr);
	if(!m_pInboundSvr)
	{
		MessageBeep(MB_OK);
		return S_FALSE;
	}

	REFNUM inbound_ref = 0;
	try
	{
		m_pInboundSvr->AddInbound(inboundSession, *config, &inbound_ref);
	}
	catch(CException* ex)
	{
		ASSERT(FALSE);
		CatchInboundMsg(ex);
		VariantClear(config);
		return S_FALSE;
	}

	ASSERT(inbound_ref != 0);

	m_base.m_refnum = inbound_ref;

	VariantClear(config);

	if(inbound_ref)
	{
		config->vt = VT_UI4;
		config->ulVal = inbound_ref;
	}

	return S_OK;
}


IInboundSvr *CSharePointInbound::GetInboundServer()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pInboundSvr)
		return m_pInboundSvr;

	HRESULT hRes = CoCreateInstance(CLSID_InboundSvr, NULL, CLSCTX_SERVER, IID_IInboundSvr, (void**)&m_pInboundSvr);
	m_pInboundSvr->AddRef();

	if (FAILED(hRes)) 
	{
		CString csError;
		csError.Format(_T("Error %x EX!"), hRes);
		AfxMessageBox(csError);
		return NULL;
	}

	ASSERT(inboundSession.vt == VT_EMPTY);
	SessionInfo info;
	strcpy(info.m_user,"ShareView Inbound UI");
	SAFEARRAY *resultsArray	= CreateFlatArray(sizeof(SessionInfo),(unsigned char *)&info);
	inboundSession.vt =  VT_UI1 | VT_ARRAY;
	inboundSession.parray = resultsArray;

	m_pInboundSvr->OpenSession(&inboundSession);

	CComObject<CSvrListener>::CreateInstance(&m_pSvrlistener);
	m_pSvrlistener->AddRef();
	m_pInboundSvr->AddListener(m_pSvrlistener,0,&m_cookie);

	m_pSvrlistener->m_pCtrl = this;

	return m_pInboundSvr;
}

void CSharePointInbound::ReleaseInboundServer()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_pInboundSvr)
		return;

	if(m_cookie)
		m_pInboundSvr->RemoveListener(0,m_cookie);

	m_cookie = 0;
	if(	m_pSvrlistener)
		m_pSvrlistener->Release();

	m_pSvrlistener = NULL;

	m_pInboundSvr->CloseSession(inboundSession);
	VariantClear(&inboundSession);

	m_pInboundSvr->Release();
	m_pInboundSvr = NULL;

}


/////////////////////////////////////////

CSharePointInbound::CSharePointInbound()
{
	m_pSvrlistener = NULL;
	m_cookie = 0;

	ZeroMemory(&m_base,SIZEOF_SHAREPOINT_COMMON);

	strncpy(m_base.m_name,"ShareView Collector",STANDARD_STRING);

	memcpy(&m_base.m_clsid,&CLSID_SharePointCollect,sizeof(CLSID));		// the data collectors clsid
	memcpy(&m_base.m_UIclsid,&CLSID_SharePointInbound,sizeof(CLSID));		// the inbound UI clsid
	m_base.m_state = INACTIVE;	
	m_base.m_singleInstance = false;	// indicates there is only 1 instance of this
										// collector type ever so when the inbound is 
										// deleted, portal will delete all collector 
										// data in PSDB
	m_base.m_allKeysImplemented = true;
	m_pInboundSvr = NULL;
	VariantInit(&inboundSession);

	m_bModConfig = false;
	m_pHelper = NULL;
}

CSharePointInbound::~CSharePointInbound()
{
	ReleaseInboundServer();
	VariantClear(&inboundSession);
	FIELD_MAP_ITER iter = m_colFlds.begin();
	while ( iter != m_colFlds.end() )
	{
		delete (*iter).second;
		iter++;
	}
	m_colFlds.clear();

}

void CSharePointInbound::CatchInboundMsg(CException* ex)
{
	TCHAR    szCause[255];

	ex->GetErrorMessage(szCause, 255);
	CString msg;
//	msg.Format(IDS_IB_EXCEPTION,szCause);
	AfxMessageBox(msg,MB_ICONEXCLAMATION);
}

IPSDBHelper *CSharePointInbound::GetPSDBHelper()
{
	if(m_pHelper)
		return m_pHelper;


	HRESULT hRes = -1;

	try
	{
	hRes = CoCreateInstance(CLSID_PSDBHelper, NULL, CLSCTX_SERVER, IID_IPSDBHelper, (void**)&m_pHelper);
	}
	catch(...)
	{
	//	CatchServerMsg(ex);
		return NULL;
	}

	if (FAILED(hRes)) 
	{
		char csError[300] ;	ZeroMemory(csError,300);
		sprintf(csError,"CSharePointInbound::GetPSDBHelper() Error %x EX!\n", hRes);
		AtlTrace(csError);
		return NULL;
	}

	return m_pHelper;
}

void CSharePointInbound::ReleasePSDBHelper()
{
	if(m_pHelper == NULL)
		return;

	try
	{
		m_pHelper->Release();
	}
	catch(...)
	{
		_ASSERTE(false);
	}
	m_pHelper = NULL;
}

ULONG CSharePointInbound::GetPubRefnum()
{
	IPSDBHelper *helper = GetPSDBHelper();

	ULONG refnum = 0;

	if(helper != NULL)
	{
		try
		{
			helper->GetNewRefnum(&refnum);
		}
		catch(...)
		{
			_ASSERTE(false);
		//	theApp.CatchServerMsg(ex);
		//	return;
		}
	}

	return refnum;
}
HRESULT CSharePointInbound::InitConfig(VARIANT config)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CStreamHelper streamHelper;
	if (!streamHelper.GoodStream()) 
	{
		ATLASSERT(false);
		return S_FALSE;
	}

	int size = 0;
	int count = 0;

	GetSizeAndCount(config, &size, &count);
	
	if(size < SIZEOF_SHAREPOINT_COMMON)
	{
		_ASSERTE(false);
		return S_FALSE;
	}
	
	CSharePointCommon *info;

	SafeArrayAccessData(config.parray, (void**)&info);
	memcpy(&m_base,info,SIZEOF_SHAREPOINT_COMMON);
	SafeArrayUnaccessData(config.parray);
	if(size > SIZEOF_SHAREPOINT_COMMON)
	{
		unsigned char *ptr = NULL;
		SafeArrayAccessData(config.parray, (void**)&ptr);

		ptr += SIZEOF_SHAREPOINT_COMMON;

		HRESULT hRet = streamHelper.TransferData(ptr, size - SIZEOF_SHAREPOINT_COMMON, false);
		if (hRet != S_OK || !streamHelper.size())	// ALWAYS has a size!!
		{
			SafeArrayUnaccessData(config.parray);
			ATLASSERT(false);
			return S_FALSE;
		}
	}
	FIELD_MAP_ITER iter = m_colFlds.begin();
	while ( iter != m_colFlds.end() )
	{
		delete (*iter).second;
		iter++;
	}
	m_colFlds.clear();
	streamHelper.Rewind();
	if (streamHelper.size())
	{
		string fieldname;
		string fieldtype;
		for ( int i = 0; i < m_base.m_fieldCount; i++ )
		{
			streamHelper >> fieldname;
			streamHelper >> fieldtype;
			CField *pFld = new CField(fieldname.c_str(), fieldtype.c_str());
			m_colFlds[i] = pFld;
		}	
	}	
	SafeArrayUnaccessData(config.parray);
	streamHelper.Rewind();

	return S_OK;
}

void CSharePointInbound::CreateInboundConfigSafeArray(VARIANT *config)
{

	VariantClear(config);
	CStreamHelper streamHelper;
	if (!streamHelper.GoodStream())
	{
		ATLASSERT(false);
		return;
	}

	FIELD_MAP_ITER it = m_colFlds.begin();
	while(it != m_colFlds.end())
	{
		CField *pFld = (*it).second;
		streamHelper << pFld->m_fieldName;
		streamHelper << pFld->m_fieldType;
		it++;
	}

	int fld_size = streamHelper.size();
	int ttl_size = SIZEOF_SHAREPOINT_COMMON + fld_size;

	SAFEARRAY *resultsArray2 = CreateFlatArray(ttl_size, NULL);

	config->vt = VT_UI1 | VT_ARRAY;
	config->parray = resultsArray2;

	unsigned char *ptr;
	SafeArrayAccessData(resultsArray2, (void**)&ptr);

	ZeroMemory(ptr,ttl_size);
	memcpy(ptr,(unsigned char*)&m_base, SIZEOF_SHAREPOINT_COMMON);
	ptr += SIZEOF_SHAREPOINT_COMMON;

	streamHelper.Rewind();
	HRESULT hRet = streamHelper.TransferData((LPVOID)ptr, streamHelper.size());
	SafeArrayUnaccessData(resultsArray2);
	if (S_OK != hRet)
	{
		ATLASSERT(false);
	}

	SafeArrayUnaccessData(resultsArray2);
}

/*
HRESULT CSharePointInbound::InitConfig(VARIANT config)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = 0;
	int count = 0;

	GetSizeAndCount(config, &size, &count);
	
	if(size < SIZEOF_SHAREPOINT_COMMON)
	{
		_ASSERTE(false);
		return S_FALSE;
	}
	
	CSharePointCommon *info;

	SafeArrayAccessData(config.parray, (void**)&info);
	memcpy(&m_base,info,SIZEOF_SHAREPOINT_COMMON);
	SafeArrayUnaccessData(config.parray);

	SafeArrayUnaccessData(config.parray);

	return S_OK;
}

void CSharePointInbound::CreateInboundConfigSafeArray(VARIANT *config)
{

	VariantInit(config);

	int ttl_size = SIZEOF_SHAREPOINT_COMMON ;

	SAFEARRAY *resultsArray2 = CreateFlatArray(ttl_size, NULL);

	config->vt = VT_UI1 | VT_ARRAY;
	config->parray = resultsArray2;

	unsigned char *ptr;
	SafeArrayAccessData(resultsArray2, (void**)&ptr);

	ZeroMemory(ptr,ttl_size);
	memcpy(ptr,(unsigned char*)&m_base, SIZEOF_SHAREPOINT_COMMON);
	ptr += SIZEOF_SHAREPOINT_COMMON;

	SafeArrayUnaccessData(resultsArray2);
}
*/

HRESULT CSharePointInbound::UpdateSvrInboundConfig()
{

	HRESULT res = S_OK;

	IInboundSvr *pSvr = GetInboundServer();
	ASSERT(pSvr);
	if(pSvr == NULL)
	{
		AfxMessageBox("Connection error with server.",MB_ICONEXCLAMATION);
		return S_FALSE;
	}
	else
	{

		VARIANT config;
		VariantInit(&config);

		CreateInboundConfigSafeArray(&config);


		ASSERT(config.vt ==  (VT_UI1 | VT_ARRAY) );

		try
		{
			res = pSvr->SetInboundConfig(inboundSession,m_base.m_refnum,config,FALSE);
		}
		catch(CException* ex)
		{
			ASSERT(FALSE);
			CatchInboundMsg(ex);
		}

		if(res == S_OK)
		{
			m_bModConfig = FALSE;
		}

		VariantClear(&config);
	}


	return res;
}


// **************************************************************************
bool CSharePointInbound::GoodInboundServer()
	//
	//  Verify the InboundServer is created or create a new instance.  All
	//  Error checking and reporting for the server should be done in this
	//  one function.
	// **********************************************************************
	{
#ifdef _UI_WITH_MFC_
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

	if (!m_pInboundSvr)							//  Return the current Pointer
		{
		HRESULT hRet = CoCreateInstance(CLSID_InboundSvr, NULL, CLSCTX_SERVER,
										IID_IInboundSvr, (void**)&m_pInboundSvr);
		m_pInboundSvr->AddRef();

		if (FAILED(hRet)) 
			{
			ATLASSERT(hRet == S_OK);
			AtlTrace("Error %x:  Unable to create an instance of the Inbound object.\n", hRet);
			return false;
			}

		ATLASSERT(inboundSession.vt == VT_EMPTY);
		SessionInfo info;
		strcpy(info.m_user, "ShareView Inbound UI");
		SAFEARRAY *resultsArray	= CreateFlatArray(sizeof(SessionInfo), (PUCHAR)&info);
		inboundSession.vt =  VT_UI1 | VT_ARRAY;
		inboundSession.parray = resultsArray;

		m_pInboundSvr->OpenSession(&inboundSession);
		}
	if (m_pInboundSvr == NULL)
		{
		OutputDebugString("ERROR:  Unable to obtain or create a connection to server.");
		ATLASSERT(m_pInboundSvr != NULL);
		return false;
		}

	return true;
	}


bool CSharePointInbound::VerifyName(LPCTSTR name, bool bAdd)
{

	bool result = false;

	IInboundSvr *pSvr = GetInboundServer();
	ASSERT(pSvr);
	if(!pSvr)
		return result;

	VARIANT inboundinfo; VariantInit(&inboundinfo);
	InboundInfo info;
	strncpy(info.m_name,name,STANDARD_STRING);
	info.m_refnum = m_base.m_refnum;
	info.m_singleInstance = bAdd;

	inboundinfo.parray = CreateFlatArray(SIZEOF_INBOUNDINFO,(unsigned char *)&info);
	inboundinfo.vt =  VT_UI1 | VT_ARRAY;

	int isUnique = 0; 
	try
	{
		HRESULT hRes = pSvr->IsUniqueInboundName(inboundSession,  inboundinfo, &isUnique);
	}
	catch(CException* ex)
	{
		ASSERT(FALSE);
		CatchInboundMsg(ex);
		VariantClear(&inboundinfo);
		return result;
	}

	result = isUnique != 0;
	VariantClear(&inboundinfo);

	return result;
}

HRESULT CSharePointInbound::DoCustomIF(int nType, LPVARIANT pvtFillThis)
//
//  Call the collector via a custom function.  Set the bool in the 
//  Variant_Bool part.
// **********************************************************************
{
	HRESULT hRet = S_FALSE;

	if (!GoodInboundServer()) return hRet;
	try
	{
		hRet = m_pInboundSvr->CustomInboundFunc(inboundSession, 
									m_base.m_refnum, nType, pvtFillThis);
	}
	catch(CException* )
	{
			ASSERT(false);
			//		CatchTryMsg(ex);
	}

	return hRet;
}

void CSharePointInbound::ConfigureSharePoint()
{
	HRESULT hRet = S_OK;
	VARIANT vtProfileList;
	VariantInit(&vtProfileList);
	VARIANT vtData;
	VariantInit(&vtData);

	vtProfileList.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	psa = SafeArrayCreateVector( VT_VARIANT, 0, 21);
	LONG lCnt = 0;
	BSTR bsTemp;

	bsTemp = _bstr_t(m_base.m_szServiceUrl).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 0
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxy).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 1
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szUser).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 2
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szPassword).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 3
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szDomain).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 4
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szFuagAuth).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 5
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szAuthType).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 6
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szCertPath).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 7
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szViewTitle).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 8
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szContentFolder).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 9
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxyUser).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 10
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxyPassword).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 11
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxyDomain).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 12
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxyBypassList).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 13
	VariantClear(&vtData);
	lCnt++;

	bsTemp = _bstr_t(m_base.m_szProxyAuthType).copy();
	vtData.vt = VT_BSTR;
	vtData.bstrVal = bsTemp;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 14
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_authmode;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 15
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_ntlm;
	SafeArrayPutElement( psa, &lCnt, (void *)&vtData ); // 16
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_update_interval;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 17
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_bUseProxy;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 18
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_bBypassProxy;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 19
	VariantClear(&vtData);
	lCnt++;

	vtData.vt = VT_INT;
	vtData.intVal = m_base.m_update_timeout;
	SafeArrayPutElement(psa, &lCnt, (void *)&vtData); // 20
	VariantClear(&vtData);
	lCnt++;

	vtProfileList.parray = psa;
	CWaitCursor wait;
	try
	{
		hRet = DoCustomIF(CONFIGURE_SHAREPOINT, &vtProfileList);
	}
	catch (...)
	{
	}

	wait.Restore();
}

void CSharePointInbound::CaptureDebugMessages(BOOL bCapture)
{
	VARIANT vtBool;
	VariantInit(&vtBool);
	vtBool.vt = VT_BOOL;
	vtBool.boolVal = bCapture;
	
	HRESULT hRet = DoCustomIF(CaptureDebug, &vtBool);

	VariantClear(&vtBool);
}

HRESULT CSharePointInbound::PopulateLists(VARIANT& vtTitleList)
{
	VARIANT vtData;
	HRESULT hRet = S_OK;
	long idx = 0;
	VariantInit(&vtData);
	VariantInit(&vtTitleList);
	CWaitCursor wait;
	try
	{
		hRet = DoCustomIF(GET_LIST_TITLES, &vtTitleList);
	}
	catch (...)
	{
	}
	wait.Restore();
	return hRet;
}

HRESULT CSharePointInbound::PopulateViews(CString& list, VARIANT& vtFieldList)
{
	VARIANT vtData;
	HRESULT hRet = S_OK;
	long idx = 0;

	VariantInit(&vtData);
	VariantInit(&vtFieldList);
	vtFieldList.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	psa = SafeArrayCreateVector( VT_VARIANT, 0, 1 );
	vtData.vt = VT_BSTR;
	vtData.bstrVal = _bstr_t(list).copy();
	SafeArrayPutElement( psa, &idx, (void *)&vtData );
	VariantClear(&vtData);
	vtFieldList.parray = psa;
	CWaitCursor wait;
	try
	{
		hRet = DoCustomIF(GET_LIST_VIEWS, &vtFieldList);
	}
	catch (...)
	{
	}
	wait.Restore();

	return hRet;
}

HRESULT CSharePointInbound::PopulateFields(CString& list, VARIANT& vtFieldList)
{
	VARIANT vtData;
	HRESULT hRet = S_OK;
	long idx = 0;

	VariantInit(&vtData);
	VariantInit(&vtFieldList);
	vtFieldList.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	psa = SafeArrayCreateVector( VT_VARIANT, 0, 1 );
	vtData.vt = VT_BSTR;
	vtData.bstrVal = _bstr_t(list).copy();
	SafeArrayPutElement( psa, &idx, (void *)&vtData );
	VariantClear(&vtData);
	vtFieldList.parray = psa;
	CWaitCursor wait;
	try
	{
		hRet = DoCustomIF(GET_LIST_FIELDS, &vtFieldList);
	}
	catch (...)
	{
	}
	wait.Restore();

	return hRet;
}

HRESULT CSharePointInbound::GetLastError(VARIANT& vtData)
{
	HRESULT hRet = S_OK;
	long idx = 0;
	VariantClear(&vtData);
	try
	{
		hRet = DoCustomIF(GET_LAST_ERROR, &vtData);
	}
	catch (...)
	{
	}
	return hRet;
}

void CSharePointInbound::ShowLastError(HRESULT hr)
{
	if (hr != S_OK)
	{
		VARIANT vtError;
		VariantInit(&vtError);
		GetLastError(vtError);
		CString csErr;
		if (vtError.vt != VT_EMPTY)
		{
			csErr = _bstr_t(vtError.bstrVal, false).copy();
		}
		else
			csErr = "Unexpected Error. Failed to retrieve data from site.";
		AfxMessageBox(csErr);
		VariantClear(&vtError);
	}

}

void CSharePointInbound::DumpBase()
{
	CString msg;
	msg.Format("m_fieldCount = %d", m_base.m_fieldCount);
	OutputDebugString(msg);
	msg.Format("m_szListTitle =%s", m_base.m_szListTitle );
	OutputDebugString(msg);
	msg.Format("m_szViewTitle = %s", m_base.m_szViewTitle);
	OutputDebugString(msg);
	return;
}
