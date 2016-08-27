// FirstMoneyUi.cpp : implementation file
//

#include "stdafx.h"
#include "FirstMoneyUi.h"
#include "afxdialogex.h"


// FirstMoneyUi dialog

IMPLEMENT_DYNAMIC(FirstMoneyUi, CDialogEx)

FirstMoneyUi::FirstMoneyUi(CWnd* pParent /*=NULL*/)
	: CDialogEx(FirstMoneyUi::IDD, pParent)
{

}

FirstMoneyUi::~FirstMoneyUi()
{
}

void FirstMoneyUi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FirstMoneyUi, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FirstMoneyUi::OnBnClickedButton1)
END_MESSAGE_MAP()


// FirstMoneyUi message handlers


void FirstMoneyUi::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
