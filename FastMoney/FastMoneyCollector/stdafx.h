// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0501 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0500	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

#pragma warning (disable : 4786) // Decorated names too long - no debug
#pragma warning (disable : 4244)
#pragma warning (disable : 4267)
#pragma warning (disable : 4018)
#pragma warning (disable : 4996)
#pragma warning (disable : 4793)

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlutil.h>
using namespace ATL;
//extern CComModule _Module;
#include <tchar.h>
#include <time.h>
#include <process.h>					// _beginthread, _endthread
#include <winsock2.h>
#include <comdef.h>
#include <s2locks.h>
#include <StringHelper.h>

 //STL includes
#include <map>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#include <memfile.h>
#include <windows.h>
#include "Sock.h"
//#####do correct
//#import "SymonInetClient.tlb" raw_interfaces_only raw_native_types no_namespace named_guids
//
//
//#import <MSXML3.dll> named_guids rename_namespace("MSXML")
//#import "msado15.dll" rename_namespace("ado") rename("EOF", "adoEOF")


#include "MsgBase.h"
#include <windows.h>
//	Unacoder - extern void LogAppEvent(int logType,LPCSTR pFormat, ...);
extern void LogAppEvent(int logType,LPCSTR pFormat, ...);

extern _TCHAR* Poly_Errors_Name[];
extern _TCHAR* Poly_Errors_Msg[];
