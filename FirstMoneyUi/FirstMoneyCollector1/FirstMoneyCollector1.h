// FirstMoneyCollector1.h : main header file for the FirstMoneyCollector1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFirstMoneyCollector1App
// See FirstMoneyCollector1.cpp for the implementation of this class
//

class CFirstMoneyCollector1App : public CWinApp
{
public:
	CFirstMoneyCollector1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
