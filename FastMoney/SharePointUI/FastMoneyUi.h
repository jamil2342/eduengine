#pragma once

#include "resource.h"
// CFastMoneyUi dialog

class CFastMoneyUi : public CDialogEx
{
	DECLARE_DYNAMIC(CFastMoneyUi)

public:
	CFastMoneyUi(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFastMoneyUi();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
