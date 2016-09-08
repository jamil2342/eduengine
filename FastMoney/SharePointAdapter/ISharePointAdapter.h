#pragma once

#include <string>
#include <list>
#include <Windows.h>
#include "SharePointEnums.h"
#include <comdef.h>

#ifdef MANAGEDWRAPPER_EXPORTS
#define DLLAPI  __declspec(dllexport)
#else
#define DLLAPI  __declspec(dllimport)
#pragma comment (lib, "SharePointAdapter.lib") // if importing, link also
#endif

class DLLAPI ISharePointAdapter
{
public:
	static ISharePointAdapter   *CreateInstance(void);
	static void  Destroy(ISharePointAdapter *instance);
	virtual int Disconnect() = 0;
	virtual void SetConfig(wchar_t* url, wchar_t* proxy, wchar_t* user, wchar_t* password, wchar_t* domain, wchar_t* authtype, enum ClientAuthenticationMode am, bool ntlm, int interval, int timeout) = 0;
	virtual void SetCertFile(wchar_t* certfile) = 0;
	virtual void SetFuagConfig(wchar_t* fuagAuth, wchar_t* userAgent) = 0;
	virtual void SetProxySettings(bool useproxy, bool bypassproxy, wchar_t* proxyuser, wchar_t* proxypassword, wchar_t* proxydomain, wchar_t* proxybypass, wchar_t* authtype) = 0;
	virtual	void SetViewTitle(wchar_t* viewTitle) = 0;
	virtual	void SetContentLocation(wchar_t* contentLoc) = 0;
	virtual	void SetDebug(bool bDebug) = 0;
	virtual bool MoreData() = 0;
	virtual void GetLastError(VARIANT *error) = 0;
	virtual void RetrieveLists(VARIANT *vValues, int &ret) = 0;
	virtual void RetrieveViews(wchar_t* listname, VARIANT *vValues, int &ret) = 0;
	virtual void RetrieveFields(wchar_t* listname, VARIANT *vValue, int &ret) = 0;
	virtual void RetrieveListItems(wchar_t* listname, VARIANT *vValues, int &ret) = 0;
	virtual void StripHTML(wchar_t* html, VARIANT *vValues) = 0;
	virtual void ExtractImagesFromHtml(wchar_t* html, VARIANT *vValues) = 0;
};
