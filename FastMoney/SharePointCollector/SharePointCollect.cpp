// SharePointCollect.cpp : Implementation of CSharePointCollect

#include "stdafx.h"
#include "SharePointCollector.h"
#include "SharePointCollect.h"
#include "streamhelper.h"

#define IID_DEFINED
#include "publisher2000server_i.c"

#include "PSDBDatum.h"
#include "updateblob.h"
#include "PSDBCommon.h"

#include "pubUtility.h"
#include "time.h"


STDMETHODIMP CSharePointCollect::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISharePointCollect
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
/////////////////////////////////////////////////////////////////////////////
//	Construction
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CSharePointCollect::GetConfig(/*[in,out]*/VARIANT *config)
{
	//m_synchConfig.ReadLock();
	VariantInit(config);

	CStreamHelper streamHelper;
	if (!streamHelper.GoodStream())
	{
		ATLASSERT(false);
		return S_FALSE;
	}
	
	FIELD_MAP_ITER iter = m_colFields.begin();
	while ( iter != m_colFields.end() )
	{
		CField* field = (*iter).second;
		if ( field )
		{
			streamHelper << field->m_fieldName;
			streamHelper << field->m_fieldType;
		}
		iter++;
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
	//m_synchConfig.ReadUnLock();
	return S_OK;
}

HRESULT CSharePointCollect::doConfig(/*[in]*/VARIANT *config)
{
	m_synchConfig.WriteLock();
	bool bChange = false;

	CStreamHelper streamHelper;
	if (!streamHelper.GoodStream()) 
	{
		ATLASSERT(false);
		return S_FALSE;
	}
	int size = 0;
	int count = 0;

	GetSizeAndCount(*config, &size, &count);
	
	CSharePointCommon *info;

	SafeArrayAccessData(config->parray, (void**)&info);

	// don't change the state based on the load
	InboundState curstate = m_base.m_state;

	memcpy(&m_base, info, SIZEOF_INBOUNDINFO);

	if (m_base.m_version > 1)
	{
		memcpy(&m_base, info, SIZEOF_SHAREPOINT_COMMON);
		SafeArrayUnaccessData(config->parray);
		if (size > SIZEOF_SHAREPOINT_COMMON)
		{
			unsigned char *ptr = NULL;
			SafeArrayAccessData(config->parray, (void**)&ptr);

			ptr += SIZEOF_SHAREPOINT_COMMON;

			HRESULT hRet = streamHelper.TransferData(ptr, size - SIZEOF_SHAREPOINT_COMMON, false);
			if (hRet != S_OK || !streamHelper.size())	// ALWAYS has a size!!
			{
				SafeArrayUnaccessData(config->parray);
				ATLASSERT(false);
				return S_FALSE;
			}
			SafeArrayUnaccessData(config->parray);
		}
	}
	else
	{
		CSharePointCommon_v1 tmpBase;
		memcpy(&tmpBase, info, SIZEOF_SHAREPOINT_COMMON_V1);
		SafeArrayUnaccessData(config->parray);
		memcpy(m_base.m_szServiceUrl, tmpBase.m_szServiceUrl, MAX_URL_SIZE);
		memcpy(m_base.m_szProxy, tmpBase.m_szProxy, MAX_URL_SIZE);
		memcpy(m_base.m_szCertPath, tmpBase.m_szCertPath, _MAX_PATH);
		memcpy(m_base.m_szContentFolder, tmpBase.m_szContentFolder, _MAX_PATH);
		memcpy(m_base.m_szUser, tmpBase.m_szUser, STANDARD_STRING);
		memcpy(m_base.m_szPassword, tmpBase.m_szPassword, STANDARD_STRING);
		memcpy(m_base.m_szDomain, tmpBase.m_szDomain, STANDARD_STRING);
		memcpy(m_base.m_szFuagAuth, tmpBase.m_szFuagAuth, STANDARD_STRING);
		memcpy(m_base.m_szAuthType, tmpBase.m_szAuthType, MAX_AGENT_SIZE);
		memcpy(m_base.m_szListTitle, tmpBase.m_szListTitle, STANDARD_STRING);
		memcpy(m_base.m_szPrevListTitle, tmpBase.m_szPrevListTitle, STANDARD_STRING);
		memcpy(m_base.m_szViewTitle, tmpBase.m_szViewTitle, STANDARD_STRING);
		memcpy(m_base.m_szCamlQuery, tmpBase.m_szCamlQuery, MAX_QUERY_SIZE);
		memset(m_base.m_szProxyUser, 0, STANDARD_STRING);
		memset(m_base.m_szProxyPassword, 0, STANDARD_STRING);
		memset(m_base.m_szProxyDomain, 0, STANDARD_STRING);
		memcpy(m_base.m_szProxyAuthType, "Basic", STANDARD_STRING);
		memset(m_base.m_szProxyBypassList, 0, MAX_BYPASS_SIZE);
		m_base.m_authmode = tmpBase.m_authmode;
		m_base.m_ntlm = tmpBase.m_ntlm;
		m_base.m_tableCount = tmpBase.m_tableCount;
		m_base.m_fieldCount = tmpBase.m_fieldCount;
		m_base.m_keyCount = tmpBase.m_keyCount;
		m_base.m_prevTableCount = tmpBase.m_prevTableCount;
		m_base.m_prevFieldCount = tmpBase.m_prevFieldCount;
		m_base.m_prevKeyCount = tmpBase.m_prevKeyCount;
		m_base.m_debugcollector = tmpBase.m_debugcollector;
		m_base.m_debugclient = tmpBase.m_debugclient;
		m_base.m_update_interval = tmpBase.m_update_interval;	//sec
		m_base.m_update_timeout = 300;	//sec
		m_base.m_version = SHAREPOINT_VERSION;
		m_base.m_bUseProxy = false;
		m_base.m_bBypassProxy = false;

		if (size > SIZEOF_SHAREPOINT_COMMON_V1)
		{
			unsigned char *ptr = NULL;
			SafeArrayAccessData(config->parray, (void**)&ptr);

			ptr += SIZEOF_SHAREPOINT_COMMON_V1;

			HRESULT hRet = streamHelper.TransferData(ptr, size - SIZEOF_SHAREPOINT_COMMON_V1, false);
			if (hRet != S_OK || !streamHelper.size())	// ALWAYS has a size!!
			{
				SafeArrayUnaccessData(config->parray);
				ATLASSERT(false);
				return S_FALSE;
			}
			SafeArrayUnaccessData(config->parray);
			bChange = true;
		}
	}

	m_base.m_singleInstance = false;
	m_base.m_allFldsImplemented = true;
	m_base.m_allKeysImplemented = true;

	bool bMod = false;
	if (m_base.m_state != curstate)
	{
		bMod = true;
		m_base.m_state = curstate;
	}

	if(curstate == ACTIVE)
	{
		time_t curtime;
		time( &curtime );
		m_base.m_refreshed = curtime;
	}

	FIELD_MAP_ITER iterS;
	CField* pField = NULL;

	iterS = m_colFields.begin();
	while (iterS != m_colFields.end())
	{
		pField = (*iterS).second;
		if (pField)								// In this for evaluation
			delete pField;
		iterS++;
	}

	m_colFields.clear();							//  Clear all now

	streamHelper.Rewind();
	if (streamHelper.size())
	{
		int size = m_base.m_fieldCount;
		CField* pField;
		string szName;
		string szType;;

		for (int nCnt = 0; nCnt < size; nCnt++)
		{
			streamHelper >> szName;
			streamHelper >> szType;

			//Here I want to fill my collection
			pField = new CField(szName.c_str(), szType.c_str());

			m_colFields[nCnt] = pField;
		}
		
	}

	if(bMod)
	{
		// recreate the variant to return to portal svc as something has changed beyond
		// what may have been sent in from the emul UI
		VariantClear(config);
		GetConfig(config);
	}

	if (bChange) 
		DoEvent(CT_InboundConfigChange, 0);

	m_synchConfig.WriteUnLock();
	return S_OK;
}

STDMETHODIMP CSharePointCollect::SetConfig(/*[in]*/VARIANT *config, /*[in]*/BOOL ApplyNow)
{
	string oldname = m_base.m_name;
	HRESULT result = doConfig(config);

	if(strcmp(oldname.c_str(),m_base.m_name) !=0 && oldname.length() != 0)
	{
		InboundInst inst;
		inst.m_ibRef = m_base.m_refnum;

		// set collectortype to 0 so it doesn't try to update the type displayname
		inst.m_typeID = 0;
		inst.m_name = m_base.m_name;

		VARIANT iinfo;	VariantInit(&iinfo);
		inst.VariantOut(&iinfo);
	
		Acquire lock(&m_SyncPSDBSvr);
		IPSDBHelper *psvr = GetPSDBHelper();
		_ASSERTE(psvr);
		HRESULT hres = S_OK;

		try
		{
			int reqid = 0;
			hres = psvr->ModifyInbound(&reqid,iinfo);

		}
		catch(...)
		{
			_ASSERTE(false);
		}
		VariantClear(&iinfo);
	}

	if (m_bFirst)
	{
		//m_EventMgr.AddEvent(T_GetImplementedForIB);
		BuildSchema();
		m_bFirst = false;
	}
	return S_OK;//result;
}


STDMETHODIMP CSharePointCollect::CustomIF(/*[in]*/int type,/*[in,out]*/VARIANT *internalInfo)
{
	HRESULT hResult = S_OK;
	int nres = 0;
	bool bTF;
	string url;
	_variant_t vtUrl;
	_variant_t vtData;
	long			lLowerBound = 0;
	long			lUpperBound = 0;
	long			lCounter	= 0;
	_bstr_t			bsData[100];
	int				lAuthMode;
	int				lNtlm;
	int				lInterval;
	int				lUseProxy;
	int				lBypassLocal;
	int				ltimeout;
	CStreamHelper streamHelper;
	DWORD dwMsgCnt = 0;

	switch(type)
	{
		case PUBLISH_FIELDS:
			PublishFields();
			break;
		case GET_LAST_ERROR:
			VariantClear(internalInfo);
			if ( CreateSharePointInstance() )
			{
				m_pSharePoint->GetLastError(internalInfo);
			}
			break;
		case CONFIGURE_SHAREPOINT:
			hResult = S_OK;
			SafeArrayGetLBound(V_ARRAY(internalInfo), 1, &lLowerBound);
			SafeArrayGetUBound(V_ARRAY(internalInfo), 1, &lUpperBound);

			for (lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
			{
				SafeArrayGetElement(V_ARRAY(internalInfo), &lCounter, &vtData);
				if(vtData.vt == VT_EMPTY) break;
				if ( lCounter < 15 )
				{
					bsData[lCounter] = V_BSTR(&vtData);
				}
				else if ( lCounter == 15 )
				{
					lAuthMode = V_INT(&vtData);
				}
				else if ( lCounter == 16 )
				{
					lNtlm = V_INT(&vtData);
				}
				else if (lCounter == 17)
				{
					lInterval = V_INT(&vtData);
				}
				else if (lCounter == 18)
				{
					lUseProxy = V_INT(&vtData);
				}
				else if (lCounter == 19)
				{
					lBypassLocal = V_INT(&vtData);
				}
				else if (lCounter == 20)
				{
					ltimeout = V_INT(&vtData);
			}
			}
			VariantClear(internalInfo);
			if ( CreateSharePointInstance() )
			{
				m_pSharePoint->SetConfig(bsData[0], bsData[1], bsData[2], bsData[3], bsData[4], bsData[6], (enum ClientAuthenticationMode)lAuthMode, lNtlm, lInterval, ltimeout);
				m_pSharePoint->SetFuagConfig(bsData[5],	L"");
				if ( bsData[7].length() > 0 )
					m_pSharePoint->SetCertFile(bsData[7]);
				m_pSharePoint->SetViewTitle(bsData[8]);
				if ( bsData[9].length() > 0 )
					m_pSharePoint->SetContentLocation(bsData[9]);
				m_pSharePoint->SetProxySettings(lUseProxy, lBypassLocal, bsData[10], bsData[11], bsData[12], bsData[13], bsData[14]);
			}
			break;
		case GET_LIST_TITLES:
			if ( m_base.m_state == ACTIVE )
				break;
			VariantClear(internalInfo);
			if ( CreateSharePointInstance() )
			{
				m_pSharePoint->RetrieveLists(internalInfo, nres);
				if ( nres )
					hResult = S_FALSE;
			}
			break;
		case GET_LIST_VIEWS:
			if ( m_base.m_state == ACTIVE )
				break;
			hResult = S_OK;
			SafeArrayGetLBound(V_ARRAY(internalInfo), 1, &lLowerBound);
			SafeArrayGetUBound(V_ARRAY(internalInfo), 1, &lUpperBound);
			for (lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
			{
				SafeArrayGetElement(V_ARRAY(internalInfo), &lCounter, &vtData);
				if(vtData.vt == VT_EMPTY) break;
				bsData[lCounter] = V_BSTR(&vtData);
			}			
			VariantClear(internalInfo);
			if ( CreateSharePointInstance() )
			{
				m_pSharePoint->RetrieveViews(bsData[0], internalInfo, nres);
				if ( nres )
					hResult = S_FALSE;
			}
			break;
		case GET_LIST_FIELDS:
			if ( m_base.m_state == ACTIVE )
				break;
			hResult = S_OK;
			SafeArrayGetLBound(V_ARRAY(internalInfo), 1, &lLowerBound);
			SafeArrayGetUBound(V_ARRAY(internalInfo), 1, &lUpperBound);
			for (lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
			{
				SafeArrayGetElement(V_ARRAY(internalInfo), &lCounter, &vtData);
				if(vtData.vt == VT_EMPTY) break;
				bsData[lCounter] = V_BSTR(&vtData);
			}
			VariantClear(internalInfo);
			if ( CreateSharePointInstance() )
			{
				m_pSharePoint->RetrieveFields(bsData[0], internalInfo, nres);
				if ( nres )
					hResult = S_FALSE;
			}
			break;
		case CaptureDebug:				//  Enable or disable debug
			if (internalInfo->vt == VT_BOOL)
				bTF = (internalInfo->boolVal == TRUE);

			m_bShowDebugMsgs = bTF;
			if ( m_pSharePoint )
				m_pSharePoint->SetDebug(bTF);
			break;
		case GetDebugMsgs:
			VariantClear(internalInfo);		// Reuqired on In/out
			dwMsgCnt = GetAllDebugMessages(streamHelper);
			if ( 0 < dwMsgCnt && streamHelper.size() > sizeof(DWORD) )
				streamHelper.Convert(internalInfo);
			break;
	}

	return hResult;
}


STDMETHODIMP CSharePointCollect::EnableConnection(/*[in]*/BOOL open)
{
//	MessageBox(NULL, "Stop in EnableConnection!!!", "Stop Here", MB_OK);

	try
	{
		if(m_base.m_state == TRANSITION)
		{
			return S_FALSE;
		}

		// check to see if we are already in that state

		if(	(open && m_base.m_state == ACTIVE ) ||
			(!open  && m_base.m_state == INACTIVE))
		{
			return S_OK;
		}


		DoEvent(CT_InboundStateChange,TRANSITION);
		if(open)
		{
			if ((m_base.m_tableCount > 0) && (m_base.m_fieldCount > 0))
			{
				//m_EventMgr.AddEvent(T_PublishFields);
				//m_EventMgr.AddEvent(T_GetImplementedForIB);
				m_EventMgr.AddEvent(T_StartData);
			}
			else
			{
				DoEvent(CT_InboundStateChange,INACTIVE);
				LogEvent(EVENTLOG_INFORMATION_TYPE,"No tables or fields exist. Collector will not activate.");
			}

			return S_FALSE;
		}
		else
		{
			m_EventMgr.AddEvent(T_StopData);
		}
	}
	catch(...)
	{
		if(open)
			DoEvent(CT_InboundStateChange,INACTIVE);
		else
			DoEvent(CT_InboundStateChange,ACTIVE);

		return S_FALSE;
	}

	return S_OK;
}


STDMETHODIMP CSharePointCollect::RemoveListener(/*[in]*/short cookie)
{
	ATLTRACE("CSharePointCollect::Unadvise \r\n");

	if(m_pListener)
		m_pListener->Release();
	m_pListener = NULL;

	InboundState curstate = m_base.m_state;
	if(curstate == ACTIVE)
	{
		m_EventMgr.m_pEventThread->StopData(); 
	}
//	ReleasePSDBHelper();

	return S_OK;
}

STDMETHODIMP CSharePointCollect::AddListener(/*[in]*/IInboundEvents *pListener, /*[in,out]*/short *cookie)
{
	ATLTRACE("CSharePointCollect::Advise\n");
	*cookie = 0;

	if(m_pListener)
	{
		_ASSERTE(FALSE);
		return S_FALSE;
	}

	//ATLTRACE("CTestCollect::Advise add lock\r\n");

	*cookie = 1;
	m_pListener = pListener;
	m_pListener->AddRef();

	return S_OK;
}


STDMETHODIMP CSharePointCollect::SetInboundID(/*[in]*/VARIANT infovar)
{
	// assign name and ref num. keep this avail for future use
	// when we get here, we know we were successful at creating this 
	// inbound collector


	HRESULT result = doConfig(&infovar);

//	MessageBox(NULL, "Stop in SetInboundId!!!", "Stop Here", MB_OK);
	m_base.m_collectorType = m_base.m_refnum;

	CreateCollector();
	DoEvent(CT_InboundAdd, 0, &infovar);
	return S_OK;//result;
}

void CSharePointCollect::CreateCollector()
{
	CPSDBCollector schema;

	//	code to add the refnum to the collectorTypeName
	string collectorTypeName;
	collectorTypeName = m_base.m_collectorTypeName;
	char buffer[20];
	ltoa(m_base.m_refnum,buffer,10);
	string refNum;
	refNum = buffer;
	collectorTypeName = collectorTypeName + refNum;
	strncpy(m_base.m_collectorTypeName, (LPCTSTR)collectorTypeName.c_str(), STANDARD_STRING);
//	End code to add the refnum to the collectorTypeName
	string cleanname = m_base.m_collectorTypeName;
	string displayname = "ShareView Collector - " + cleanname;

	schema.SetCollectorType(m_base.m_collectorType, m_base.m_collectorTypeName, displayname.c_str(), 1, ADHOC_DS);

	VARIANT typeInfo;		VariantInit(&typeInfo);
	schema.StreamOutCollectorSchema(&typeInfo);

	Acquire lock(&m_SyncPSDBSvr);
	IPSDBHelper *helper = GetPSDBHelper();

	int reqID = 0;

	try
	{
		helper->AddCollectorTables(&reqID, typeInfo, CTXT_TablesCollector);
	}
	catch(...)
	{
	}

	AddInboundInstanceInfo();
	VariantClear(&typeInfo);
}

void CSharePointCollect::DeleteTable(string &table)
{
	VARIANT info;	VariantInit(&info);
	if(table.length())
	{
		info.vt = VT_BSTR;
		info.bstrVal = NULL;
		int length = table.length();
		SysReAllocStringLen( &info.bstrVal, NULL, length);
		MultiByteToWideChar( CP_ACP, 0, table.c_str(),
			length, info.bstrVal, length );
	}

	Acquire lock(&m_SyncPSDBSvr);
	IPSDBHelper *helper = GetPSDBHelper();

	HRESULT hres;
	int reqID = 0;
	if(helper != NULL)
	{
		try
		{
			hres = helper->DeleteCollectorTable(&reqID, m_base.m_collectorType, info, true);
		}
		catch(...)
		{
			char szMsg[1000];
			sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::DeleteTable(%s) failed.\n"), (LPCSTR)_bstr_t(info.bstrVal));
			OutputDebugString(szMsg);
		}
	}
	else
	{
		//do_error();
	}

	VariantClear(&info);
}

ULONG CSharePointCollect::GetPubRefnum()
{
	Acquire lock(&m_SyncPSDBSvr);
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

STDMETHODIMP CSharePointCollect::SetUpdatePulse(int secs, BOOL onlyOnNoActivity)
{
	m_synchConfig.WriteLock();

	bool chg = false;
	if(m_base.m_pulse != secs)
	{
		m_base.m_pulse = secs;
		chg = true;
	}
	else if(m_base.m_onlyOnNoActivity != (onlyOnNoActivity!=0) )
	{
		m_base.m_onlyOnNoActivity = onlyOnNoActivity!=0;
		chg = true;
	}

	if(chg)
		DoEvent(CT_InboundConfigChange, 0);

	m_synchConfig.WriteUnLock();
	return S_OK;
}

#include <comdef.h>

void CSharePointCollect::DoEvent(changeType type, short state, VARIANT *err)
{
	Acquire lock(this);	

	if(type == CT_InboundStateChange)
	{
		m_base.m_state = (InboundState)state;
		m_base.m_refreshed = 0;
		AtlTrace("CSharePointCollect::DoEvent() CT_InboundStateChange state is %d\n",m_base.m_state);
	}

	HRESULT hRes = S_OK;

	if(m_pListener!=NULL)
	{
		VARIANT info;
		VariantInit(&info);
		bool bException = false;
		try
		{
			switch(type)
			{
				case CT_InboundStateChange:
				case CT_InboundPulse:
					info.vt = VT_I2;
					info.iVal = state;
					hRes = m_pListener->InboundChange( type, info);
					break;

				case CT_InboundAdd:
				case CT_InboundConfigChange:
				case CT_InboundKeysChanged:
					GetConfig(&info);
					hRes = m_pListener->InboundChange( type,info);
					break;

				case CT_InboundErrMsg:
					hRes = m_pListener->InboundChange( type,*err);
					break;
			}
		}
		catch(_com_error ce)
		{
			hRes = ce.Error();
			bException = true;
		}
		catch(...)
		{
			bException = true;
		}

		VariantClear(&info);

		// did the sink blow?
		if(bException)
		{
			try
			{
				// release this interface, it is broken.
				RemoveListener(0);
				_ASSERTE(false);
			}
			catch(...)
			{
			}
			m_pListener = NULL;
		}
	}
}

/////////////////////////////////////////////


CSharePointCollect::CSharePointCollect()
{
	ZeroMemory(&m_base,SIZEOF_SHAREPOINT_COMMON);

	int bsize = SIZEOF_SHAREPOINT_COMMON;
	m_hStartupDone = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pListener = NULL;
	m_EventMgr.Init(this);
	m_pDatum = NULL;

	VariantInit(&inboundSession);
	m_pHelper = NULL;
	m_pDBListener = NULL;
	m_bFirst = true;
	m_pSharePoint = NULL;
	m_bTablesExist = false;

	SPTYPETOPOLY[""] = POLY_STR;
	SPTYPETOPOLY["Integer"] = POLY_INT;
	SPTYPETOPOLY["Text"] = POLY_STR;
	SPTYPETOPOLY["Note"] = POLY_STR;
	SPTYPETOPOLY["DateTime"] = POLY_STR;
	SPTYPETOPOLY["Counter"] = POLY_INT;
	SPTYPETOPOLY["Choice"] = POLY_STR;
	SPTYPETOPOLY["Lookup"] = POLY_STR;
	SPTYPETOPOLY["Boolean"] = POLY_STR;
	SPTYPETOPOLY["Number"] = POLY_FLOAT;
	SPTYPETOPOLY["Currency"] = POLY_STR;
	SPTYPETOPOLY["URL"] = POLY_STR;
	SPTYPETOPOLY["Computed"] = POLY_STR;
	SPTYPETOPOLY["Threading"] = POLY_STR;
	SPTYPETOPOLY["Guid"] = POLY_STR;
	SPTYPETOPOLY["MultiChoice"] = POLY_STR;
	SPTYPETOPOLY["GridChoice"] = POLY_STR;
	SPTYPETOPOLY["Calculated"] = POLY_STR;
	SPTYPETOPOLY["File"] = POLY_STR;
	SPTYPETOPOLY["Attachments"] = POLY_STR;
	SPTYPETOPOLY["User"] = POLY_STR;
	SPTYPETOPOLY["Recurrence"] = POLY_STR;
	SPTYPETOPOLY["CrossProjectLink"] = POLY_STR;
	SPTYPETOPOLY["ModStat"] = POLY_STR;
	SPTYPETOPOLY["Error"] = POLY_STR;
	SPTYPETOPOLY["ContentTypeId"] = POLY_STR;
	SPTYPETOPOLY["PageSeparator"] = POLY_STR;
	SPTYPETOPOLY["ThreadIndex"] = POLY_STR;
	SPTYPETOPOLY["WorkflowStatus"] = POLY_STR;
	SPTYPETOPOLY["AllDayEvent"] = POLY_STR;
	SPTYPETOPOLY["WorkflowEventType"] = POLY_STR;
	SPTYPETOPOLY["Geolocation"] = POLY_STR;
	SPTYPETOPOLY["OutcomeChoice"] = POLY_STR;
	SPTYPETOPOLY["MaxItems"] = POLY_STR;
}

CSharePointCollect::~CSharePointCollect()
{
//	ClearMaps();
	m_keys.ReleaseAll();
	if ( m_pDatum )
		delete m_pDatum;
	m_pDatum = NULL;

	FIELD_MAP_ITER iterS;
	CField* pField = NULL;
		
	iterS = m_colFields.begin();
	while (iterS != m_colFields.end())
	{
		pField = (*iterS).second;
		if (pField)								// In this for evaluation
			delete pField;
		iterS++;
	}
	m_colFields.clear();							//  Clear all now

	if(m_pListener)
		m_pListener->Release();
	m_pListener = NULL;
	if ( m_pSharePoint )
	{
		ISharePointAdapter::Destroy(m_pSharePoint);
		m_pSharePoint = NULL;
	}
	if (m_hStartupDone )
		CloseHandle(m_hStartupDone);
}


HRESULT  CSharePointCollect::AddEvent(int reqID, int type, int errCode, BSTR msg,VARIANT response)
{
	Acquire lock(this);	

	_ASSERTE(response.vt == VT_BSTR || response.vt == VT_EMPTY);

	return S_OK;		
}

void CSharePointCollect::AddInboundInstanceInfo()
{
	_bstr_t bsName = m_base.m_name;
	string name = bsName;

	VARIANT instInfo;		VariantInit(&instInfo);
	VARIANT moreInfo;		VariantInit(&moreInfo);
	
	m_impFlds.m_ibRef = m_base.m_refnum;
	m_impFlds.m_typeID = m_base.m_collectorType;
	
	m_impFlds.m_name = name.c_str();
	m_impFlds.m_desc = name.c_str();

	m_impFlds.StreamUpdatesOut(&instInfo);

	Acquire lock(&m_SyncPSDBSvr);
	IPSDBHelper *helper = GetPSDBHelper();

	HRESULT hres;
	int reqID = 0;
	try
	{
		hres = helper->AddInbound2DB(&reqID, instInfo, (implementType)implement_none, &moreInfo);
	}
	catch(...)
	{
	}
	VariantClear(&instInfo);
	VariantClear(&moreInfo);
	m_bFirst = false;
	SetEvent(m_hStartupDone);
}

bool CSharePointCollect::CreateSharePointInstance()
{
	HRESULT hr = S_OK;

	if ( m_pSharePoint == NULL )
	{
		ShowMsgFmt(false, "ISharePointAdapter::CreateInstance()\n");
		m_pSharePoint = ISharePointAdapter::CreateInstance();
	}

	if ( m_pSharePoint == NULL )
	{
		if ( !m_bErrorIssued )
		{
			ShowMsgFmt(true, "Failed to load ISharePointAdapter - error %x\n", hr );
			//LogEvent(EVENTLOG_ERROR_TYPE, "Failed to load ISharePointAdapter - error %x", hr );
		}
		m_pSharePoint = NULL;
		m_bErrorIssued = true;
		return false;
	}
	else
		m_bErrorIssued = false;

	return true;
}

void CSharePointCollect::PublishFields()
{
	int cnt = 1;
	string strTableName;
	string strPrevTableName;
	string strNumber;
	string strFieldName;
	
	m_base.m_prevKeyCount = 0;
	char buf[1000];
	char szMsg[1000];
	if (strlen(m_base.m_szListTitle) > 0)
	{
		strcpy_s(buf, _countof(buf), m_base.m_szListTitle);
		strTableName = StripBadChars(buf, false);
		sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - m_szListTitle = %s\n"), strTableName.c_str());
		OutputDebugString(szMsg);
	}
	if (strlen(m_base.m_szPrevListTitle) > 0)
	{
		strcpy_s(buf, _countof(buf), m_base.m_szPrevListTitle);
		strTableName = StripBadChars(buf, false);
		sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - m_szPrevListTitle = %s\n"), strTableName.c_str());
		OutputDebugString(szMsg);
	}

	sprintf_s(szMsg,_countof(szMsg), _T("CSharePointCollect::PublishFields() - m_base.m_prevTableCount = %d\n"), m_base.m_prevTableCount);
	OutputDebugString(szMsg);

	if ( m_bTablesExist)
	{
		CTableKeys *pTblKeys = NULL;
		CKeyStuff *pKeyStuff;
		ImpKeyMapIter mapIter;

		m_bTablesExist = false;
		pTblKeys = m_keys.GetTable(cnt);
		if ( pTblKeys )
		{
			mapIter = pTblKeys->m_impKeys.begin();
			while ( mapIter != pTblKeys->m_impKeys.end() )
			{
				pKeyStuff = mapIter->second;
				sprintf_s(buf, _countof(buf), _T("CSharePointCollect::PublishFields() - Removing expired key %s\n"), (LPCSTR)mapIter->second->keyval);
				OutputDebugString(buf);
				if (m_pDatum)
					m_pDatum->RemoveRec(mapIter->second->keyval);
				mapIter = pTblKeys->m_impKeys.erase(mapIter);
			}
			VARIANT impl2;		VariantInit(&impl2);
			VARIANT info;		VariantInit(&info);

			if (m_pDatum)
				m_pDatum->VariantOut(&impl2);
			Acquire lock(this);
			IPSDBHelper *helper = GetPSDBHelper();
			HRESULT hres;
			int reqID = 0;

			if (helper != NULL)
			{
				try
				{
					// new blob data
					hres = helper->UpdateDataTblBlob(impl2);	//verify
					if (m_pDatum)
						m_pDatum->ResetBlobs();

				}
				catch (_com_error ex)
				{
					sprintf_s(buf, _countof(buf), "CSharePointCollect::PublishFields() failed to update blob. Error %s", ex.ErrorMessage());
					OutputDebugString(buf);
				}
			}

			VariantClear(&info);
			VariantClear(&impl2);
		}
		Sleep(1000);
		DeleteTable(strTableName);
		Sleep(500);
		sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - DeleteTable(%s)\n"), strTableName.c_str());
		OutputDebugString(szMsg);
		m_schema.m_tables.DeleteTable(cnt);
		m_keys.DeleteTable(cnt);
		m_base.m_prevTableCount = 0;
		m_base.m_prevKeyCount = 0;
		m_base.m_szPrevListTitle[0] = 0;
		DoEvent(CT_InboundConfigChange, 0);
	}
	sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - m_base.m_tableCount = %d, m_base.m_fieldCount = %d\n"), m_base.m_tableCount, m_base.m_fieldCount);
	OutputDebugString(szMsg);
	if ((m_base.m_tableCount > 0) && (m_base.m_fieldCount > 0) && strlen(m_base.m_szListTitle) > 0 )
	{
		string cleanname = m_base.m_collectorTypeName;
		string displayname = _T("ShareView Collector - ") + cleanname;

		m_impModFlds.m_ibRef  = m_base.m_refnum;
		m_impModFlds.m_typeID = m_base.m_collectorType;
		m_impModFlds.m_name   = cleanname.c_str();
		m_impModFlds.m_desc   = cleanname.c_str();
	
		sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - ClearRecs()\n"));
		OutputDebugString(szMsg);

		m_schema.m_tables.ClearRecs();
		
		m_schema.SetCollectorType(m_base.m_collectorType, cleanname.c_str(), displayname.c_str(), 1, ADHOC_DS);
		for (cnt = 1; cnt <= m_base.m_tableCount; cnt++)
		{
			strcpy_s(buf,_countof(buf), m_base.m_szListTitle);
			strTableName = StripBadChars(buf, false);
			//TABLE_MAP_ITER iter = m_colTables.begin();
			m_schema.InsertTable(cnt, m_base.m_collectorType, strTableName.c_str(), strTableName.c_str(), cnt)	;
			m_schema.InsertFld( 1/*fldID*/, cnt/*tableID*/, 1/*col*/, 
							_T("userkey")/*name*/, _T("userkey")/*desc*/,
							'Y'/*key*/, 'Y'/*indexed*/,
							POLY_STR/*dataType*/, 1/*internal*/);

			m_impModFlds.SetField(cnt, 1, IMPLEMENT_ALL);
			FIELD_MAP_ITER iter = m_colFields.begin();
			int cnt2 = 2;
			while ( iter != m_colFields.end() )
			{
				CField* pFld = (*iter).second;
				int dataType = SPTYPETOPOLY[pFld->m_fieldType] == POLY_UNKNOWN ? POLY_STR: SPTYPETOPOLY[pFld->m_fieldType];
				m_schema.InsertFld( cnt2/*fldID*/, cnt/*tableID*/, cnt2/*col*/, 
					pFld->m_fieldName.c_str()/*name*/, pFld->m_fieldName.c_str()/*desc*/,
					'N'/*key*/, 'N'/*indexed*/,
					 dataType/*dataType*/, cnt2/*internal*/);

				sprintf_s(szMsg, _countof(szMsg), "CSharePointCollect::PublishFields() - %s, %d\n", pFld->m_fieldName.c_str(), dataType);
				OutputDebugString(szMsg);
				iter++;
				cnt2++;
			}
			if ( m_pDatum )
			{
				delete m_pDatum;
				m_pDatum = NULL;
			}
			CollectorTable *pCTbl = m_schema.m_tables.GetTable(cnt);
			_ASSERTE(pCTbl);

			strcpy_s(buf,_countof(buf), m_base.m_szListTitle);
			strTableName = StripBadChars(buf, false);
			sprintf_s(buf, _countof(buf), "%s_%s", m_base.m_collectorTypeName, strTableName.c_str());
			OutputDebugString(buf);
			OutputDebugString("\n");
			m_pDatum = new CUpdateBlob;
			m_pDatum->SetTypeFromTable(pCTbl,buf,m_base.m_refnum,10,true);
			m_bTablesExist = true;
		}
		VARIANT info;		VariantInit(&info);
		m_schema.StreamOutCollectorSchema(&info);
						
		IPSDBHelper *helper = GetPSDBHelper();
						
		int reqID = 0;
		HRESULT hres;
		try
		{
			hres = helper->AddCollectorTables(&reqID, info, CTXT_TablesOnly);
			sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - AddCollectorTables hRes = %d\n"), hres);
			OutputDebugString(szMsg);
			_ASSERTE(m_pDBListener);
			ModifyImplemented();
		}
		catch (...)
		{
			sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::PublishFields() - AddCollectorTables Exception hRes = %d\n"), hres);
			OutputDebugString(szMsg);
		}

		VariantClear(&info);
	}
}

void CSharePointCollect::ModifyImplemented()
{
	_bstr_t bsName = m_base.m_name;
	string name = bsName;
	char szMsg[1000];
	VARIANT instInfo;		VariantInit(&instInfo);
	
	m_impModFlds.StreamUpdatesOut(&instInfo);
	
	Acquire lock(&m_SyncPSDBSvr);
	IPSDBHelper *helper = GetPSDBHelper();

	HRESULT hres;
	int reqID = 0;
	try
	{
		hres = helper->ModifyImplemented(&reqID, instInfo, ITXT_UpdateImplementedTablesI);
		sprintf_s(szMsg, _countof(szMsg), _T("CSharePointCollect::ModifyImplemented() - hRes = %d\n"), hres);
		OutputDebugString(szMsg);
	}
	catch(...)
	{
	}
	VariantClear(&instInfo);
	m_impModFlds.ReleaseMap();
}

IPSDBHelper *CSharePointCollect::GetPSDBHelper()
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
		sprintf(csError,"CSharePointCollect::GetPSDBHelper() Error %x EX!\n", hRes);
		AtlTrace(csError);
		return NULL;
	}

	if(m_pHelper)
		OnAddListener();

	return m_pHelper;
}


void CSharePointCollect::ReleasePSDBHelper()
{
	if(m_pHelper == NULL)
		return;

	Acquire lock(&m_SyncPSDBSvr);	// don't release it while in use!!!

	OnRemoveListener();

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

void CSharePointCollect::OnAddListener() 
{

	CComObject<CPSDBListener>::CreateInstance(&m_pDBListener);
	m_pDBListener->AddRef();
	m_pDBListener->m_pMgr = this;

	IPSDBHelper *psvr = GetPSDBHelper();
	_ASSERTE(psvr);

	int cookie=0;
	HRESULT hres = S_OK;

	try
	{
		hres = psvr->AddListener(m_pDBListener,&cookie);
		_ASSERTE(cookie);
		m_pDBListener->cookie = cookie;
	}
	catch(...)
	{
		_ASSERTE(false);
		return ;

	}

	if(hres != S_OK)
	{
		AtlTrace("CSharePointCollect::OnAddListener() didn't set up listener properly !!!\n");
		m_pDBListener->Release();
		m_pDBListener = NULL;
	}

}

void CSharePointCollect::OnRemoveListener() 
{
	if(m_pDBListener)	
	{
		IPSDBHelper *psvr = GetPSDBHelper();
		_ASSERTE(psvr);
		HRESULT hres = S_OK;

		try
		{
			hres = psvr->RemoveListener(m_pDBListener->cookie);
			delete m_pListener;
		}
		catch(...)
		{
			_ASSERTE(false);
			return ;
		}
	}
	else
		::MessageBeep(MB_OK);

	m_pDBListener = NULL;
	
}

STDMETHODIMP CSharePointCollect::GetAllKeys(VARIANT *keys)
{
	m_keys.m_ibRef = m_base.m_refnum;
	m_keys.VariantOut(keys, false);
	return S_OK;
}

STDMETHODIMP CSharePointCollect::SetImplemented(VARIANT keys, VARIANT flds)
{
	updatekeys.ReleaseAll();
	if (keys.vt != VT_EMPTY)
	{
		updatekeys.VariantIn(&keys);
	}
	return S_OK;
}

STDMETHODIMP CSharePointCollect::SpecialImplement(specialImpType type, VARIANT info)
{
	CString folder;
	switch (type)
	{
	case SIT_PSDBHelperAvail:
		char tmp[1000];
		char msg[1000];
		strcpy_s(tmp, _countof(tmp), m_base.m_szListTitle);
		string strTableName = m_base.m_collectorTypeName;
		strTableName += _T("_");
		strTableName += StripBadChars(tmp, false);
		sprintf_s(msg, _countof(msg), _T("CSharePointCollect::SpecialImplement():%s\n"), strTableName.c_str());
		OutputDebugString(msg);

		Acquire lock(&m_SyncPSDBSvr);
		IPSDBHelper *helper = GetPSDBHelper();
		try
		{
			helper->DeleteAllRecords(m_base.m_refnum, m_base.m_collectorType, _bstr_t(strTableName.c_str()));
			folder = m_base.m_szContentFolder;
			DeleteFolder(folder);
		}
		catch (...)
		{
		}
		m_EventMgr.AddEvent(T_GetImplementedForIB);
		break;
	}
	return S_OK;
}

bool CSharePointCollect::DeleteFolder(CString& szFolder)
{
	WIN32_FIND_DATA wfd;
	ZeroMemory(&wfd, sizeof(WIN32_FIND_DATA));
	CString err;
	CString szFilter(szFolder);
	szFilter += "\\*.*";
	HANDLE hFind = FindFirstFile(szFilter, &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return true;
	else
	{
		do
		{
			CString szFile(wfd.cFileName);
			if (szFile.Compare(_T(".")) != 0 && szFile.Compare(_T("..")) != 0)
			{
				CString szPath;
				szPath.Format(_T("%s\\%s"), szFolder, wfd.cFileName);
				CString szMsg;
				szMsg.Format(_T("Deleting file '%s\\%s' on startup."), szFolder, wfd.cFileName);
				OutputDebugString(szMsg);
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (!DeleteFolder(szPath))
					{
						FindClose(hFind);
						return false;
					}
				}
				else if (!DeleteFile(szPath))
				{
					CString sz;
					DWORD dwError = GetLastError();
					if (GetErrorMessage(err))
						sz.Format(_T("Failed to delete file \"%s\". Error %u: \"%s\""), szPath, dwError, err);
					else
						sz.Format(_T("Failed to delete file \"%s\". Error %u"), szPath, dwError);

					LogEvent(EVENTLOG_WARNING_TYPE, (LPSTR)(LPCSTR)sz);
					FindClose(hFind);
					return false;
				}
			}
		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}

	if (!RemoveDirectory(szFolder))
	{
		CString sz;
		CString err;
		DWORD dwError = GetLastError();
		if (GetErrorMessage(err))
			sz.Format(_T("Failed to delete folder \"%s\". Error %u: \"%s\""), szFolder, dwError, err);
		else
			sz.Format(_T("Failed to delete folder \"%s\". Error %u"), szFolder, dwError);

		LogEvent(EVENTLOG_WARNING_TYPE, (LPSTR)(LPCSTR)sz);
		return false;
	}


	return true;
}

LPCTSTR CSharePointCollect::GetErrorMessage(CString &err)
{
	DWORD dwError = GetLastError();
	if (dwError)
	{
		LPVOID lpMsgBuf = NULL;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dwError,
			0, // Default language
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);

		if (lpMsgBuf)
		{
			err = (LPTSTR)lpMsgBuf;

			// Free the buffer.
			LocalFree(lpMsgBuf);
			return err;
		}
	}

	IErrorInfo* pErrorInfo = NULL;
	GetErrorInfo(0, &pErrorInfo);
	BSTR desc = NULL;
	if (pErrorInfo)
		pErrorInfo->GetDescription(&desc);
	if (desc)
	{
		_bstr_t bstrError(desc, false);
		err = (LPCTSTR)bstrError;
	}

	if (pErrorInfo)
		pErrorInfo->Release();

	return err;
}

void CSharePointCollect::BuildSchema()
{
	int cnt; 
	string strTableName;
	string strNumber;
	string strFieldName;

	if ((m_base.m_tableCount > 0) && (m_base.m_fieldCount > 0) && strlen(m_base.m_szListTitle) > 0)
	{
		char buf[1000];
		m_bTablesExist = true;
		string cleanname = m_base.m_collectorTypeName;
		string displayname = "ShareView Collector - " + cleanname;

		m_schema.m_tables.ClearRecs();
		m_schema.SetCollectorType(m_base.m_collectorType, cleanname.c_str(), displayname.c_str(), 1, ADHOC_DS);
		for (cnt = 1; cnt <= m_base.m_tableCount; cnt++)
		{
			char buf[1000];
			strcpy_s(buf,_countof(buf), m_base.m_szListTitle);
			strTableName = StripBadChars(buf, false);
			m_schema.InsertTable(cnt, m_base.m_collectorType, strTableName.c_str(), strTableName.c_str(), cnt);  	

			m_schema.InsertFld( 1/*fldID*/, cnt/*tableID*/, 1/*col*/, 
							_T("userkey")/*name*/, _T("userkey")/*desc*/,
							'Y'/*key*/, 'Y'/*indexed*/,
							POLY_STR/*dataType*/, 1/*internal*/);
			
			FIELD_MAP_ITER iter = m_colFields.begin();
			int cnt2 = 2;
			while ( iter != m_colFields.end() )
			{
				CField* pFld = (*iter).second;
				int dataType = SPTYPETOPOLY[pFld->m_fieldType] == POLY_UNKNOWN ? POLY_STR: SPTYPETOPOLY[pFld->m_fieldType];
				m_schema.InsertFld( cnt2/*fldID*/, cnt/*tableID*/, cnt2/*col*/, 
								pFld->m_fieldName.c_str()/*name*/, pFld->m_fieldName.c_str()/*desc*/,
								'N'/*key*/, 'N'/*indexed*/,
								dataType/*dataType*/, cnt2/*internal*/);
				iter++;
				cnt2++;
			}
			if (m_pDatum)
			{
				delete m_pDatum;
				m_pDatum = NULL;
			}
			CollectorTable *pCTbl = m_schema.m_tables.GetTable(cnt);
			_ASSERTE(pCTbl);

			strcpy_s(buf, _countof(buf), m_base.m_szListTitle);
			strTableName = StripBadChars(buf, false);
			sprintf_s(buf, _countof(buf), "%s_%s", m_base.m_collectorTypeName, strTableName.c_str());
			m_pDatum = new CUpdateBlob;
			m_pDatum->SetTypeFromTable(pCTbl, buf, m_base.m_refnum, 10, true);
			m_bTablesExist = true;
		}
	}
}

void LogEvent(int logType,LPCSTR pFormat, ...)
{
	// EVENTLOG_SUCCESS                0x0000
	// EVENTLOG_ERROR_TYPE             0x0001
	// EVENTLOG_WARNING_TYPE           0x0002
	// EVENTLOG_INFORMATION_TYPE       0x0004

    TCHAR    chMsg[8192];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1]; 
    va_list pArg;

    va_start(pArg, pFormat);
	for (int i = 0; pArg[i] != 0; i++)
	{
		if (pArg[i] == '%')
			pArg[i] = '?';
	}
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    /* Get a handle to use with ReportEvent(). */
    hEventSource = RegisterEventSource(NULL, MY_DESC);
    if (hEventSource != NULL)
    {
        /* Write to event log. */
        ReportEvent(hEventSource, logType, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
        DeregisterEventSource(hEventSource);
    }
}
