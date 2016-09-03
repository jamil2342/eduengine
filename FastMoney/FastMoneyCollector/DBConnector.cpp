#include "StdAfx.h"
#include "FastMoneyCollector.h"
//#include "RSSCollect.h"
//#include "EventMgr.h"
#include "DBConnector.h"

CDBConnector::CDBConnector(void)
{
	m_pPolyCon = NULL;
	m_pSQLCon = NULL;
}

CDBConnector::~CDBConnector(void)
{
	if (m_pPolyCon)
		m_pPolyCon = NULL;
	if (m_pSQLCon)
		m_pSQLCon = NULL;
}

void CDBConnector::InitConnect()
{
	//	FastMoneyCollector * pOwner;
	HRESULT hr = E_FAIL;
	char szMsg[2000];
	CString strSQLCon;
	CString strPolyCon;
	string szSqlProv = "";
	//m_pOwner = pOwner;
	CRegKey regKey;
	long ret;
	ret = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Symon Communications"), KEY_READ);

	char szTemp[1024];
	char szValue[1024];
	DWORD dwCount = 1024;

	if (ret == ERROR_SUCCESS)
	{
		if (m_pPolyCon == NULL)  //Poly Connection
		{
			try
			{
				m_pPolyCon.CreateInstance(__uuidof(ado::Connection));
				ATLASSERT(m_pPolyCon != NULL);
			}
			catch (const _com_error& e)
			{
				hr = e.Error();
				m_pPolyCon = NULL;
			}
			catch (...)
			{
				hr = E_UNEXPECTED;
				m_pPolyCon = NULL;
				//Error(_T("Unidentified exception occured in Connect()"), __uuidof(IConverter), hr);
			}

			if (m_pPolyCon != NULL)
			{
				try
				{
					strPolyCon = "Provider=Polyhedra OLE DB Provider;Data Source=LOCALHOST:31001;User ID=SYSTEM;Password=jimmyTHEgreek;";
					m_pPolyCon->CursorLocation = ado::adUseServer;

					m_pPolyCon->Open((LPCTSTR)strPolyCon, L"", L"", ado::adOptionUnspecified);

					if (m_pPolyCon->State == ado::adStateOpen)
					{
						hr = S_OK;
					}
				}
				catch (...)
				{
					m_pPolyCon = NULL;
				}
			}
		}

		if (m_pSQLCon == NULL)
		{
			try
			{
				m_pSQLCon.CreateInstance(__uuidof(ado::Connection));
				ATLASSERT(m_pSQLCon != NULL);
			}
			catch (const _com_error& e)
			{
				hr = e.Error();
				sprintf(szMsg, "Error in SQL Create instance, error is %d ", hr);
				//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
				m_pSQLCon = NULL;
			}
			catch (...)
			{
				sprintf(szMsg, "Unexpected error in SQL Create instance");
				//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
				hr = E_UNEXPECTED;
				m_pSQLCon = NULL;
			}

			if (m_pSQLCon != NULL)
			{
				ret = regKey.QueryStringValue(_T("SQLDATA"), szTemp, &dwCount);

				if (ret == ERROR_SUCCESS) // found and retrieved the SQL Connection string
				{
					strSQLCon = szTemp;
					ret = regKey.QueryStringValue(_T("SQLSERVER"), szTemp, &dwCount);
					if (ret == ERROR_SUCCESS)
					{
						sprintf_s(szValue, 1024, (LPCSTR)strSQLCon, szTemp);
						strSQLCon = szValue;
					}
					else
					{
						m_pSQLCon = NULL;
					}
				}
				else
				{
					m_pSQLCon = NULL;
				}

				if (m_pSQLCon != NULL)
				{
					//#ifdef _DEBUG
					//					sprintf(szMsg, "CDBConnector::InitConnect - constring for SQL = %s", strSQLCon);
					//					LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
					//#endif
					try
					{
						m_pSQLCon->CursorLocation = ado::adUseClient;

						m_pSQLCon->Open(_bstr_t(strSQLCon), L"SYSTEM", L"jimmyTHEgreek", ado::adOptionUnspecified);

						if (m_pSQLCon->State == ado::adStateOpen)
						{
							hr = S_OK;
						}
					}
					catch (_com_error &e)
					{
						sprintf(szMsg, "SQL - SQL Connection failed, Connection string - %s - with error - %s", (LPCSTR)strSQLCon, (LPCSTR)e.ErrorMessage());
						//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
						m_pSQLCon = NULL;
					}
					catch (...)
					{
						sprintf(szMsg, "SQL - SQL Connection failed, Connection string - %s", (LPCSTR)strSQLCon);
						//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
						m_pSQLCon = NULL;
					}
				}
			}
		}
	}
}

bool CDBConnector:: AddFastMoneyDataToDB(Item ^ fm)
{
	HRESULT hRet = S_OK;
	char szMsg[2000];
	CString strCmd;
	strCmd.Format(_T("INSERT INTO FastMoney (title,pubDate,author,link,description,itunes_category,source,itunes_subtitle,itunes_duration,itunes_summary,itunes_explicit,itunes_block,itunes_keywords,itunes_author,guid,enclosure) Values ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"), fm->Title, fm->PubDate, fm->Author[0], fm->Link, fm->Description, fm->Category->Text, fm->Source->Url, fm->Subtitle, fm->Duration, fm->Summary, fm->Explicit, fm->Block, fm->Keywords, fm->Author[0], fm->Guid, fm->Enclosure->Url);
	try
	{
		if (m_pSQLCon != NULL)
		{
			ado::_CommandPtr     pSqlCmd(__uuidof(ado::Command));
			pSqlCmd->ActiveConnection = m_pSQLCon;
			pSqlCmd->CommandType = ado::adCmdText;
			pSqlCmd->CommandText = (LPCTSTR)strCmd;
			try
			{
				pSqlCmd->Execute(NULL, NULL, ado::adOptionUnspecified);
			}
			catch (_com_error &e)
			{
				sprintf(szMsg, "SQL - SQL statement failed. %s - with error - %s", (LPCSTR)strCmd, e.ErrorMessage());
				//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
				return false;
			}
			catch (...)
			{
				sprintf(szMsg, "SQL - SQL statement failed. %s", (LPCSTR)strCmd);
				//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
				return false;
			}
			pSqlCmd->ActiveConnection = NULL;
		}
	}
	catch (const _com_error& e)
	{
		hRet = e.Error();
		string szError = e.ErrorMessage();
		sprintf(szMsg, "Add Group Com Error - %s \n", (LPCSTR)szError.c_str());
		//	LogAppEvent(EVENTLOG_INFORMATION_TYPE, szMsg);
		return false;
	}
	catch (...)
	{
		hRet = E_UNEXPECTED;
		return false;
	}
	return true;
}

