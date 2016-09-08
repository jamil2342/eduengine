#if !defined(AFX_PAGE1_H__E42E1785_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
#define AFX_PAGE1_H__E42E1785_944E_11D6_815A_0050DAB4A7C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1.h : header file
//
#include "resource.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog
class CSharePointInbound;

class CPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage1)

// Construction
public:
	CPage1(CSharePointInbound * pInbound = NULL);
	~CPage1();

	CSharePointInbound * m_pInbound;

	CString oldInboundName;

	bool m_chg;
	bool m_selChg;
	BOOL SaveItOff();

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_PAGE1 };
	CString	m_name;
	int		m_freq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeFreq();
	afx_msg void OnChangeName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_editName;
	CEdit m_editFreq;
	afx_msg void OnEnChangeUtimeout();
	int m_timeout;
	CEdit m_editTimeout;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__E42E1785_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
