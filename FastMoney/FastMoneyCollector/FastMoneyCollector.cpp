
#include "FastMoneyCollector.h"
#include "MemFile.h"
#include "DBConnector.h"
#include "PSDBSchema.h"
#include "PSDBDatum.h"
#include "UpdateBlob.h"  //amy
#include "PSDBCommon.h"
using namespace System;

using namespace System;



namespace FastMoneyCollector
{
#ifdef __cplusplus
	extern "C"
	{
#endif
		void RetrieveListItems(wchar_t* url, VARIANT *vValues, int &ret)
		{
			FastMoneyClient ^ _managedObject = FastMoneyCollector::Instance->Obj;
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


		__declspec(dllexport)  int GetFastMoneyDataTable(wchar_t* Url)
		{
			int nres = 0;
			TCHAR buf[1000];
			CTableKeys *pTblKeys = NULL;
			CKeyStuff *pKeyStuff;
			ImpKeyMapIter mapIter;

			VARIANT     vTimeStamp;	VariantInit(&vTimeStamp);
			SYSTEMTIME  st;
			GetSystemTime(&st);
			vTimeStamp.vt = VT_DATE;
			SystemTimeToVariantTime(&st, &vTimeStamp.date);


			int tableid = 1;
			VARIANT vtItems;
			VARIANT vtData;
			VARIANT vtError;
			VariantInit(&vtItems);
			VariantInit(&vtData);
			VariantInit(&vtError);

			_bstr_t strNumber(_T("1"));
			RetrieveListItems(Url, &vtItems, nres);
			return 0;

		}

		__declspec(dllexport) int GetFastMoney(wchar_t* Url)
		{

			FastMoneyClient ^ Service = FastMoneyCollector::Instance->Obj;
			array< Item^ >^ local = Service->GetFastMoney(gcnew String(Url));

			try
			{
				CDBConnector dbCon;
				dbCon.InitConnect();

				for (size_t i = 0; i < local->Length; i++)
				{
					dbCon.AddFastMoneyDataToDB(local[i]);
				}


				return 1;
			}
			catch (_com_error ex)
			{
				return 0;
			}

		}

#ifdef __cplusplus
	}
#endif
}