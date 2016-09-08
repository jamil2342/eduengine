#pragma once
#include "afxwin.h"
#include "resource.h"

// CPage3 dialog

class CSharePointInbound;

class CPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3(CSharePointInbound* pInbound = NULL);
	virtual ~CPage3();

	CSharePointInbound * m_pInbound;

	bool m_chg;
	bool m_selChg;
	bool SaveItOff();

// Dialog Data
	enum { IDD = IDD_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_listname;
	CListBox m_listtitles;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGetlist();
	afx_msg void OnLbnSelchangeListtitles();
	virtual BOOL OnApply();
	virtual BOOL OnKillActive();
	CButton m_btnGetList;
	virtual BOOL OnSetActive();
};
