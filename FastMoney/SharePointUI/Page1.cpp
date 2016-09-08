// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Page1.h"
#include "bmpinfo.h"

#include "SharePointUI.h"
#include "SharePointInbound.h"

#include "svrListener.h"
#include "pubutility.h"
#include "PSDBDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage1 property page

IMPLEMENT_DYNCREATE(CPage1, CPropertyPage)

CPage1::CPage1(CSharePointInbound *pInbound) : CPropertyPage(CPage1::IDD)
, m_timeout(0)
{
	m_pInbound = pInbound;
	ASSERT(m_pInbound);

	m_chg = false;
	m_selChg = false;

	//{{AFX_DATA_INIT(CPage1)
	m_name = m_pInbound->m_base.m_name;
	m_freq = m_pInbound->m_base.m_update_interval;
	m_timeout = m_pInbound->m_base.m_update_timeout;
	//}}AFX_DATA_INIT
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 75);
	DDX_Text(pDX, IDC_FREQ, m_freq);
	DDV_MinMaxInt(pDX, m_freq, 5, 3600);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_NAME, m_editName);
	DDX_Control(pDX, IDC_FREQ, m_editFreq);
	DDX_Text(pDX, IDC_UTIMEOUT, m_timeout);
	DDV_MinMaxInt(pDX, m_timeout, 0, 32000);
	DDX_Control(pDX, IDC_UTIMEOUT, m_editTimeout);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_EN_CHANGE(IDC_FREQ, OnChangeFreq)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_UTIMEOUT, &CPage1::OnEnChangeUtimeout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers

BOOL CPage1::OnApply() 
{
	if(!SaveItOff())
		return false;

	UpdateData(false);	// in case we flipped the hi-lo vals, OR didn't delete/add pubflds
	return CPropertyPage::OnApply();
}

BOOL CPage1::OnWizardFinish() 
{
	if(!SaveItOff())
		return false;
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CPage1::SaveItOff()
{
	if(!UpdateData())
		return false;
	
	if (m_pInbound->VerifyName(m_name) == false)
	{
		m_name = oldInboundName;
		AfxMessageBox("Invalid name for collector.  You must enter a unique name for this collector.");
		m_editName.SetFocus();
		return false;
	}

	if ((m_freq < 5) || (m_freq > 3600))
		return FALSE;
	if ((m_timeout < 0) || (m_timeout > 32000))
		return FALSE;

	m_name.TrimLeft();
	m_name.TrimRight();

	if(m_name.IsEmpty())
	{
		AfxMessageBox("You must provide a name for the inbound.");
		m_editName.SetFocus();
		return false;
	}

	char temp[100];	sprintf(temp,m_name,100);
	bool bValidName = IsValidInboundName(temp);
	if (!bValidName)
	{
		AfxMessageBox("Collector names can not have \' or \" in them.");
		m_editName.SetFocus();
		return false;
	}

	if(m_name.Compare(m_pInbound->m_base.m_name))
	{
		m_chg = true;
		strncpy(m_pInbound->m_base.m_name,(LPCTSTR)m_name,75);
	}
	if(m_freq != m_pInbound->m_base.m_update_interval)
	{
		m_chg = true;
		m_pInbound->m_base.m_update_interval = m_freq;
	}
	if (m_timeout != m_pInbound->m_base.m_update_timeout)
	{
		m_chg = true;
		m_pInbound->m_base.m_update_timeout = m_timeout;
	}
	return true;
}

BOOL CPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	oldInboundName = m_name;

	if (m_pInbound->m_base.m_state == ACTIVE)
	{
		m_editName.EnableWindow(FALSE);
		m_editFreq.EnableWindow(FALSE);
		m_editTimeout.EnableWindow(FALSE);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage1::OnChangeFreq() 
{
	SetModified();	
	m_selChg = true;
}

void CPage1::OnChangeName() 
{
	SetModified();	
	m_selChg = true;
}


void CPage1::OnEnChangeUtimeout()
{
	SetModified();
	m_selChg = true;
}
