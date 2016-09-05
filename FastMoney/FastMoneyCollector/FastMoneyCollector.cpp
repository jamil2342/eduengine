
#include "FastMoneyCollector.h"
#include "MemFile.h"
#include "DBConnector.h"
#include "PSDBSchema.h"
#include "PSDBDatum.h"
#include "UpdateBlob.h"  
#include "PSDBCommon.h"
#include "SharePointCommon.h"

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
			m_iDataCounter = 0;
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
			//#####do correct
			if (true)
			{
				int tableid = 1;
				VARIANT vtItems;
				VARIANT vtData;
				VARIANT vtError;
				VariantInit(&vtItems);
				VariantInit(&vtData);
				VariantInit(&vtError);

				_bstr_t strNumber(_T("1"));
				//m_pOwner->m_pSharePoint->RetrieveListItems(_bstr_t(m_pOwner->m_base.m_szListTitle), &vtItems, nres);
				RetrieveListItems(Url, &vtItems, nres);
				//#####do correct
				bool bMoreData = false;// m_pOwner->m_pSharePoint->MoreData();
				if (vtItems.vt != VT_EMPTY && nres == 0)
				{
					long			lLowerBound = 0;
					long			lUpperBound = 0;
					long			lCounter = 0;

					SafeArrayGetLBound(V_ARRAY(&vtItems), 1, &lLowerBound);
					SafeArrayGetUBound(V_ARRAY(&vtItems), 1, &lUpperBound);
					long			idx = lLowerBound;
					SafeArrayGetElement(V_ARRAY(&vtItems), &idx, &vtData);
					int cnt = vtData.iVal;
					_stprintf_s(buf, _countof(buf), _T("DoQuery() cnt=%d, lbound=%d, ubound=%d\n"), cnt, lLowerBound, lUpperBound);
					//#####do correct
					//m_pOwner->ShowMsgString(false, buf);
					idx++;
					long lVal;
					double dVal;
					string tmpStr;
					CString fieldname;
					while (idx <= lUpperBound)
					{
						long tmpIdx = idx;
						for (int i = 0; i < cnt; i++)
						{
							SafeArrayGetElement(V_ARRAY(&vtItems), &tmpIdx, &vtData);
							fieldname = (LPCTSTR)_bstr_t(vtData.bstrVal);
							fieldname = fieldname.MakeLower();
							fieldname.Replace(_T("_"), _T(""));
							fieldname.Replace(_T("x0020"), _T(""));
							fieldname.Replace(_T("x002d"), _T(""));
							VariantClear(&vtData);
							tmpIdx++;
							SafeArrayGetElement(V_ARRAY(&vtItems), &tmpIdx, &vtData);
							//#####do correct
							//if (fieldname == _T("id"))
							//{
							//	strNumber = vtData.bstrVal;
							//	//#####do correct
							//	pTblKeys = m_pOwner->m_keys.GetTable(tableid);
							//	if (pTblKeys == NULL)
							//	{
							//		Implement_Options impl = IMPLEMENT_YES;
							//		//#####do correct
							//		//m_pOwner->ShowMsgFmt(false, "DoQuery() Inserting key %s", (LPCTSTR)strNumber);
							//		m_pOwner->m_keys.AddKey(tableid, strNumber, impl);
							//		m_pOwner->m_pDatum->AppendRecVal(strNumber, _T(""), _T(""), true);
							//		CTableKeys* m_tKeys2 = m_pOwner->m_keys.GetTable(tableid);//tableKeys;
							//		ImpKeyMapIter iter2 = m_tKeys2->m_impKeys.find(strNumber);
							//		if (iter2 != m_tKeys2->m_impKeys.end())
							//		{
							//			pKeyStuff = iter2->second;
							//			pKeyStuff->bReceived = true;
							//		}
							//	}
							//	else
							//	{
							//		mapIter = pTblKeys->m_impKeys.find(strNumber);
							//		if (mapIter == pTblKeys->m_impKeys.end())
							//		{
							//			Implement_Options impl = IMPLEMENT_YES;
							//			//#####do correct
							//			//m_pOwner->ShowMsgFmt(false, "DoQuery() Inserting key %s", (LPCTSTR)strNumber);
							//			m_pOwner->m_keys.AddKey(tableid, strNumber, impl);
							//			m_pOwner->m_pDatum->AppendRecVal(strNumber, _T(""), _T(""), true);
							//			ImpKeyMapIter iter3 = pTblKeys->m_impKeys.find(strNumber);
							//			if (iter3 != pTblKeys->m_impKeys.end())
							//			{
							//				pKeyStuff = iter3->second;
							//				pKeyStuff->bReceived = true;
							//			}
							//			else
							//			{
							//				// bad
							//			}
							//		}
							//		else
							//		{
							//			pKeyStuff = mapIter->second;
							//			pKeyStuff->bReceived = true;
							//		}
							//	}
							//	break;
							//}
							tmpIdx++;
						}
						for (int i = 0; i < cnt; i++)
						{
							SafeArrayGetElement(V_ARRAY(&vtItems), &idx, &vtData);
							fieldname = (LPCTSTR)_bstr_t(vtData.bstrVal);
							fieldname = fieldname.MakeLower();
							fieldname.Replace(_T("_"), _T(""));
							fieldname.Replace(_T("x0020"), _T(""));
							fieldname.Replace(_T("x002d"), _T(""));
							VariantClear(&vtData);
							string stype;
							FIELD_MAP_ITER iter = m_pOwner->m_colFields.begin();
							while (iter != m_pOwner->m_colFields.end())
							{
								if ((*iter).second->m_fieldName.compare(fieldname) == 0)
								{
									stype = (*iter).second->m_fieldType;
									break;
								}
								iter++;
							}

							idx++;
							SafeArrayGetElement(V_ARRAY(&vtItems), &idx, &vtData);

							_variant_t vtTemp(vtData, false);
							if (vtData.vt != VT_NULL && vtData.vt != VT_EMPTY)
							{
								switch (m_pOwner->SPTYPETOPOLY[stype])
								{
								case POLY_STR:
									vtTemp.ChangeType(VT_BSTR);
									break;
								case POLY_INT:
									vtTemp.ChangeType(VT_I4);
									break;
								case POLY_FLOAT:
									vtTemp.ChangeType(VT_R8);
									break;
								case POLY_UNKNOWN:
									vtTemp.ChangeType(VT_BSTR);
									break;
								}
							}
							if (vtTemp.vt == VT_BSTR)
							{
								//tmpStr = (LPCSTR)_bstr_t(vtTemp.bstrVal);
								//wstring tmpStr(vtTemp.bstrVal);
								//m_pOwner->ShowMsgFmt(false, _T("%s:%s:BSTR:%s\n"), (LPCTSTR)strNumber, fieldname,tmpStr.c_str());
								m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, (LPCWSTR)_bstr_t(vtTemp.bstrVal), false);
							}
							else if (vtTemp.vt == VT_I4)
							{
								lVal = vtTemp.lVal;
								//m_pOwner->ShowMsgFmt(false, _T("%s:%s:INT:%d\n"), (LPCTSTR)strNumber, fieldname, lVal);
								m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, lVal, false);
							}
							else if (vtTemp.vt == VT_R8)
							{
								dVal = vtTemp.dblVal;
								//m_pOwner->ShowMsgFmt(false, _T("%s:%s:FLOAT:%f\n"), (LPCTSTR)strNumber, fieldname, dVal);
								m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, dVal, false);
							}
							else if (vtTemp.vt == VT_NULL)
							{
								//m_pOwner->ShowMsgFmt(false, _T("%s:%s:NULL:(null)\n"), (LPCTSTR)strNumber, fieldname);
								m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, _T(""), false);
							}
							else
							{
								sprintf_s(buf, _countof(buf), _T("%s:%s:VT_TYPE %d\n"), (LPCTSTR)strNumber, fieldname, vtData.vt);
								//m_pOwner->ShowMsgString(false, buf);
								m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, _T(""), false);
							}
							VariantClear(&vtData);
							VariantClear(&vtTemp);
							idx++;
						}
					}
					//#####do correct
					/*if (!bMoreData)
					{
					pTblKeys = m_pOwner->m_keys.GetTable(tableid);
					if (pTblKeys)
					{
					mapIter = pTblKeys->m_impKeys.begin();
					while (mapIter != pTblKeys->m_impKeys.end())
					{
					pKeyStuff = mapIter->second;
					if (pKeyStuff->bReceived == false)
					{
					sprintf_s(buf, _countof(buf), _T("Removing expired key %s\n"), (LPCSTR)mapIter->second->keyval);
					m_pOwner->ShowMsgString(false, buf);
					m_pOwner->m_pDatum->RemoveRec(mapIter->second->keyval);
					mapIter = pTblKeys->m_impKeys.erase(mapIter);
					}
					else
					{
					pKeyStuff->bReceived = false;
					mapIter++;
					}

					}
					}
					}
					*/
					try
					{
						VARIANT impl2;		VariantInit(&impl2);
						VARIANT info;		VariantInit(&info);
						//#####do correct
						//Acquire lock(this);

						m_pOwner->m_pDatum->VariantOut(&impl2);
						IPSDBHelper *helper = m_pOwner->GetPSDBHelper();
						HRESULT hres;
						int reqID = 0;

						if (helper != NULL)
						{
							try
							{
								// new blob data
								hres = helper->UpdateDataTblBlob(impl2);	//verify
								m_pOwner->m_pDatum->ResetBlobs();

							}
							catch (_com_error ex)
							{
								sprintf_s(buf, _countof(buf), _T("RetrieveListItems() failed to update blob. Error %s"), ex.ErrorMessage());
								m_pOwner->ShowMsgString(true, buf);
								//#####do correct
								//m_ConnectionOpen = ERR_RECOVERY;
							}
						}

						VariantClear(&info);
						VariantClear(&impl2);
					}
					catch (_com_error ex)
					{
						sprintf_s(buf, _countof(buf), _T("RetrieveListItems() exception %s"), ex.ErrorMessage());
						//#####do correct
						//m_pOwner->ShowMsgString(true, buf);
						//m_ConnectionOpen = ERR_RECOVERY;
					}
				}
				//#####do correct
				//else if (nres != 0)
				//{
				//	//m_pOwner->m_pSharePoint->GetLastError(&vtError);
				//	sprintf_s(buf, _countof(buf), _T("DoQuery() - RetrieveListItems() timeout"));
				//	m_pOwner->ShowMsgString(true, buf);
				//	m_ConnectionOpen = ERR_RECOVERY;
				//	//LogEvent(EVENTLOG_INFORMATION_TYPE,szBuf);
				//}
				VariantClear(&vtItems);

			}
			m_iDataCounter++;
#ifdef _DEBUG
			//OutputHeading(
			//	"Dump all objects two memory checkpoints");
			//_CrtMemDumpAllObjectsSince(NULL);
			//OutputHeading("Perform a memory check for heap corruption.");
			//_CrtCheckMemory();
#endif
			return 0;

		}
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
