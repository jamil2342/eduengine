#pragma once
#include "resource.h"

// FirstMoneyUi dialog

class FirstMoneyUi : public CDialogEx
{
	DECLARE_DYNAMIC(FirstMoneyUi)

public:
	FirstMoneyUi(CWnd* pParent = NULL);   // standard constructor
	virtual ~FirstMoneyUi();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
