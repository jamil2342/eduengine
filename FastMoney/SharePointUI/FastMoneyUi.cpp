// FastMoneyUi.cpp : implementation file
//

#include "stdafx.h"
#include "FastMoneyUi.h"
#include "afxdialogex.h"


// CFastMoneyUi dialog

IMPLEMENT_DYNAMIC(CFastMoneyUi, CDialogEx)

CFastMoneyUi::CFastMoneyUi(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFastMoneyUi::IDD, pParent)
{

}

CFastMoneyUi::~CFastMoneyUi()
{
}

void CFastMoneyUi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFastMoneyUi, CDialogEx)
END_MESSAGE_MAP()


// CFastMoneyUi message handlers
