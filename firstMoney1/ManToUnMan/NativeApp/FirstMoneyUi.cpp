// FirstMoneyUi.cpp : implementation file
//

#include "stdafx.h"
#include "FirstMoneyUi.h"
#include "afxdialogex.h"
#include "NativeInterface.h"

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

//
//void ReceivedFloatArray(float values[], int length)
//{
//	for (int i = 0; i < length; i++)
//	{
//		printf("Received float value %f \n", values[i]);
//	}
//}
void FirstMoneyUi::OnBnClickedButton1()
{

	int SumValue = 0;
	char retValue = ' ';
	SumValue = SumFromCSharp(4, 5);
	//printf("Sum calculated in C#: %d \n", SumValue);

	//UnManagedStudent student = GetStudent();
	//printf("Name of the student received from C# %s \n", student.name);

	//GetFloatArrayFromCSharp(&ReceivedFloatArray);

	//printf("Enter any key to Terminate");
	//scanf("%c", &retValue);
	return ;
	// TODO: Add your control notification handler code here
}
