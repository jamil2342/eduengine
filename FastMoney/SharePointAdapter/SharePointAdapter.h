#pragma once
#include <vcclr.h>
#include "ISharePointAdapter.h"
#include <list>

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace SharePointClient;

void MarshalString ( String ^ s, std::string& os );
void MarshalString ( String ^ s, std::wstring& os ) ;

public class DLLAPI CSharePointAdapter : ISharePointAdapter
{
private:
	gcroot<CSharePointClient ^>	_managedObject;

public:
	CSharePointAdapter(void);
	~CSharePointAdapter(void);
	int Disconnect();

public:
	void SetConfig(wchar_t* url,  wchar_t* proxy,  wchar_t* user,  wchar_t* password,  wchar_t* domain, wchar_t* authtype, enum ClientAuthenticationMode am, bool ntlm, int interval, int timeout);
	void SetCertFile(wchar_t* certfile);
	void SetFuagConfig(wchar_t* fuagAuth, wchar_t* userAgent);
	void SetProxySettings(bool useproxy, bool bypassproxy, wchar_t* proxyuser, wchar_t* proxypassword, wchar_t* proxydomain, wchar_t* proxybypass, wchar_t* authtype);
	void SetViewTitle(wchar_t* viewTitle);
	void SetContentLocation(wchar_t* contentLoc);
	void SetDebug(bool bDebug);
	void GetLastError(VARIANT *error);
	bool MoreData();
	void RetrieveLists(VARIANT *vValues, int &ret);
	void RetrieveViews(wchar_t* listname, VARIANT *vValues, int &ret);
	void RetrieveFields(wchar_t* listname, VARIANT *vValue, int &ret);
	void RetrieveListItems(wchar_t* listname, VARIANT *vValues, int &ret);
	void StripHTML( wchar_t* listName, VARIANT *vValue);
	void ExtractImagesFromHtml(wchar_t* html,  VARIANT *vValues);
};
