#pragma once
#include "resource.h"
#include "MemFile.h"
// FastMoneyUI dialog

class FastMoneyUI : public CDialogEx
{
	DECLARE_DYNAMIC(FastMoneyUI)
	int timer_id = 1000;
public:
	FastMoneyUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~FastMoneyUI();
	void OnTimer(UINT_PTR nIdEvent)
	{
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
	
	}
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
