#pragma once
#include "resource.h"

// FastMoneyUI dialog

class FastMoneyUI : public CDialogEx
{
	DECLARE_DYNAMIC(FastMoneyUI)

public:
	FastMoneyUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~FastMoneyUI();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
