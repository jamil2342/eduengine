// dllmain.h : Declaration of module class.

class CSharePointCollectorModule : public ATL::CAtlDllModuleT< CSharePointCollectorModule >
{
public :
	DECLARE_LIBID(LIBID_SharePointCollectorLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SHAREPOINTCOLLECTOR, "{BDB96B47-54C6-490A-99B8-971D50CE43AC}")
};

extern class CSharePointCollectorModule _AtlModule;
