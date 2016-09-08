// SharePointCollect.h : Declaration of the CSharePointCollect

#pragma once
#include "resource.h"       // main symbols
#include "aSyncro.h"
#include "SharePointCommon.h"

#include "EventMgr.h"
#include "mtobject6.h"
#include "publisher2000Server.h"
#include "SharePointCollector.h"
#include "PSDBSchema.h"


class CPSDBSchema;
class PSDBDatum;
class CUpdateBlob;

class CPSDBResponse;
#include "PSDBListener.h"
struct IPolyHelper;
#include "PSDBImplementIB.h"

#include "ErrorsAndDebug.h"

enum
{
	UNKNOWN_EVENT,
	SHAREPOINT_POLYFAILED,
	SHAREPOINT_POLYSUCCEEDED,
	SHAREPOINT_LOST_SVR_CONNECTION
};

// CSharePointCollect

class ATL_NO_VTABLE CSharePointCollect :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSharePointCollect, &CLSID_SharePointCollect>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISharePointCollect, &IID_ISharePointCollect, &LIBID_SharePointCollectorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IIBCollector, &IID_IIBCollector, &LIBID_SharePointCollectorLib>,
	public CErrorsAndDebug,
	public MTObject
{
public:
	CSharePointCollect();
	virtual ~CSharePointCollect();

DECLARE_REGISTRY_RESOURCEID(IDR_SHAREPOINTCOLLECT)
DECLARE_NOT_AGGREGATABLE(CSharePointCollect)

BEGIN_COM_MAP(CSharePointCollect)
	COM_INTERFACE_ENTRY(ISharePointCollect)
	COM_INTERFACE_ENTRY(IIBCollector)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(SetUpdatePulse)(int secs, BOOL onlyOnNoActivity);
	STDMETHOD(GetConfig)(/*[in,out]*/VARIANT *config);
	STDMETHOD(SetConfig)(/*[in]*/VARIANT *config, /*[in]*/BOOL ApplyNow);
	STDMETHOD(CustomIF)(/*[in]*/int type,/*[in,out]*/VARIANT *internalInfo);
	STDMETHOD(EnableConnection)(/*[in]*/BOOL open);
	STDMETHOD(RemoveListener)(/*[in]*/short cookie);
	STDMETHOD(AddListener)(/*[in]*/IInboundEvents *pListener, /*[in,out]*/short *cookie);
	STDMETHOD(SetInboundID)(/*[in]*/VARIANT info);
	STDMETHOD(SpecialImplement)(/*[in]*/specialImpType type,/*[in]*/ VARIANT info);
	STDMETHOD(SetImplemented)(/*[in]*/ VARIANT keys, /*[in]*/ VARIANT flds);
	STDMETHOD(GetAllKeys)(/*[out]*/ VARIANT *keys);

	IInboundEvents *m_pListener;
	CaSynchro m_synchConfig;
	ULONG GetPubRefnum();
	void PublishFields();

	CPSDBCollector m_schema;
	bool m_bTablesExist;

	VARIANT inboundSession;

	//TABLE_MAP m_colTables;
	CUpdateBlob *m_pDatum;
	FIELD_MAP m_colFields;

	void BuildSchema();

	CSharePointCommon m_base;
	ISharePointAdapter *m_pSharePoint;
	bool m_bErrorIssued;
	bool CreateSharePointInstance(); 
	HRESULT doConfig(/*[in]*/VARIANT *config); // for update and startup

	void DoEvent(changeType type, short state, VARIANT *err = NULL);

	CEventMgr m_EventMgr;

	HRESULT  AddEvent(int reqID, int type, int errCode, BSTR msg,VARIANT response);
	IPSDBHelper *GetPSDBHelper();
	MTObject  	m_SyncPSDBSvr;
	CInboundKeys m_keys;	// psdb
	IBInstImpIds m_impFlds;	// psdb
	IBInstImpIds m_impModFlds;	// psdb
	CInboundKeys updatekeys;
	CComObject<CPSDBListener>*m_pDBListener;
	bool m_bFirst;
	void ModifyImplemented();
	TYPE_MAP SPTYPETOPOLY;
	HANDLE m_hStartupDone;
private:
	CPSDBResponse *m_pResponse;
	IPSDBHelper *m_pHelper;
	void ReleasePSDBHelper();
	WORD cookie;

	void OnAddListener(); 
	void OnRemoveListener();
	void AddInboundInstanceInfo();

public:
	void CreateCollector();
	void DeleteTable(string &table);
	bool DeleteFolder(CString& szFolder);
	LPCTSTR GetErrorMessage(CString &err);
};

OBJECT_ENTRY_AUTO(__uuidof(SharePointCollect), CSharePointCollect)
