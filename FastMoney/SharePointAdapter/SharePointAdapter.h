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


	void RetrieveListItems1(wchar_t* url, VARIANT *vValues, int &ret)
	{
		CSharePointClient ^ _managedObject = gcnew CSharePointClient();
		DataTable^ DT = _managedObject->GetFastMoneyDataTable(gcnew String(url));
		//String^ error = _managedObject->LastError;
		LONG lRow = 0;
		SAFEARRAY *psa;
		//LONG lStores = 0;
		SAFEARRAYBOUND saBoundNew;
		VARIANT vtTemp;
		VariantInit(&vtTemp);
		long ubound;

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
			VariantInit(vValues);
			vValues->vt = VT_ARRAY | VT_VARIANT;
			psa = SafeArrayCreateVector(VT_VARIANT, 0, DT->Columns->Count * (DT->Rows->Count * 2) + 1);
		}

		long lRow0 = 0;
		int cnt = DT->Columns->Count;
		vtTemp.vt = VT_I4;
		vtTemp.lVal = cnt;
		SafeArrayPutElement(psa, &lRow0, (void *)&vtTemp);
		if (lRow == 0)
			lRow++;

		for each (DataRow^ row in DT->Rows)
		{
			for each (DataColumn^ col in DT->Columns)
			{
				Marshal::GetNativeVariantForObject(col->ColumnName, IntPtr(&vtTemp));
				SafeArrayPutElement(psa, &lRow, (void *)&vtTemp);
				lRow++;
				VariantClear(&vtTemp);

				Marshal::GetNativeVariantForObject(row[col], IntPtr(&vtTemp));
				SafeArrayPutElement(psa, &lRow, (void *)&vtTemp);
				VariantClear(&vtTemp);
				lRow++;
			}
			//Console::WriteLine();
		}
		vValues->parray = psa;

	}

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
