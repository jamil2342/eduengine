// ErrorsAndDebug.cpp - Error and debug class for manipulating
//                      Errors and debug information.
//
#include "stdafx.h"
#include <s2locks.h>
#include <StringHelper.h>
#include <StreamHelper.h>
#include "ErrorsAndDebug.h"

// **************************************************************************
CErrorsAndDebug::CErrorsAndDebug()
	//
	//  Constructor - Initialize things.
	// **********************************************************************
	{
	m_bShowDebugMsgs = false;
	}

// **************************************************************************
CErrorsAndDebug::~CErrorsAndDebug()
	//
	//  Constructor - Cleanup things.
	// **********************************************************************
	{
	}

// **************************************************************************
void CErrorsAndDebug::ShowMsgFmt(bool bErrorMsg, LPCSTR pszFormat, ...)
	//
    //  Add some Status Information
	// **********************************************************************
    {
	if (!pszFormat) return;
	if (!strlen(pszFormat)) return;

	if (bErrorMsg)
		{
		m_lErrors++;
		}

	string szMsg;
	va_list argList;

	va_start(argList, pszFormat);
	int nRet = stringFormatV(szMsg, pszFormat, argList);
	va_end(argList);

	if (!szMsg.empty() && m_bShowDebugMsgs)
		m_StatusMsgs.AddMsg(szMsg);
	OutputDebugString(szMsg.c_str());
	}

// **************************************************************************
void CErrorsAndDebug::ShowMsgString(bool bErrorMsg, LPCSTR pszMsg)
	//
    //  Add some Status Information
	// **********************************************************************
    {
	if (!pszMsg) return;
	if (!strlen(pszMsg)) return;

	if (bErrorMsg)
		m_lErrors++;

	string szMsg = pszMsg;
	if (bErrorMsg || m_bShowDebugMsgs)
		{
	    if (!szMsg.empty())
			m_StatusMsgs.AddMsg(szMsg);
		}
	OutputDebugString(szMsg.c_str());
	}

// **************************************************************************
bool CErrorsAndDebug::DebugOn()
	//
	//  Return whether showing debug messages are on or off.
	// **********************************************************************
	{
	return m_bShowDebugMsgs;
	}

// **************************************************************************
HRESULT CErrorsAndDebug::GetTopMessage(string& szMsg)
	//
	//  Interface to return the top message off of the debug message queue.
	// **********************************************************************
	{
	HRESULT hr = S_FALSE;

	if (m_StatusMsgs.GetTopMessage(szMsg))
		hr = S_OK;

	return hr;
	}

// **************************************************************************
bool CErrorsAndDebug::CounterExists(CStreamHelper& streamHelper)
	//
	//  Returns if size > DWORD because the first DWORD size should be
	//  a counter of messages or things in the stream.
	// **********************************************************************
	{
	return (streamHelper.size() > sizeof(DWORD));
	}

// **************************************************************************
DWORD CErrorsAndDebug::GetAllDebugMessages(CStreamHelper& streamHelper)
	//
	//  Provide a standard means to pull off all of the errors and debug
	//  messages.
	// **********************************************************************
	{
	DWORD dwCnt = 0;
	DWORD dwRunningCnt = 0;
	string szMsg;
	
	if (CounterExists(streamHelper))	//  Get/Maintain the Cntr
		{
		streamHelper.Rewind();
		streamHelper >> dwRunningCnt;			//  Get the counter first
		streamHelper.SeekEnd();					//  Set Pointer back to end
		}
	else
		streamHelper << dwCnt;					//  Put the counter first

	while (S_OK == GetTopMessage(szMsg))
		{
		dwCnt++;
		streamHelper << szMsg;
		}

	dwRunningCnt += dwCnt;
	if (0 < dwCnt && CounterExists(streamHelper))
		{
		streamHelper.Rewind();
		streamHelper << dwRunningCnt;
		streamHelper.SeekEnd();					//  Set Pointer back to end
		}

	return dwCnt;
	}

// **************************************************************************
void CErrorsAndDebug::ShowDebug(bool bTF)
	//
	//  Turn on or off debug messages.
	// **********************************************************************
	{
	m_bShowDebugMsgs = bTF;
	}

extern void LogAppEvent(int logType,LPCSTR pFormat, ...);

const char LogNAME[] = "ShareView Collector";
// EVENTLOG_ERROR_TYPE             0x0001
// EVENTLOG_WARNING_TYPE           0x0002
// EVENTLOG_INFORMATION_TYPE       0x0004

void LogAppEvent(int logType,LPCSTR pFormat, ...)
{
    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;

    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    /* Get a handle to use with ReportEvent(). */
    hEventSource = RegisterEventSource(NULL, LogNAME);
    if (hEventSource != NULL)
    {
        /* Write to event log. */
        ReportEvent(hEventSource, logType, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
        DeregisterEventSource(hEventSource);
    }

}

// **************************************************************************
void CErrorsAndDebug::ErrorToEventLogFmt(LPCSTR pszFormat, ...)
	//
    //  Add some Status Information
	// **********************************************************************
    {
	if (!pszFormat) return;
	if (!strlen(pszFormat)) return;

	string szMsg;
	va_list argList;

	va_start(argList, pszFormat);
	int nRet = stringFormatV(szMsg, pszFormat, argList);
	va_end(argList);

	if (!szMsg.empty())
		LogAppEvent(EVENTLOG_ERROR_TYPE,szMsg.c_str());
	}

