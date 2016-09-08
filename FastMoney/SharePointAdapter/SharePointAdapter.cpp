// SharePointAdapter.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "ISharePointAdapter.h"
#include "SharePointAdapter.h"

void WriteEventLog(String^ msg)
{
	String^ ews = gcnew String("SharePointAdapter");
	if (!EventLog::SourceExists(ews))
	{
		EventLog::CreateEventSource(ews, "Application");
	}
	EventLog^ myLog = gcnew EventLog();
	myLog->Source = ews;
	myLog->WriteEntry(msg);

}

void MarshalString ( String ^ s, std::string& os ) 
{
	if ( String::IsNullOrEmpty(s) )
		return;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString ( String ^ s, std::wstring& os ) 
{
   const wchar_t* chars = 
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

CSharePointAdapter::CSharePointAdapter(void)
{
    _managedObject = gcnew CSharePointClient();
}

CSharePointAdapter::~CSharePointAdapter(void)
{
}

int CSharePointAdapter::Disconnect()
{ 
	_managedObject->ExitNow = true;
	int timeout = 0;
	while (_managedObject->m_InProgress && timeout++ < 60 )
	{
		System::Diagnostics::Trace::WriteLine("Checking m_InProgress...");
		Sleep(1000);
	}
	_managedObject->killBindGrid();
	return 0;
}

void CSharePointAdapter::SetConfig(wchar_t* url,  wchar_t* proxy,  wchar_t* user,  wchar_t* password,  wchar_t* domain, wchar_t* authtype, enum ClientAuthenticationMode am, bool ntlm, int interval, int updatetimeout)
{
	_managedObject->ServiceUrl = Marshal::PtrToStringUni(static_cast<IntPtr>(url));
	_managedObject->ProxyUrl = Marshal::PtrToStringUni(static_cast<IntPtr>(proxy));
	_managedObject->User = Marshal::PtrToStringUni(static_cast<IntPtr>(user));
	_managedObject->Password = Marshal::PtrToStringUni(static_cast<IntPtr>(password));
	_managedObject->Domain = Marshal::PtrToStringUni(static_cast<IntPtr>(domain));
	_managedObject->AuthType = Marshal::PtrToStringUni(static_cast<IntPtr>(authtype));
	_managedObject->AuthMode = am; 
	_managedObject->NTLM = ntlm;
	_managedObject->UpdateInterval = interval;
	_managedObject->UpdateTimeout = updatetimeout;
	return;
}

void CSharePointAdapter::SetDebug(bool bDebug)
{
	_managedObject->SetDebug(bDebug);
}

void CSharePointAdapter::SetProxySettings(bool useproxy, bool bypassproxy, wchar_t* proxyuser, wchar_t* proxypassword, wchar_t* proxydomain, wchar_t*proxybypass, wchar_t* authtype)
{
	_managedObject->ProxyUser = Marshal::PtrToStringUni(static_cast<IntPtr>(proxyuser));
	_managedObject->ProxyPassword = Marshal::PtrToStringUni(static_cast<IntPtr>(proxypassword));
	_managedObject->ProxyDomain = Marshal::PtrToStringUni(static_cast<IntPtr>(proxydomain));
	_managedObject->BypassList = Marshal::PtrToStringUni(static_cast<IntPtr>(proxybypass));
	_managedObject->ProxyAuthType = Marshal::PtrToStringUni(static_cast<IntPtr>(authtype));
	_managedObject->UseProxy = useproxy;
	_managedObject->BypassProxy = bypassproxy;
}


void CSharePointAdapter::SetFuagConfig(wchar_t* fuagAuth,  wchar_t* userAgent)
{
	if ( fuagAuth != NULL && wcslen(fuagAuth) > 0 )
		_managedObject->FuagAuth = Marshal::PtrToStringUni(static_cast<IntPtr>(fuagAuth));

	if ( userAgent != NULL  && wcslen(userAgent) > 0)
		_managedObject->UserAgent = Marshal::PtrToStringUni(static_cast<IntPtr>(userAgent));
	return;
}

void CSharePointAdapter::SetCertFile(wchar_t* certfile)
{
	_managedObject->CertFile = Marshal::PtrToStringUni(static_cast<IntPtr>(certfile));
}

void CSharePointAdapter::SetViewTitle(wchar_t* query)
{
	_managedObject->ViewTitle = Marshal::PtrToStringUni(static_cast<IntPtr>(query));
}

void CSharePointAdapter::SetContentLocation(wchar_t* folder)
{
	_managedObject->ContentFolder = Marshal::PtrToStringUni(static_cast<IntPtr>(folder));
}

void CSharePointAdapter::GetLastError(VARIANT *vError)
{
	String ^error =  _managedObject->LastError;
	VariantInit(vError);
	vError->vt = VT_BSTR;
	IntPtr ip = Marshal::StringToBSTR(error);
	vError->bstrVal = static_cast<BSTR>(ip.ToPointer());
	Marshal::FreeBSTR(ip);
	_managedObject->LastError = nullptr;
}

void CSharePointAdapter::RetrieveLists(VARIANT *vValues, int &ret)
{
	List<String ^>^ rlist = _managedObject->RetrieveLists();
	String ^error =  _managedObject->LastError;
	VariantInit(vValues);
	vValues->vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	LONG lCount = 0;
	VARIANT varProperty;
	if ( error != nullptr )
	{
		if ( error->Length > 0 )
		{
			ret = 1;
			return;
		}
	}
	psa = SafeArrayCreateVector( VT_VARIANT, 0, rlist->Count);
	for each (String^ list in rlist)
	{
		varProperty.vt = VT_BSTR;
		IntPtr ip = Marshal::StringToBSTR(list);
		varProperty.bstrVal = static_cast<BSTR>(ip.ToPointer());
		SafeArrayPutElement( psa, &lCount, (void *)&varProperty );
		Marshal::FreeBSTR(ip);
		//VariantClear(&varProperty);
		lCount++;
	}
	vValues->parray = psa;
}

void CSharePointAdapter::RetrieveViews(wchar_t* listname, VARIANT *vValues, int &ret)
{
	List<String ^>^ rlist = _managedObject->RetrieveViews(gcnew String(listname));
	String^ error = _managedObject->LastError;
	VariantInit(vValues);
	vValues->vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	LONG lCount = 0;
	VARIANT varProperty;
	if ( error != nullptr )
	{
		if ( error->Length > 0 )
		{
			ret = 1;
			return;
		}
	}
	psa = SafeArrayCreateVector( VT_VARIANT, 0, rlist->Count);
	for each (String^ list in rlist)
	{
		varProperty.vt = VT_BSTR;
		IntPtr ip = Marshal::StringToBSTR(list);
		varProperty.bstrVal = static_cast<BSTR>(ip.ToPointer());
		SafeArrayPutElement( psa, &lCount, (void *)&varProperty );
		Marshal::FreeBSTR(ip);
		//(&varProperty);
		lCount++;
	}
	vValues->parray = psa;
}

void CSharePointAdapter::RetrieveFields(wchar_t* listname, VARIANT *vValues, int &ret)
{
	Dictionary<String ^,String ^>^ flist = _managedObject->RetrieveFields(gcnew String(listname));
	String^ error = _managedObject->LastError;
	VariantInit(vValues);
	vValues->vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	LONG lCount = 0;
	VARIANT varProperty;
	if ( error != nullptr )
	{
		if ( error->Length > 0 )
		{
			ret = 1;
			return;
		}
	}

	psa = SafeArrayCreateVector( VT_VARIANT, 0, flist->Count * 2);
	for each (KeyValuePair<String ^,String ^> list in flist)
	{
		varProperty.vt = VT_BSTR;
		IntPtr ip = Marshal::StringToBSTR(list.Key);
		varProperty.bstrVal = static_cast<BSTR>(ip.ToPointer());
		SafeArrayPutElement( psa, &lCount, (void *)&varProperty );
		Marshal::FreeBSTR(ip);
		//VariantClear(&varProperty);
		lCount++;

		varProperty.vt = VT_BSTR;
		ip = Marshal::StringToBSTR(list.Value);
		varProperty.bstrVal = static_cast<BSTR>(ip.ToPointer());
		SafeArrayPutElement( psa, &lCount, (void *)&varProperty );
		Marshal::FreeBSTR(ip);
		//VariantClear(&varProperty);
		lCount++;
	}
	vValues->parray = psa;

}

bool CSharePointAdapter::MoreData()
{
	return _managedObject->MoreData;
}

void CSharePointAdapter::RetrieveListItems( wchar_t* listName, VARIANT *vValues, int &ret)
{
	DataTable^ DT = _managedObject->RetrieveListItems(gcnew String(listName));
	String^ error = _managedObject->LastError;
	LONG lRow = 0;
	SAFEARRAY *psa;
	//LONG lStores = 0;
	SAFEARRAYBOUND saBoundNew;
	VARIANT vtTemp;
	VariantInit(&vtTemp);
	long ubound;
	if ( error != nullptr )
	{
		if ( error->Length > 0 )
		{
			ret = 1;
			return;
		}
	}
	if (DT == nullptr)
	{
		return;
	}
	if (vValues->vt == (VT_ARRAY | VT_VARIANT))
	{
		psa = vValues->parray;
		SafeArrayGetUBound(psa, 1, &ubound);
		saBoundNew.lLbound = 0;
		saBoundNew.cElements = ubound + 1 + (DT->Columns->Count * (DT->Rows->Count * 2) + 1);
		SafeArrayRedim(psa, &saBoundNew);
		lRow = ubound + 1;
	}
	else
	{
		VariantInit( vValues );
		vValues->vt = VT_ARRAY | VT_VARIANT;
		psa = SafeArrayCreateVector( VT_VARIANT, 0, DT->Columns->Count * (DT->Rows->Count * 2) + 1);
	}

	long lRow0 = 0;
	int cnt = DT->Columns->Count;
	vtTemp.vt = VT_I4;
	vtTemp.lVal = cnt;
	SafeArrayPutElement( psa, &lRow0, (void *)&vtTemp);
	if ( lRow == 0 )
		lRow++;

    for each (DataRow^ row in DT->Rows)
    {
        for each (DataColumn^ col in DT->Columns)
        {
			Marshal::GetNativeVariantForObject(col->ColumnName, IntPtr(&vtTemp));
			SafeArrayPutElement( psa, &lRow, (void *)&vtTemp);
			lRow++;
			VariantClear(&vtTemp);

			Marshal::GetNativeVariantForObject(row[col], IntPtr(&vtTemp));
			SafeArrayPutElement( psa, &lRow, (void *)&vtTemp);
			VariantClear(&vtTemp);
			lRow++;
        }
        //Console::WriteLine();
    }
	vValues->parray = psa;
	
}

//void CSharePointAdapter::DownloadFile(wchar_t* url, int &ret)
//{
//	ret = _managedObject->DownLoadUrl(gcnew String(url)) ? 0: 1;
//}
//

void CSharePointAdapter::StripHTML( wchar_t* listName, VARIANT *vValue)
{
	IntPtr ip = Marshal::StringToBSTR(_managedObject->StripHTML(gcnew String(listName)));
	BSTR bs = SysAllocString(static_cast<BSTR>(ip.ToPointer()));
	if ( SysStringLen(bs) != 0 )
	{
		vValue->vt = VT_BSTR;
		vValue->bstrVal = bs;
	}
	Marshal::FreeBSTR(ip);
}

void CSharePointAdapter::ExtractImagesFromHtml(wchar_t* listName, VARIANT *vValues)
{
	List<String ^>^ rlist = _managedObject->ExtractImages(gcnew String(listName));
	VariantInit(vValues);
	vValues->vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAY *psa;
	LONG lCount = 0;
	VARIANT varProperty;
	psa = SafeArrayCreateVector( VT_VARIANT, 0, rlist->Count);
	for each (String^ list in rlist)
	{
		varProperty.vt = VT_BSTR;
		IntPtr ip = Marshal::StringToBSTR(list);
		varProperty.bstrVal = static_cast<BSTR>(ip.ToPointer());
		SafeArrayPutElement( psa, &lCount, (void *)&varProperty );
		Marshal::FreeBSTR(ip);
		//VariantClear(&varProperty);
		lCount++;
	}
	vValues->parray = psa;
}
