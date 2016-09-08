// FastMoneyUI.cpp : implementation file
//

#include "stdafx.h"
#include "FastMoneyUI.h"
#include "afxdialogex.h"
#include "MemFile.h"

// FastMoneyUI dialog

IMPLEMENT_DYNAMIC(FastMoneyUI, CDialogEx)

FastMoneyUI::FastMoneyUI(CWnd* pParent /*=NULL*/)
: CDialogEx(FastMoneyUI::IDD, pParent)
{
	
}

FastMoneyUI::~FastMoneyUI()
{
}

void FastMoneyUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FastMoneyUI, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FastMoneyUI::OnBnClickedButton1)
END_MESSAGE_MAP()


void FastMoneyUI::OnBnClickedButton1()
{

	//SetTimer(timer_id, 6000,nullptr);
	//return;
	SetDlgItemText(IDC_EDIT1, _T("http://podcast.cnbc.com/mmpodcast/fastmoney.xml"));
	CString Url; 
	GetDlgItemText(IDC_EDIT1, Url);

	_bstr_t	bsData[1];
	bsData[0] = Url;
	int Success = GetFastMoneyDataTable(bsData[0]);//GetFastMoney(bsData[0]);
	if (Success == 1)
	{
		MessageBox(_T("Data Save Successfully."), _T("Success"),
			MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		MessageBox(_T("COnnection Error."), _T("Error"),
			MB_ICONERROR | MB_OK);
	}

	return;
	// TODO: Add your control notification handler code here
}
