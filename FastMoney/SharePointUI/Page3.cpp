// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "Page3.h"
#include "afxdialogex.h"

#include "SharePointUI.h"
#include "SharePointInbound.h"

#include "svrListener.h"
#include "pubutility.h"
#include "PSDBDefines.h"

// CPage3 dialog

IMPLEMENT_DYNAMIC(CPage3, CPropertyPage)

CPage3::CPage3(CSharePointInbound* pInbound)
	: CPropertyPage(CPage3::IDD)
	, m_listname(_T(""))
{
	m_pInbound = pInbound;
	m_chg = false;
	m_selChg = false;
}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURRENT, m_listname);
	DDX_Control(pDX, IDC_LISTTITLES, m_listtitles);
	DDX_Control(pDX, IDC_GETLIST, m_btnGetList);
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
	ON_BN_CLICKED(IDC_GETLIST, &CPage3::OnBnClickedGetlist)
	ON_LBN_SELCHANGE(IDC_LISTTITLES, &CPage3::OnLbnSelchangeListtitles)
END_MESSAGE_MAP()


// CPage3 message handlers

BOOL CPage3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	OutputDebugString("CPage3::OnInitDialog()");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPage3::OnBnClickedGetlist()
{
	VARIANT vtList;
	VARIANT vtData;
	VariantInit(&vtList);
	VariantInit(&vtData);
	CString csListTitle;
	long			lLowerBound = 0;
	long			lUpperBound = 0;
	m_listtitles.ResetContent();

	CString url( m_pInbound->m_base.m_szServiceUrl);
	if (!url.IsEmpty())
	{
		CWaitCursor wait;
		m_pInbound->ConfigureSharePoint();
		HRESULT hres = m_pInbound->PopulateLists(vtList);
		wait.Restore();
		m_pInbound->ShowLastError(hres);
		if ( hres == S_OK )
		{
			if ( vtList.vt != VT_EMPTY )
			{
				SafeArrayGetLBound(V_ARRAY(&vtList), 1, &lLowerBound);
				SafeArrayGetUBound(V_ARRAY(&vtList), 1, &lUpperBound);
				for (long lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
				{
					SafeArrayGetElement(V_ARRAY(&vtList), &lCounter, &vtData);
					if(vtData.vt == VT_BSTR )
					{
						csListTitle = vtData.bstrVal;
						int nIndex = m_listtitles.AddString(csListTitle);
						VariantClear(&vtData);
					}
				}
				UpdateData(FALSE);
				SetModified();
				//m_selChg = true;
			}
		}
		VariantClear(&vtList);
	}

}

void CPage3::OnLbnSelchangeListtitles()
{
	int pos = m_listtitles.GetCurSel();
	if ( pos > -1 )
	{
		m_listtitles.GetText(pos, m_listname);
		SetModified();	
		m_selChg = true;
		UpdateData(FALSE);
	}
}

bool CPage3::SaveItOff()
{
	if(!UpdateData())
		return false;

	if (m_selChg)
	{
		OutputDebugString("CPage3::title changed");

		m_chg = true;
		strncpy_s(m_pInbound->m_base.m_szListTitle, _countof(m_pInbound->m_base.m_szListTitle), (LPCTSTR)m_listname,STANDARD_STRING);
		strncpy_s(m_pInbound->m_base.m_szViewTitle, _countof(m_pInbound->m_base.m_szViewTitle), "",STANDARD_STRING);
		m_pInbound->m_base.m_tableCount = 1;
		m_pInbound->m_base.m_fieldCount = 0;
		FIELD_MAP_ITER iter = m_pInbound->m_colFlds.begin();
		while (iter != m_pInbound->m_colFlds.end())
		{
			delete (*iter).second;
			iter++;
		}
		m_pInbound->m_colFlds.clear();
		m_selChg = false;
	}

	return true;
}

BOOL CPage3::OnApply()
{
	if(!SaveItOff())
		return false;

	UpdateData(false);	

	return CPropertyPage::OnApply();
}


BOOL CPage3::OnKillActive()
{
	if ( SaveItOff() == false )
		return FALSE;
	return CPropertyPage::OnKillActive();
}


BOOL CPage3::OnSetActive()
{
	m_listname = m_pInbound->m_base.m_szListTitle;
	UpdateData(FALSE);
	CString url(m_pInbound->m_base.m_szServiceUrl);
	m_listtitles.EnableWindow(FALSE);
	m_btnGetList.EnableWindow(FALSE);

	if (!url.IsEmpty() && m_pInbound->m_base.m_state != ACTIVE)
	{
		m_listtitles.EnableWindow(TRUE);
		m_btnGetList.EnableWindow(TRUE);
		OnBnClickedGetlist();
	}
	return CPropertyPage::OnSetActive();
}
