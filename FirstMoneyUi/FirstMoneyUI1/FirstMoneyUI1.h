
// FirstMoneyUI1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFirstMoneyUI1App:
// See FirstMoneyUI1.cpp for the implementation of this class
//

class CFirstMoneyUI1App : public CWinApp
{
public:
	CFirstMoneyUI1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFirstMoneyUI1App theApp;