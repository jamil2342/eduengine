#pragma once

#include "resource.h"
#include "afxwin.h"

class CSharePointInbound;
// CDiagnosticDlg dialog

class CDiagnosticDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CDiagnosticDlg)

public:
	CDiagnosticDlg(CSharePointInbound *pInbound=NULL);   // standard constructor
	virtual ~CDiagnosticDlg();

	CSharePointInbound* m_pInbound;
	UINT m_nDebugMsgTimer;
	bool GetFileNameToWriteTo( CString &szNewFile );
	HRESULT SaveListToFile();
	void StartTimer( BOOL bEnable );
	void ShowMsgInList( LPCTSTR pszMsg );
	void GetAndShowDebugMsgs();
	CString m_szDebugFile;

// Dialog Data
	enum { IDD = IDD_DIAGNOSTICS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedClear();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_listMessages;
};
