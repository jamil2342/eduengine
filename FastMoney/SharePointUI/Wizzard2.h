#if !defined(AFX_WIZZARD2_H__E42E1784_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
#define AFX_WIZZARD2_H__E42E1784_944E_11D6_815A_0050DAB4A7C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizzard2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizzard2 dialog
class CSharePointInbound;

class CWizzard2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizzard2)

// Construction
public:
	CWizzard2(CSharePointInbound *pObj = NULL);
	~CWizzard2();

	CSharePointInbound *m_pObj;

// Dialog Data
	//{{AFX_DATA(CWizzard2)
	enum { IDD = IDD_WIZARD2 };
	CEdit	m_freqStr;
	short	m_freq;
	short	m_timeout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizzard2)
	public:
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizzard2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZZARD2_H__E42E1784_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
