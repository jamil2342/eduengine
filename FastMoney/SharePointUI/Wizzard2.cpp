// Wizzard2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"
#include "Wizzard2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizzard2 property page

IMPLEMENT_DYNCREATE(CWizzard2, CPropertyPage)

CWizzard2::CWizzard2(CSharePointInbound* pObj) : CPropertyPage(CWizzard2::IDD)
, m_timeout(0)
{
	m_pObj = pObj;
	//{{AFX_DATA_INIT(CWizzard2)
	m_freq = 60;
	//}}AFX_DATA_INIT
}

CWizzard2::~CWizzard2()
{
}

void CWizzard2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizzard2)
	DDX_Control(pDX, IDC_FREQ, m_freqStr);
	DDX_Text(pDX, IDC_FREQ, m_freq);
	DDV_MinMaxInt(pDX, m_freq, 5, 3600);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_UTIMEOUT, m_timeout);
	DDV_MinMaxUInt(pDX, m_timeout, 0, 32000);
}


BEGIN_MESSAGE_MAP(CWizzard2, CPropertyPage)
	//{{AFX_MSG_MAP(CWizzard2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizzard2 message handlers

LRESULT CWizzard2::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardBack();
}

BOOL CWizzard2::OnWizardFinish() 
{
	UpdateData();
	if ((m_freq < 5) || (m_freq > 3600))
		return FALSE;
	if ((m_timeout < 0) || (m_timeout > 32000))
		return FALSE;

	m_pObj->m_base.m_update_interval = m_freq;
	m_pObj->m_base.m_update_timeout = m_timeout;

	return CPropertyPage::OnWizardFinish();
}

BOOL CWizzard2::OnSetActive() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK|PSWIZB_FINISH);	
	return CPropertyPage::OnSetActive();
}

BOOL CWizzard2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if(m_pObj)
	{
		m_freq = m_pObj->m_base.m_update_interval;
		m_timeout = m_pObj->m_base.m_update_timeout;
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
