#if !defined(AFX_WIZZARD1_H__E42E1783_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
#define AFX_WIZZARD1_H__E42E1783_944E_11D6_815A_0050DAB4A7C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizzard1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizzard1 dialog
class CSharePointInbound;
extern _bstr_t	bstrEmpty;

class CWizzard1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizzard1)

// Construction
public:
	CWizzard1(CSharePointInbound * pObj = NULL);
	~CWizzard1();

	CSharePointInbound *m_pObj;

// Dialog Data
	//{{AFX_DATA(CWizzard1)
	enum { IDD = IDD_WIZARD1 };
	CEdit	mc_name;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizzard1)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizzard1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZZARD1_H__E42E1783_944E_11D6_815A_0050DAB4A7C2__INCLUDED_)
