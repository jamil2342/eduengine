// Wizzard1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Wizzard1.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"
#include "PSDBDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizzard1 property page

IMPLEMENT_DYNCREATE(CWizzard1, CPropertyPage)

CWizzard1::CWizzard1(CSharePointInbound *pInboundObj) : CPropertyPage(CWizzard1::IDD)
{
	m_pObj = pInboundObj;
	//{{AFX_DATA_INIT(CWizzard1)
	m_name = _T("");
	//}}AFX_DATA_INIT
}

CWizzard1::~CWizzard1()
{
}

void CWizzard1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizzard1)
	DDX_Control(pDX, IDC_NAME, mc_name);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 75);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizzard1, CPropertyPage)
	//{{AFX_MSG_MAP(CWizzard1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizzard1 message handlers

BOOL CWizzard1::OnSetActive() 
{
	BOOL res = CPropertyPage::OnSetActive();
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);	
	
	return CPropertyPage::OnSetActive();
}

LRESULT CWizzard1::OnWizardNext() 
{
	UpdateData();	
	m_name.TrimLeft();
	m_name.TrimRight();

	char temp[100];	sprintf(temp,m_name,100);

	bool bValidName = IsValidInboundName(temp);
	if (!bValidName)
	{
		AfxMessageBox("Collector names can not have \' or \" in them.");
		return -1;
	}

	CString cleanname = StripBadChars(temp, false);
	cleanname.TrimLeft();
	cleanname.TrimRight();
	
	if(m_name.IsEmpty())
	{
		AfxMessageBox(IDS_EMPTY_DESC);
		mc_name.SetFocus();
		return -1;
	}
	if(cleanname.IsEmpty())
	{
		AfxMessageBox("A valid name must consist of alpha characters.");
		return -1;
	}


	if(m_pObj->VerifyName(m_name,true) == false)
	{
		AfxMessageBox("Invalid name for collector.  You must enter a unique name for this collector.");
		return -1;
	}
	
	strncpy(m_pObj->m_base.m_name , (LPCTSTR)m_name,STANDARD_STRING);
	strncpy(m_pObj->m_base.m_collectorTypeName, (LPCTSTR)cleanname, STANDARD_STRING);

	
	return CPropertyPage::OnWizardNext();
}

BOOL CWizzard1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if(m_pObj)
	{
		m_name = m_pObj->m_base.m_name;
		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
