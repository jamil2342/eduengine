#include "stdafx.h"
#include "SharePointCollector.h"
#include "SharePointData.h"
#include "SharePointCollect.h"

#include <COMDEF.H>
#include "objectdefs.h"
#include "pubutility.h"

#include "PSDBSchema.h"
#include "PSDBDatum.h"
#include "UpdateBlob.h"  //amy
#include "PSDBCommon.h"
// The following macros set and clear, respectively, given bits
// of the C runtime library debug flag, as specified by a bitmask.

#ifdef   _DEBUG
#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)
#endif

//#include "eventloghelpers_publisher.h"
//#define _TIMING_TEST
// This routine place comments at the head of a section of debug output
void OutputHeading(const char * explanation)
{
	_RPT1(_CRT_WARN, "\n\n%s:\n**************************************************************************\n", explanation);

}
// **************************************************************************
CSharePointData::CSharePointData()
//
//	Create a new CNTSSData for Runner or for Property Page.
// **********************************************************************
{
	InitData(NULL);
	m_pThreadMgr = NULL;
}

// **************************************************************************
void CSharePointData::InitData(CEventThread *pMgr)
//
//	Initialize data done from Constructor
// **********************************************************************
{
	m_pThreadMgr = pMgr;

	if(pMgr != NULL && m_ConnectionOpen != INACTIVE)
	{
		_ASSERTE(false);
	}

	m_bQuitProcessing = false;					// Flag to help other threads quit early

	m_ConnectionOpen = INACTIVE;
	m_iDataCounter = 0;
	m_nErrorRecovery = 0;
	_CrtMemCheckpoint(&m_s1);
}

void CSharePointData::DoQuery()
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

	if ((m_pThreadMgr->pmgr->m_pOwner->m_base.m_tableCount > 0) && (m_pThreadMgr->pmgr->m_pOwner->m_base.m_fieldCount > 0))
	{
		int tableid = 1;
			VARIANT vtItems;
			VARIANT vtData;
			VARIANT vtError;
			VariantInit(&vtItems);
			VariantInit(&vtData);
			VariantInit(&vtError);
			
			_bstr_t strNumber(_T("1"));
			m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->RetrieveListItems(_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szListTitle),&vtItems, nres);
			bool bMoreData = m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->MoreData();
			if ( vtItems.vt != VT_EMPTY && nres == 0 )
			{
				long			lLowerBound = 0;
				long			lUpperBound = 0;
				long			lCounter	= 0;

				SafeArrayGetLBound(V_ARRAY(&vtItems), 1, &lLowerBound);
				SafeArrayGetUBound(V_ARRAY(&vtItems), 1, &lUpperBound);
				long			idx = lLowerBound;
				SafeArrayGetElement(V_ARRAY(&vtItems), &idx, &vtData);
				int cnt = vtData.iVal;
				_stprintf_s(buf, _countof(buf), _T("DoQuery() cnt=%d, lbound=%d, ubound=%d\n"), cnt, lLowerBound, lUpperBound);
				m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(false, buf);
				idx++;
				long lVal;
				double dVal;
				string tmpStr;
				CString fieldname;
				while  ( idx <= lUpperBound )
				{
					long tmpIdx = idx;
					for ( int i = 0; i < cnt; i ++ )
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
						if ( fieldname == _T("id"))
						{
							strNumber = vtData.bstrVal;
							pTblKeys = m_pThreadMgr->pmgr->m_pOwner->m_keys.GetTable(tableid);
							if (pTblKeys == NULL)
							{
								Implement_Options impl = IMPLEMENT_YES;
								m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, "DoQuery() Inserting key %s", (LPCTSTR)strNumber);
								m_pThreadMgr->pmgr->m_pOwner->m_keys.AddKey(tableid, strNumber, impl);
								m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal(strNumber, _T(""), _T(""), true);
								CTableKeys* m_tKeys2 = m_pThreadMgr->pmgr->m_pOwner->m_keys.GetTable(tableid);//tableKeys;
								ImpKeyMapIter iter2 = m_tKeys2->m_impKeys.find(strNumber);
								if ( iter2 != m_tKeys2->m_impKeys.end() )
								{
									pKeyStuff = iter2->second;
									pKeyStuff->bReceived = true;
								}
							}
							else 
							{
								mapIter = pTblKeys->m_impKeys.find(strNumber);
								if(mapIter == pTblKeys->m_impKeys.end())
								{
									Implement_Options impl = IMPLEMENT_YES;
									m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, "DoQuery() Inserting key %s", (LPCTSTR)strNumber);
									m_pThreadMgr->pmgr->m_pOwner->m_keys.AddKey(tableid, strNumber, impl);
									m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal(strNumber, _T(""), _T(""), true);
									ImpKeyMapIter iter3 = pTblKeys->m_impKeys.find(strNumber);
									if ( iter3 != pTblKeys->m_impKeys.end() )
									{
										pKeyStuff = iter3->second;
										pKeyStuff->bReceived = true;
									}
									else
									{
										// bad
									}
								}
								else
								{
									pKeyStuff = mapIter->second;
									pKeyStuff->bReceived = true;
								}
							}
							break;
						}
						tmpIdx++;
					}
					for ( int i = 0; i < cnt; i ++ )
					{
						SafeArrayGetElement(V_ARRAY(&vtItems), &idx, &vtData);
						fieldname = (LPCTSTR)_bstr_t(vtData.bstrVal);
						fieldname = fieldname.MakeLower();
						fieldname.Replace(_T("_"), _T(""));
						fieldname.Replace(_T("x0020"), _T(""));
						fieldname.Replace(_T("x002d"), _T(""));
						VariantClear(&vtData);
						string stype;
						FIELD_MAP_ITER iter = m_pThreadMgr->pmgr->m_pOwner->m_colFields.begin();
						while ( iter!= m_pThreadMgr->pmgr->m_pOwner->m_colFields.end() )
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
						if ( vtData.vt != VT_NULL && vtData.vt != VT_EMPTY)
						{
							switch (m_pThreadMgr->pmgr->m_pOwner->SPTYPETOPOLY[stype])
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
						if ( vtTemp.vt == VT_BSTR) 
						{
							//tmpStr = (LPCSTR)_bstr_t(vtTemp.bstrVal);
							//wstring tmpStr(vtTemp.bstrVal);
							//m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, _T("%s:%s:BSTR:%s\n"), (LPCTSTR)strNumber, fieldname,tmpStr.c_str());
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, (LPCWSTR)_bstr_t(vtTemp.bstrVal), false);
						}
						else if ( vtTemp.vt == VT_I4 )
						{
							lVal = vtTemp.lVal;
							//m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, _T("%s:%s:INT:%d\n"), (LPCTSTR)strNumber, fieldname, lVal);
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, lVal, false);
						}
						else if ( vtTemp.vt == VT_R8 )
						{
							dVal = vtTemp.dblVal;
							//m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, _T("%s:%s:FLOAT:%f\n"), (LPCTSTR)strNumber, fieldname, dVal);
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, dVal, false);
						}
						else if ( vtTemp.vt == VT_NULL )
						{
							//m_pThreadMgr->pmgr->m_pOwner->ShowMsgFmt(false, _T("%s:%s:NULL:(null)\n"), (LPCTSTR)strNumber, fieldname);
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, _T(""), false);
						}
						else
						{
							sprintf_s(buf, _countof(buf), _T("%s:%s:VT_TYPE %d\n"), (LPCTSTR)strNumber, fieldname, vtData.vt);
							//m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(false, buf);
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->AppendRecVal((LPCWSTR)strNumber, fieldname, _T(""), false);
						}
						VariantClear(&vtData);
						VariantClear(&vtTemp);
						idx++;
					}
				}
				if (!bMoreData)
				{
					pTblKeys = m_pThreadMgr->pmgr->m_pOwner->m_keys.GetTable(tableid);
					if (pTblKeys)
					{
						mapIter = pTblKeys->m_impKeys.begin();
						while (mapIter != pTblKeys->m_impKeys.end())
						{
							pKeyStuff = mapIter->second;
							if (pKeyStuff->bReceived == false)
							{
								sprintf_s(buf, _countof(buf), _T("Removing expired key %s\n"), (LPCSTR)mapIter->second->keyval);
								m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(false, buf);
								m_pThreadMgr->pmgr->m_pOwner->m_pDatum->RemoveRec(mapIter->second->keyval);
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

				try
				{
					VARIANT impl2;		VariantInit(&impl2);
					VARIANT info;		VariantInit(&info);
					Acquire lock(this);

					m_pThreadMgr->pmgr->m_pOwner->m_pDatum->VariantOut(&impl2);
					IPSDBHelper *helper = m_pThreadMgr->pmgr->m_pOwner->GetPSDBHelper();
					HRESULT hres;
					int reqID = 0;

					if(helper != NULL)
					{
						try
						{
							// new blob data
							hres = helper->UpdateDataTblBlob(impl2);	//verify
							m_pThreadMgr->pmgr->m_pOwner->m_pDatum->ResetBlobs();

						}
						catch (_com_error ex)
						{
							sprintf_s(buf, _countof(buf), _T("RetrieveListItems() failed to update blob. Error %s"), ex.ErrorMessage());
							m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(true, buf);
							m_ConnectionOpen = ERR_RECOVERY;
						}
					}

					VariantClear(&info);
					VariantClear(&impl2);
				}
				catch(_com_error ex )
				{
					sprintf_s(buf, _countof(buf), _T("RetrieveListItems() exception %s"), ex.ErrorMessage());
					m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(true, buf);
					m_ConnectionOpen = ERR_RECOVERY;
				}
			}
			else if ( nres != 0 )
			{
				//m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->GetLastError(&vtError);
				sprintf_s(buf, _countof(buf), _T("DoQuery() - RetrieveListItems() timeout"));
				m_pThreadMgr->pmgr->m_pOwner->ShowMsgString(true, buf);
				m_ConnectionOpen = ERR_RECOVERY;
				//LogEvent(EVENTLOG_INFORMATION_TYPE,szBuf);
			}
			VariantClear(&vtItems);

	}
	m_iDataCounter++;
#ifdef _DEBUG
	OutputHeading(
		"Dump all objects two memory checkpoints");
	_CrtMemDumpAllObjectsSince(NULL);
	OutputHeading("Perform a memory check for heap corruption.");
	_CrtCheckMemory();
#endif
	return;
}


// **************************************************************************
CSharePointData::~CSharePointData()
//
//	Data class destructor for cleanup.
// **********************************************************************
{

	m_bQuitProcessing = true;					// Flag all early to quit!!
	Acquire lock(this);
	if (m_ConnectionOpen == ACTIVE)
		doDisconnect();

	m_pThreadMgr = NULL;
}


// **************************************************************************
ULONG CSharePointData::Connect()
{
	if(m_pThreadMgr == NULL)
		return S_FALSE;
	m_pThreadMgr->pmgr->m_pOwner->CreateSharePointInstance();
	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->SetConfig(
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szServiceUrl),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxy),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szUser),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szPassword),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szDomain),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szAuthType),
		(enum ClientAuthenticationMode)m_pThreadMgr->pmgr->m_pOwner->m_base.m_authmode,
		m_pThreadMgr->pmgr->m_pOwner->m_base.m_ntlm, 
		m_pThreadMgr->pmgr->m_pOwner->m_base.m_update_interval,
		m_pThreadMgr->pmgr->m_pOwner->m_base.m_update_timeout);

	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->SetViewTitle(_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szViewTitle));
	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->SetFuagConfig(_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szFuagAuth), L"" );
	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->SetContentLocation(_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szContentFolder));

	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->SetProxySettings(
		m_pThreadMgr->pmgr->m_pOwner->m_base.m_bUseProxy,
		m_pThreadMgr->pmgr->m_pOwner->m_base.m_bBypassProxy,
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxyUser),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxyPassword),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxyDomain),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxyBypassList),
		_bstr_t(m_pThreadMgr->pmgr->m_pOwner->m_base.m_szProxyAuthType)
		);

	m_bQuitProcessing = false;					// Keep dogs behind starting line until now
	m_ConnectionOpen = ACTIVE;
	m_nErrorRecovery = 0;
	return S_OK;
}


// **************************************************************************
void CSharePointData::doDisconnect()
//
// Stop Data Feed and Logout
// if (we got a data update in-between checking enabled, stop feed 
//  and shut down
// **********************************************************************
{
	m_ConnectionOpen = TRANSITION;		// transition

	m_bQuitProcessing = true;
	m_ConnectionOpen = INACTIVE;
	m_pThreadMgr->pmgr->m_pOwner->m_pSharePoint->Disconnect();
}

void CSharePointData::PublishFields()
{
	m_pThreadMgr->pmgr->m_pOwner->PublishFields();
}
