// Page4.cpp : implementation file
//

#include "stdafx.h"
#include "Page4.h"
#include "afxdialogex.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"
#include "comutil.h"

// CPage4 dialog

IMPLEMENT_DYNAMIC(CPage4, CPropertyPage)

CPage4::CPage4(CSharePointInbound* pInbound)
	: CPropertyPage(CPage4::IDD)
	, m_viewname(_T(""))
	, m_listtitle(_T(""))
{
	m_pInbound = pInbound;
	m_chg = false;
	m_selChg = false;
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VIEWTITLE, m_viewname);
	DDX_Control(pDX, IDC_VIEWTITLE, m_comboViewTitle);
	DDX_Control(pDX, IDC_FIELDS, m_listfields);
}


BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_VIEWTITLE, &CPage4::OnCbnSelchangeViewtitle)
END_MESSAGE_MAP()


// CPage4 message handlers
BOOL CPage4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	OutputDebugString("CPage4::OnInitDialog()");
	CRect rect;
	m_listfields.GetClientRect(&rect);
	int nColInterval = rect.Width()/3;
	m_listfields.InsertColumn(0, "Name", LVCFMT_LEFT, nColInterval, -1 );
	m_listfields.InsertColumn(1, "Type", LVCFMT_LEFT, nColInterval, -1 );
	m_listfields.SetExtendedStyle( m_listfields.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	if ( m_pInbound->m_base.m_state == ACTIVE )
	{
		m_comboViewTitle.EnableWindow(FALSE);
		OutputDebugString("CPage4::OnInitDialog() EnableWindow(FALSE)");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPage4::OnCbnSelchangeViewtitle()
{
	CWaitCursor wait;
	UpdateData();
	OutputDebugString("CPage4::OnCbnSelchangeViewtitle()");

	m_chg = true;
	SetModified();

	VARIANT vtFieldList;
	VARIANT vtData;
	VariantInit(&vtFieldList);
	VariantInit(&vtData);
	CString listtitle = m_pInbound->m_base.m_szListTitle;
	CString saveview = m_pInbound->m_base.m_szViewTitle;
	strncpy_s(m_pInbound->m_base.m_szViewTitle, _countof(m_pInbound->m_base.m_szViewTitle), (LPCTSTR)m_viewname,STANDARD_STRING);
	m_pInbound->ConfigureSharePoint();
	strncpy_s(m_pInbound->m_base.m_szViewTitle, _countof(m_pInbound->m_base.m_szViewTitle), (LPCTSTR)saveview,STANDARD_STRING);
	HRESULT hRes = m_pInbound->PopulateFields(listtitle, vtFieldList); 
	m_pInbound->ShowLastError(hRes);
	if (hRes != S_OK)
	{
		wait.Restore();
		return;
	}
	CString csFieldName;
	long			lLowerBound = 0;
	long			lUpperBound = 0;
	long			lCounter	= 0;
	long			idx = 0;

	m_listfields.DeleteAllItems();
	SafeArrayGetLBound(V_ARRAY(&vtFieldList), 1, &lLowerBound);
	SafeArrayGetUBound(V_ARRAY(&vtFieldList), 1, &lUpperBound);
	for (lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
	{
		SafeArrayGetElement(V_ARRAY(&vtFieldList), &lCounter, &vtData);
		if(vtData.vt == VT_BSTR && lCounter %2 == lLowerBound )
		{
			csFieldName = vtData.bstrVal;
			csFieldName = csFieldName.MakeLower();
			csFieldName.Replace("_","");
			csFieldName.Replace("x0020","");
			csFieldName.Replace("x002d","");
		}
		else
		{
			int nIndex = m_listfields.InsertItem(0 ,csFieldName);
			m_listfields.SetItemText(nIndex,1,(LPCSTR)_bstr_t(vtData.bstrVal));
		}
		VariantClear(&vtData);
	}
	wait.Restore();
}

BOOL CPage4::OnApply()
{
	OutputDebugString("CPage4::OnApply()");

	if(!SaveItOff())
		return false;

	UpdateData(false);	

	return CPropertyPage::OnApply();
}

bool CPage4::SaveItOff()
{

	OutputDebugString("CPage4::SaveItOff()");
	if(!UpdateData())
		return false;

	if(m_viewname.Compare(m_pInbound->m_base.m_szViewTitle))
	{
		OutputDebugString("CPage4::viewname changed");
		m_chg = true;
		strncpy_s(m_pInbound->m_base.m_szViewTitle, _countof(m_pInbound->m_base.m_szViewTitle), (LPCTSTR)m_viewname,STANDARD_STRING);

		FIELD_MAP_ITER iter = m_pInbound->m_colFlds.begin();
		while ( iter != m_pInbound->m_colFlds.end() )
		{
			delete (*iter).second;
			iter++;
		}
		m_pInbound->m_colFlds.clear();

		CString csFieldName;
		CString csFieldType;
		int iCnt = 0;
		for (int i =0; i < m_listfields.GetItemCount(); i++ )
		{
			csFieldName = m_listfields.GetItemText(i,0);
			iCnt += csFieldName.MakeLower().Compare("images") == 0 ? 1 : 0;
			csFieldType = m_listfields.GetItemText(i,1);
			CField* pFld = new CField(csFieldName,csFieldType);
			m_pInbound->m_colFlds[i] = pFld;
		}
		if ( iCnt >  1 )
		{
			AfxMessageBox("ShareView view cannot contain an 'images' column.");
			return false;
		}

		m_pInbound->m_base.m_fieldCount = m_pInbound->m_colFlds.size();
	}
	return true;
}

BOOL CPage4::OnSetActive()
{
	CWaitCursor wait;
	CString listtitle = m_pInbound->m_base.m_szListTitle;
	CString viewname = m_pInbound->m_base.m_szViewTitle;
	OutputDebugString("CPage4::OnSetActive() " + m_listtitle + "/" + listtitle);
	OutputDebugString("CPage4::OnSetActive() " + m_viewname + "/" + viewname);
	m_comboViewTitle.EnableWindow();
	m_comboViewTitle.ResetContent();
	if ( m_pInbound->m_base.m_state != ACTIVE )
	{
		m_viewname = viewname;
		if (!listtitle.IsEmpty())
			LoadTitles(listtitle, viewname);  //populates dropdown, not fields. Doesn't work if ACTIVE
	}
	else if (m_pInbound->m_base.m_state == ACTIVE  )
	{
		int pos = m_comboViewTitle.AddString(viewname);
		if ( pos > -1 )
		{
			OutputDebugString("CPage4::OnSetActive() " + viewname);
			m_comboViewTitle.SetCurSel(pos);
		}
		m_comboViewTitle.EnableWindow(FALSE);
	}
		
	m_listfields.DeleteAllItems();  //clear fields
	if (!viewname.IsEmpty())
	{
		FIELD_MAP_ITER it = m_pInbound->m_colFlds.begin();
		while (it != m_pInbound->m_colFlds.end())
		{
			CField* pFld = (*it).second;
			int nIndex = m_listfields.InsertItem(0 ,pFld->m_fieldName.c_str());
			m_listfields.SetItemText(nIndex,1,pFld->m_fieldType.c_str());
			it++;
		}
	}
	wait.Restore();
	return CPropertyPage::OnSetActive();
}


void CPage4::LoadTitles(CString listtitle, CString viewname)
{
	VARIANT vtFieldList;
	VARIANT vtData;
	VariantInit(&vtFieldList);
	VariantInit(&vtData);
	CString msg;

	m_pInbound->ConfigureSharePoint();
	HRESULT hr = m_pInbound->PopulateViews(listtitle, vtFieldList); 
	m_pInbound->ShowLastError(hr);
	if (hr != S_OK)
	{
		return;
	}
	msg.Format("CPage4::LoadTitles() hr = %d", hr);
	OutputDebugString(msg);
	msg.Format("CPage4::LoadTitles() viewname %s", viewname);
	OutputDebugString(msg);

	string csViewName;
	long	lLowerBound = 0;
	long	lUpperBound = 0;
	long	lCounter	= 0;
	long	idx = 0;
	int		pos = -1;

	if ( vtFieldList.vt != VT_EMPTY)
	{
		m_comboViewTitle.ResetContent();
		SafeArrayGetLBound(V_ARRAY(&vtFieldList), 1, &lLowerBound);
		SafeArrayGetUBound(V_ARRAY(&vtFieldList), 1, &lUpperBound);
		for (lCounter=lLowerBound; lCounter<=lUpperBound; lCounter++)
		{
			SafeArrayGetElement(V_ARRAY(&vtFieldList), &lCounter, &vtData);
			if(vtData.vt == VT_BSTR )
			{
				csViewName = (LPCSTR)_bstr_t(vtData.bstrVal);
				msg.Format("CPage4::LoadTitles() vtFieldList() %s",csViewName.c_str());
				OutputDebugString(msg);
				pos = m_comboViewTitle.AddString(csViewName.c_str());
				if ( pos > -1 && viewname.CompareNoCase(csViewName.c_str()) == 0 )
				{
					OutputDebugString("CPage4::m_comboViewTitle() " + viewname);
					m_comboViewTitle.SetCurSel(pos);
				}
			}
			VariantClear(&vtData);
		}
		VariantClear(&vtFieldList);
	}
	UpdateData(FALSE);
}
