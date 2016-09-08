#pragma once
#include "afxwin.h"
#include "resource.h"


// CPage2 dialog

class CSharePointInbound;

class CPage2 : public CPropertyPage

{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CSharePointInbound* pInbound = NULL);
	virtual ~CPage2();

	CSharePointInbound * m_pInbound;

	bool m_chg;
	bool m_selChg;
	bool SaveItOff();
	bool GetCertFileName(CString &szNewFile);

// Dialog Data
	enum { IDD = IDD_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_url;
	CString m_authmode;
	CString m_username;
	CString m_password;
	CString m_authtype;
	CComboBox m_comboAuthMode;
	CComboBox m_comboAuthType;
	CEdit m_editUserName;
	CEdit m_editPassword;
	CComboBox m_comboFuagAuth;
	CString m_fuagauth;
	CEdit m_editUrl;
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
	virtual BOOL OnKillActive();
	void Activate(bool bActivate);
	afx_msg void OnEnChangeUrl();
	afx_msg void OnCbnSelchangeAuthmode();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeUsername();
	afx_msg void OnEnChangePassword();
	afx_msg void OnCbnSelchangeAuthtype();
	afx_msg void OnCbnSelchangeFuagauth();
	CString m_proxyurl;
	CString m_proxyuser;
	CString m_proxypswd;
	afx_msg void OnEnChangeProxyurl();
	afx_msg void OnEnChangeProxyuser();
	afx_msg void OnEnChangeProxypswd();
	BOOL m_useproxy;
	afx_msg void OnBnClickedCheck1();
};
