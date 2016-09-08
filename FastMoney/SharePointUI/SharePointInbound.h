// SharePointInbound.h : Declaration of the CSharePointInbound

#ifndef __SharePointINBOUND_H_
#define __SharePointINBOUND_H_

#include "resource.h"       // main symbols
#include "publisher2000Server.h"
#include "SharePointCommon.h"
#include "ErrorsAndDebug.h"
#include "mtobject6.h"

static char* AUTH_MODE[] =
{
	{_T("Default")},
	{_T("FormsAuthentication")},
	{_T("Anonymous")}
};

static char* FUAG_AUTH[] =
{
	{_T("Active Directory")},
	{_T("Extranet Partners")},
};

class CSvrListener;
struct IPolyHelper;
/////////////////////////////////////////////////////////////////////////////
// CSharePointInbound
class ATL_NO_VTABLE CSharePointInbound : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSharePointInbound, &CLSID_SharePointInbound>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISharePointInbound, &IID_ISharePointInbound, &LIBID_SharePointUILib>,
	public IDispatchImpl<IInboundUI, &IID_IInboundUI, &LIBID_SharePointUILib>,
	public CErrorsAndDebug,
	public MTObject
{
public:
	CSharePointInbound();
	~CSharePointInbound();
	CComObject<CSvrListener> *m_pSvrlistener;
	WORD m_cookie;
	BOOL bServerRemote;
	bool VerifyName(LPCTSTR name,bool bAdd=false);
	
	ULONG GetPubRefnum();
	void DumpBase();
	bool GoodInboundServer();
	HRESULT DoCustomIF(int nType, LPVARIANT pvtFillThis);
	void ConfigureSharePoint();
	HRESULT PopulateLists(VARIANT& vtTitleList);
	HRESULT PopulateViews(CString& list, VARIANT& vtFieldList);
	HRESULT PopulateFields(CString& list, VARIANT& vtFieldList);
	HRESULT GetLastError(VARIANT& vtTitleList);
	void CaptureDebugMessages(BOOL bCapture);
	void ShowLastError(HRESULT hr);
	CSharePointCommon m_base;
//	TABLE_MAP m_colTables;
	FIELD_MAP m_colFlds;
	vector<string> m_listViews;

	IInboundSvr *GetInboundServer();
	void ReleaseInboundServer();
	void CatchInboundMsg(CException* ex);

	IInboundSvr *m_pInboundSvr;
	VARIANT inboundSession;

	IPSDBHelper *GetPSDBHelper();
	IPSDBHelper *m_pHelper;
	void ReleasePSDBHelper();

	HRESULT InitConfig(VARIANT config);	
	void CreateInboundConfigSafeArray(VARIANT *config);
	HRESULT UpdateSvrInboundConfig();
	bool m_bModConfig;

DECLARE_REGISTRY_RESOURCEID(IDR_SharePointINBOUND)
DECLARE_NOT_AGGREGATABLE(CSharePointInbound)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSharePointInbound)
	COM_INTERFACE_ENTRY(ISharePointInbound)
	COM_INTERFACE_ENTRY(IInboundUI)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IInboundUI
public:
	STDMETHOD(GetIconInfo)(/*[in,out]*/VARIANT *exename, /*[in,out]*/int *resourceID);
	STDMETHOD(DoProperties)(/*[in]*/unsigned long refnum);
	STDMETHOD(DoWizard)(/*[in,out]*/VARIANT *config);

// ISharePointInbound
public:

};

#endif //__SharePointINBOUND_H_
