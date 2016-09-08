// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#pragma warning( default: 4996 )


#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <atlbase.h>

using namespace ATL;

//========= polyhedra stuff below =================
//#include "constants.h"	// for polyhedra errors
extern const char * Poly_Errors_Msg[];
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

#include <atlcom.h>
#include <atlstr.h>

#include <bitset>
#include <time.h>
#include <process.h>							// _beginthread, _endthread
#include <winsock2.h>
#include <comdef.h>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>
using namespace std;

#include <memfile.h>
#include <s2locks.h>
#include <StringHelper.h>
#include "Sock.h"
#pragma warning(disable:4786)

#include "../SharePointAdapter/ISharePointAdapter.h"

extern void LogEvent(int logType,LPCSTR pFormat, ...);
