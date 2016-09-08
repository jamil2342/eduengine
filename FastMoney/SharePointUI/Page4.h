#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CPage4 dialog
class CSharePointInbound;

class CPage4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage4)

public:
	CPage4(CSharePointInbound* pInbound = NULL);   // standard constructor
	virtual ~CPage4();
	CSharePointInbound * m_pInbound;

	bool m_chg;
	bool m_selChg;
	bool SaveItOff();
	void LoadTitles(CString listtitle, CString viewname);

// Dialog Data
	enum { IDD = IDD_PAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_viewname;
	CComboBox m_comboViewTitle;
	CListCtrl m_listfields;
	afx_msg void OnCbnSelchangeViewtitle();
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	CString m_listtitle;
};
