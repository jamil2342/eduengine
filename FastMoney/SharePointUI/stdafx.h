// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__F183FF65_943B_11D6_815A_0050DAB4A7C2__INCLUDED_)
#define AFX_STDAFX_H__F183FF65_943B_11D6_815A_0050DAB4A7C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#define _ATL_APARTMENT_THREADED
#define _CRT_SECURE_NO_WARNINGS

#include <afxwin.h>
#include <afxdisp.h>

#include <afxdlgs.h> // for property pages

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// STL includes
#include <map>
#include <string>
#include <vector>
#include <COMDEF.H>
#include <afxcontrolbars.h>
using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F183FF65_943B_11D6_815A_0050DAB4A7C2__INCLUDED)
