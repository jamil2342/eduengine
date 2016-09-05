#pragma onces
#include "EventMgr.h"
#include "mtobject6.h"
#include "publisher2000Server.h"
#include "SharePointCollector.h"
#include "PSDBSchema.h"
#include "PSDBListener.h"
#include <stdlib.h>
//#include "ErrorsAndDebug.h"
#include "SharePointCommon.h"
class FastMoneyCollect : public CComObjectRootEx<CComMultiThreadModel>,
	//#####do correct
	//public CComCoClass<FastMoneyCollect, &CLSID_FastMoneyCollect>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISharePointCollect, &IID_ISharePointCollect, &LIBID_SharePointCollectorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IIBCollector, &IID_IIBCollector, &LIBID_SharePointCollectorLib>,
	//public CErrorsAndDebug,
	public MTObject
{
	CPSDBResponse *m_pResponse;
	IPSDBHelper *m_pHelper;
	WORD cookie;
public:
	IInboundEvents *m_pListener;
	CaSynchro m_synchConfig;

	CPSDBCollector m_schema;
	bool m_bTablesExist;

	VARIANT inboundSession;

	//TABLE_MAP m_colTables;
	CUpdateBlob *m_pDatum;
	FIELD_MAP m_colFields;
	bool m_bErrorIssued;
	CEventMgr m_EventMgr;

	MTObject  	m_SyncPSDBSvr;
	CInboundKeys m_keys;	// psdb
	IBInstImpIds m_impFlds;	// psdb
	IBInstImpIds m_impModFlds;	// psdb
	CInboundKeys updatekeys;
	CComObject<CPSDBListener>*m_pDBListener;
	bool m_bFirst;
	TYPE_MAP SPTYPETOPOLY;
	HANDLE m_hStartupDone;
	FastMoneyCollect()
	{
	}


	// **************************************************************************
	void ShowMsgString(bool bErrorMsg, LPCSTR pszMsg)
		//
		//  Add some Status Information
		// **********************************************************************
	{
		string szMsg = pszMsg;
		OutputDebugString(szMsg.c_str());
	}


	// **************************************************************************
	void ShowMsgFmt(bool bErrorMsg, LPCSTR pszMsg)
		//
		//  Add some Status Information
		// **********************************************************************
	{
		string szMsg = pszMsg;
		OutputDebugString(szMsg.c_str());
	}

	void OnAddListener()
	{

		CComObject<CPSDBListener>::CreateInstance(&m_pDBListener);
		m_pDBListener->AddRef();
		//#####do correct
		//m_pDBListener->m_pMgr = this;

		IPSDBHelper *psvr = GetPSDBHelper();
		_ASSERTE(psvr);

		int cookie = 0;
		HRESULT hres = S_OK;

		try
		{
			hres = psvr->AddListener(m_pDBListener, &cookie);
			_ASSERTE(cookie);
			m_pDBListener->cookie = cookie;
		}
		catch (...)
		{
			_ASSERTE(false);
			return;

		}

		if (hres != S_OK)
		{
			AtlTrace("CSharePointCollect::OnAddListener() didn't set up listener properly !!!\n");
			m_pDBListener->Release();
			m_pDBListener = NULL;
		}

	}


	IPSDBHelper *GetPSDBHelper()
	{
		if (m_pHelper)
			return m_pHelper;


		HRESULT hRes = -1;

		try
		{
			hRes = CoCreateInstance(CLSID_PSDBHelper, NULL, CLSCTX_SERVER, IID_IPSDBHelper, (void**)&m_pHelper);
		}
		catch (...)
		{
			//	CatchServerMsg(ex);
			return NULL;
		}

		if (FAILED(hRes))
		{
			char csError[300];	ZeroMemory(csError, 300);
			sprintf(csError, "CSharePointCollect::GetPSDBHelper() Error %x EX!\n", hRes);
			AtlTrace(csError);
			return NULL;
		}

		if (m_pHelper)
			OnAddListener();

		return m_pHelper;
	}


};

