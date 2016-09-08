// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "Page2.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"

// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2(CSharePointInbound* pInbound)
	: CPropertyPage(CPage2::IDD)

	, m_url(_T(""))
	, m_authmode(_T(""))
	, m_username(_T(""))
	, m_password(_T(""))
	, m_authtype(_T(""))
	, m_fuagauth(_T(""))
	, m_proxyurl(_T(""))
	, m_proxyuser(_T(""))
	, m_proxypswd(_T(""))
	, m_useproxy(FALSE)
{
	m_pInbound = pInbound;
	ASSERT(m_pInbound);
	m_chg = false;
	m_selChg = false;
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_URL, m_url);
	DDV_MaxChars(pDX, m_url, MAX_URL_SIZE);
	DDX_Text(pDX, IDC_AUTHMODE, m_authmode);
	DDV_MaxChars(pDX, m_authmode, 20);
	DDX_Text(pDX, IDC_AUTHTYPE, m_authtype);
	DDV_MaxChars(pDX, m_authtype, 20);
	DDX_Text(pDX, IDC_FUAGAUTH, m_fuagauth);
	DDV_MaxChars(pDX, m_fuagauth, 20);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, STANDARD_STRING);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, STANDARD_STRING);
	DDX_Control(pDX, IDC_AUTHMODE, m_comboAuthMode);
	DDX_Control(pDX, IDC_AUTHTYPE, m_comboAuthType);
	DDX_Control(pDX, IDC_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_URL, m_editUrl);
	DDX_Control(pDX, IDC_FUAGAUTH, m_comboFuagAuth);
	DDX_Text(pDX, IDC_PROXYURL, m_proxyurl);
	DDX_Text(pDX, IDC_PROXYUSER, m_proxyuser);
	DDX_Text(pDX, IDC_PROXYPSWD, m_proxypswd);
	DDX_Check(pDX, IDC_CHECK1, m_useproxy);
}

BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	ON_EN_CHANGE(IDC_URL, &CPage2::OnEnChangeUrl)
	ON_CBN_SELCHANGE(IDC_AUTHMODE, &CPage2::OnCbnSelchangeAuthmode)
	ON_BN_CLICKED(IDC_RADIO1, &CPage2::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPage2::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_USERNAME, &CPage2::OnEnChangeUsername)
	ON_EN_CHANGE(IDC_PASSWORD, &CPage2::OnEnChangePassword)
	ON_CBN_SELCHANGE(IDC_AUTHTYPE, &CPage2::OnCbnSelchangeAuthtype)
	ON_CBN_SELCHANGE(IDC_FUAGAUTH, &CPage2::OnCbnSelchangeFuagauth)
	ON_EN_CHANGE(IDC_PROXYURL, &CPage2::OnEnChangeProxyurl)
	ON_EN_CHANGE(IDC_PROXYUSER, &CPage2::OnEnChangeProxyuser)
	ON_EN_CHANGE(IDC_PROXYPSWD, &CPage2::OnEnChangeProxypswd)
	ON_BN_CLICKED(IDC_CHECK1, &CPage2::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CPage2 message handlers

void CPage2::OnEnChangeUrl()
{
	SetModified();	
	m_selChg = true;
}

void CPage2::OnCbnSelchangeAuthmode()
{
	SetModified();	
	m_selChg = true;
	int pos = m_comboAuthMode.GetCurSel();
	if ( pos == 2 ) // not anon
	{
		m_editUserName.EnableWindow(FALSE);
		m_editPassword.EnableWindow(FALSE);
	}
	else
	{
		m_editUserName.EnableWindow();
		m_editPassword.EnableWindow();
	}
	if ( pos == 0 )
		m_comboAuthType.EnableWindow();
	else
	{
		m_comboAuthType.SetCurSel(0);
		m_comboAuthType.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CPage2::OnCbnSelchangeFuagauth()
{
	SetModified();	
	m_selChg = true;
}

void CPage2::OnCbnSelchangeAuthtype()
{
	SetModified();	
	m_selChg = true;
}

void CPage2::OnEnChangeUsername()
{
	SetModified();	
	m_selChg = true;
}

void CPage2::OnEnChangePassword()
{
	SetModified();	
	m_selChg = true;
}

void CPage2::OnBnClickedRadio1()
{
	UpdateData();
	m_comboAuthMode.EnableWindow();
	m_comboFuagAuth.EnableWindow(FALSE);
	m_editUserName.EnableWindow(FALSE);
	m_editPassword.EnableWindow(FALSE);
	int pos = m_comboAuthMode.GetCurSel();
	if ( pos != 2 ) // not anon
	{
		m_editUserName.EnableWindow();
		m_editPassword.EnableWindow();
	}
	if ( pos == 0 )
		m_comboAuthType.EnableWindow();
	else
		m_comboAuthType.EnableWindow(FALSE);

	UpdateData(FALSE);
	SetModified();	
	m_selChg = true;
}


void CPage2::OnBnClickedRadio2()
{
	UpdateData();
	int pos = m_comboAuthMode.SetCurSel(0); // Only 'Default' is valid
	m_authmode = AUTH_MODE[0];
	m_comboAuthMode.EnableWindow(FALSE);
	m_comboAuthType.EnableWindow();
	m_comboFuagAuth.EnableWindow();
	m_editUserName.EnableWindow();
	m_editPassword.EnableWindow();
	pos = m_comboFuagAuth.GetCurSel();
	if ( pos == - 1)
	{
		m_comboFuagAuth.SetCurSel(0);
		SetModified();
	}
	UpdateData(FALSE);
	m_selChg = true;
}

BOOL CPage2::OnApply()
{
	if(!SaveItOff())
		return false;

	UpdateData(false);

	return CPropertyPage::OnApply();
}

BOOL CPage2::OnKillActive()
{
	if ( SaveItOff() == false )
		return FALSE;

	return CPropertyPage::OnKillActive();
}

bool CPage2::SaveItOff()
{
	if(!UpdateData())
		return false;

	int pos = m_comboAuthMode.GetCurSel();
	if ( pos > -1 && m_comboAuthMode.IsWindowEnabled())
	{
		if ( pos == 2) // anon
		{
			if ( strlen(m_pInbound->m_base.m_szPassword) > 0 )
			{
				memset(m_pInbound->m_base.m_szPassword,0,STANDARD_STRING);
				m_password = "";
				m_chg = true;
			}
			if ( strlen(m_pInbound->m_base.m_szUser) > 0 )
			{
				memset(m_pInbound->m_base.m_szUser,0,STANDARD_STRING);
				m_username = "";
				m_chg = true;
			}
		}
		if ( m_pInbound->m_base.m_authmode != pos )
		{
			m_pInbound->m_base.m_authmode = pos;
			m_chg = true;
		}
	}

	if(m_url.Compare(m_pInbound->m_base.m_szServiceUrl))
	{
		if ( IsValidURL(NULL, _bstr_t(m_url), 0) == S_OK ) // if url changed, everything wiped out
		{
			m_chg = true;
			strncpy_s(m_pInbound->m_base.m_szServiceUrl, _countof(m_pInbound->m_base.m_szServiceUrl), (LPCTSTR)m_url,MAX_URL_SIZE);
			strncpy_s(m_pInbound->m_base.m_szListTitle, _countof(m_pInbound->m_base.m_szListTitle), "", STANDARD_STRING);
			strncpy_s(m_pInbound->m_base.m_szViewTitle, _countof(m_pInbound->m_base.m_szViewTitle), "", STANDARD_STRING);
			m_pInbound->m_base.m_tableCount = 0;
			m_pInbound->m_base.m_fieldCount = 0;
			FIELD_MAP_ITER iter = m_pInbound->m_colFlds.begin();
			while (iter != m_pInbound->m_colFlds.end())
			{
				delete (*iter).second;
				iter++;
			}
			m_pInbound->m_colFlds.clear();
		}
		else
		{
			AfxMessageBox("Enter a valid URL.");
			m_editUrl.SetFocus();
			return false;
		}
	}

	if (m_comboFuagAuth.IsWindowEnabled() )
	{
		if (m_fuagauth.Compare(m_pInbound->m_base.m_szFuagAuth))
		{
			m_chg = true;
			strncpy_s(m_pInbound->m_base.m_szFuagAuth, _countof(m_pInbound->m_base.m_szFuagAuth), (LPCTSTR)m_fuagauth, STANDARD_STRING);
		}
		else if (m_fuagauth.IsEmpty() )
		{
			AfxMessageBox("Please select or enter a value.");
			m_comboFuagAuth.SetFocus();
			return false;		
		}
		pos = m_comboAuthMode.GetCurSel();
		if ( m_pInbound->m_base.m_authmode != pos )
		{
			m_pInbound->m_base.m_authmode = pos;
			m_chg = true;
		}
	}
	else
	{
		if ( strlen(m_pInbound->m_base.m_szFuagAuth) > 0 )
		{
			m_chg = true;
			memset(m_pInbound->m_base.m_szFuagAuth, 0, STANDARD_STRING);
		}
	}
	if(m_username.Compare(m_pInbound->m_base.m_szUser))
	{
		m_chg = true;
		strncpy_s(m_pInbound->m_base.m_szUser, _countof(m_pInbound->m_base.m_szUser), (LPCTSTR)m_username,STANDARD_STRING);
	}
	if(m_password.Compare(m_pInbound->m_base.m_szPassword))
	{
		m_chg = true;
		strncpy_s(m_pInbound->m_base.m_szPassword, _countof(m_pInbound->m_base.m_szPassword), (LPCTSTR)m_password,STANDARD_STRING);
	}
	if(m_authtype.Compare(m_pInbound->m_base.m_szAuthType))
	{
		CString aut = m_authtype.Compare("None") == 0 ? "" : m_authtype;
		if ( aut.Compare(m_pInbound->m_base.m_szAuthType))
		{
			strncpy_s(m_pInbound->m_base.m_szAuthType, _countof(m_pInbound->m_base.m_szAuthType), (LPCTSTR)aut,STANDARD_STRING);
			m_chg = true;
		}
	}
	if (m_proxyurl.Compare(m_pInbound->m_base.m_szProxy))
	{
		strncpy_s(m_pInbound->m_base.m_szProxy, _countof(m_pInbound->m_base.m_szProxy), (LPCTSTR)m_proxyurl, MAX_URL_SIZE);
		m_chg = true;
	}
	if (m_proxyuser.Compare(m_pInbound->m_base.m_szProxyUser))
	{
		strncpy_s(m_pInbound->m_base.m_szProxyUser, _countof(m_pInbound->m_base.m_szProxyUser), (LPCTSTR)m_proxyuser, STANDARD_STRING);
		m_chg = true;
	}
	if (m_proxypswd.Compare(m_pInbound->m_base.m_szProxyPassword))
	{
		strncpy_s(m_pInbound->m_base.m_szProxyPassword, _countof(m_pInbound->m_base.m_szProxyPassword), (LPCTSTR)m_proxypswd, STANDARD_STRING);
		m_chg = true;
	}
	if (m_useproxy != m_pInbound->m_base.m_bUseProxy)
	{
		m_pInbound->m_base.m_bUseProxy = m_useproxy;
		m_chg = true;
	}

	UpdateData(FALSE);
	
	if (strlen(m_pInbound->m_base.m_szFuagAuth) > 0  || m_pInbound->m_base.m_authmode == 1 )
		if ( strlen(m_pInbound->m_base.m_szPassword) == 0 || strlen(m_pInbound->m_base.m_szUser) == 0  )
		{
			AfxMessageBox("Username and password are required based on your authentication selections.");
			if ( strlen(m_pInbound->m_base.m_szUser) == 0)
				m_editUserName.SetFocus();
			else
				m_editPassword.SetFocus();
			return false;
		}
	
	if ( m_chg )
		m_pInbound->ConfigureSharePoint();
	return TRUE;
}

BOOL CPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_url = m_pInbound->m_base.m_szServiceUrl;
	m_authmode = AUTH_MODE[m_pInbound->m_base.m_authmode];
	m_comboAuthMode.SetCurSel(m_pInbound->m_base.m_authmode);
	m_fuagauth = m_pInbound->m_base.m_szFuagAuth;
	m_authtype = strlen(m_pInbound->m_base.m_szAuthType) == 0 ? "None" : m_pInbound->m_base.m_szAuthType;
	m_comboAuthType.SelectString(0,m_authtype);

	m_proxyuser = m_pInbound->m_base.m_szProxyUser;
	m_proxypswd = m_pInbound->m_base.m_szProxyPassword;
	m_proxyurl = m_pInbound->m_base.m_szProxy;
	m_useproxy = m_pInbound->m_base.m_bUseProxy;
	//m_bBypass = m_pInbound->m_base.m_bBypassProxy;
	//m_proxyauthtype = m_pInbound->m_base.m_szProxyAuthType;

	if ( m_pInbound->m_base.m_authmode == 0 )
		m_comboAuthType.EnableWindow();
	else
		m_comboAuthType.EnableWindow(FALSE);

	if ( m_fuagauth.IsEmpty() )
	{
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		m_comboFuagAuth.EnableWindow(FALSE);
	}
	else
	{
		m_comboAuthMode.EnableWindow(FALSE);
		m_comboAuthType.EnableWindow();
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
		if ( m_fuagauth.Compare(FUAG_AUTH[0]) == 0 )
		{
			m_comboFuagAuth.SetCurSel(0);
			m_comboAuthMode.EnableWindow(FALSE);
		}
		else if ( m_fuagauth.Compare(FUAG_AUTH[1]) == 0 )
		{
			m_comboFuagAuth.SetCurSel(1);
			m_comboAuthMode.EnableWindow(FALSE);
		}
	}

	m_username = m_pInbound->m_base.m_szUser;
	m_password = m_pInbound->m_base.m_szPassword;
	UpdateData(FALSE);
	OnBnClickedCheck1();

	if (m_pInbound->m_base.m_state == ACTIVE)
	{
		m_editUrl.EnableWindow(FALSE);
		m_editUserName.EnableWindow(FALSE);
		m_editPassword.EnableWindow(FALSE);
		m_comboAuthMode.EnableWindow(FALSE);
		m_comboAuthType.EnableWindow(FALSE);
		m_comboFuagAuth.EnableWindow(FALSE);
		Activate(FALSE);
		CButton* btn = (CButton*)GetDlgItem(IDC_RADIO1);
		btn->EnableWindow(FALSE);
		btn = (CButton*)GetDlgItem(IDC_RADIO2);
		btn->EnableWindow(FALSE);
		btn = (CButton*)GetDlgItem(IDC_CHECK1);
		btn->EnableWindow(FALSE);
	}
	else
	{
		if ( m_pInbound->m_base.m_authmode == 2 )
		{
			m_editUserName.EnableWindow(FALSE);
			m_editPassword.EnableWindow(FALSE);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPage2::OnEnChangeProxyurl()
{
	SetModified();
	m_selChg = true;
}


void CPage2::OnEnChangeProxyuser()
{
	SetModified();
	m_selChg = true;
}


void CPage2::OnEnChangeProxypswd()
{
	SetModified();
	m_selChg = true;
}


void CPage2::OnBnClickedCheck1()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	Activate(pBtn->GetCheck());
	SetModified();
	m_selChg = true;
}

void CPage2::Activate(bool bActivate)
{
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_PROXYURL);
	CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_PROXYUSER);
	CEdit* pEdit3 = (CEdit*)GetDlgItem(IDC_PROXYPSWD);
	pEdit1->EnableWindow(bActivate);
	pEdit2->EnableWindow(bActivate);
	pEdit3->EnableWindow(bActivate);
}