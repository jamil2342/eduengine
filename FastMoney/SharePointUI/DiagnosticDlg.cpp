// DiagnosticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DiagnosticDlg.h"
#include "SharePointUI.h"
#include "SharePointInbound.h"
#include "pubutility.h"
#include <memfile.h>

// CDiagnosticDlg dialog

IMPLEMENT_DYNAMIC(CDiagnosticDlg, CPropertyPage)

CDiagnosticDlg::CDiagnosticDlg(CSharePointInbound* pInbound)
	: CPropertyPage(CDiagnosticDlg::IDD)
{
	m_pInbound = pInbound;
}

CDiagnosticDlg::~CDiagnosticDlg()
{
}

void CDiagnosticDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESSAGELIST, m_listMessages);
}


BEGIN_MESSAGE_MAP(CDiagnosticDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_SAVEFILE, &CDiagnosticDlg::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_CLEAR, &CDiagnosticDlg::OnBnClickedClear)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CDiagnosticDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_listMessages.SetHorizontalExtent(1500);
	m_pInbound->CaptureDebugMessages(TRUE);
	StartTimer(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDiagnosticDlg::OnBnClickedSavefile()
{
	CString szNewFile;

	szNewFile = m_szDebugFile;
	if (GetFileNameToWriteTo(szNewFile))
	{
		m_szDebugFile = szNewFile;
		HRESULT hr = SaveListToFile();
		if (hr == S_OK)
		{
			CString szMsg;
			szMsg.Format("Saved List to File %s.", szNewFile );
			MessageBox((LPCTSTR)szMsg, "Saved Debug Data", MB_ICONINFORMATION);
		}
		else if ( hr == S_FALSE )
		{
			CString szMsg;
			szMsg.Format("Nothing to save. File %s not saved.", szNewFile );
			MessageBox((LPCTSTR)szMsg, "File Error", MB_ICONEXCLAMATION);
		}
		else
		{
			CString szMsg;
			szMsg.Format("ERROR %ld: Unable to save to file. Make sure file is not read-only.", hr);
			MessageBox((LPCTSTR)szMsg, "File Error", MB_ICONEXCLAMATION);
		}
	}
}

void CDiagnosticDlg::OnBnClickedClear()
{
	m_listMessages.ResetContent();
}


void CDiagnosticDlg::OnDestroy()
{
	CPropertyPage::OnDestroy();

	StartTimer(FALSE);

	if (m_pInbound)
	{
		m_pInbound->CaptureDebugMessages(FALSE);
	}
	
}


void CDiagnosticDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nDebugMsgTimer)
	{
		GetAndShowDebugMsgs();
	}
	CPropertyPage::OnTimer(nIDEvent);
}


void CDiagnosticDlg::GetAndShowDebugMsgs()
{
	CStreamHelper streamHelper;
	if (!streamHelper.GoodStream()) return;

	string szMsg;
	VARIANT vtFillThis;

	VariantInit(&vtFillThis);
	if (m_pInbound)
		if (!SUCCEEDED(m_pInbound->DoCustomIF(GetDebugMsgs, &vtFillThis)))
			return;

	if (vtFillThis.vt == (VT_UI1 | VT_ARRAY))
	{
		int nTTL = 0;
		int nCount = 0;

		GetSizeAndCount(vtFillThis, &nTTL, &nCount);
		if (nTTL > 0)
		{
			//  Get data to Stream the IStream way
			PUCHAR ptr;
			SafeArrayAccessData(vtFillThis.parray, (LPVOID*)&ptr);
			HRESULT hRet = streamHelper.TransferData(ptr, nTTL, false);
			SafeArrayUnaccessData(vtFillThis.parray);

			if (hRet == S_OK && streamHelper.size() > sizeof(nTTL))	// ALWAYS has a size!!
			{
				long lTTL = 0;
				streamHelper.Rewind();			//  Get to beginning of Stream
				streamHelper >> lTTL;			//  Put the counter first
				for (long lCnt = 0; lCnt < lTTL; lCnt++)
				{
					streamHelper >> szMsg;
					if (!szMsg.empty())
					{
						ShowMsgInList(szMsg.c_str());
					}
				}
			}
		}
	}
	VariantClear(&vtFillThis);

	DWORD dwMsgCnt = m_pInbound->m_StatusMsgs.count();
	//stringFormat(szMsg, "Status Msg Count = %ld", dwMsgCnt);
	//ShowMsgInList(szMsg.c_str());
	if (dwMsgCnt)
	{
		while (S_OK == m_pInbound->GetTopMessage(szMsg))
			ShowMsgInList(szMsg.c_str());
	}

}

void CDiagnosticDlg::ShowMsgInList( LPCTSTR pszMsg )
{
	if (!pszMsg) return;

	//  NOTE:  Put it in a few lines because it would loop because it
	//         didn't get an indication of < 1000 quick enough.	
	int nCnt = 0;
	while (1)
	{
		nCnt = m_listMessages.GetCount();
		if (nCnt < 1000) break;
		m_listMessages.DeleteString(0);
	}

	if (strlen(pszMsg))
		m_listMessages.AddString(pszMsg);
	nCnt = m_listMessages.GetCount();
	if (nCnt > 0)
		m_listMessages.SetCurSel(nCnt - 1);

}

void CDiagnosticDlg::StartTimer(BOOL bEnable)
{
	UINT lSecs = 2000;							// 2 Sec Status Time

	if (m_nDebugMsgTimer && m_hWnd) KillTimer(m_nDebugMsgTimer);
	
	if (TRUE == bEnable)
		m_nDebugMsgTimer = SetTimer(1, lSecs, NULL);

}

#define MAX_5_MEG 5000000

HRESULT CDiagnosticDlg::SaveListToFile()
{
	HRESULT hr = S_FALSE;
	memfile mf;
	mf.set_max_size(MAX_5_MEG);					// 5 meg Max
	CString szItemText;

	int nTTL = m_listMessages.GetCount();
	for (int nCnt = 0; nCnt < nTTL; nCnt++)
	{
		m_listMessages.GetText(nCnt, szItemText);
		mf << (LPCTSTR)szItemText;
		mf << "\r\n";
	}
	if (mf.size())
		hr = mf.write_file((LPCTSTR)m_szDebugFile, 0, -1, -1, NULL, OPEN_ALWAYS);

	return hr;


}

bool CDiagnosticDlg::GetFileNameToWriteTo(CString &szNewFile)
{
	bool bRet = false;
	CString szFilename, szFilter, szStartFile;

   	// Dlg doesn't show if right character is any of these
	szStartFile = szNewFile;

	szFilter = _T("Text Files (*.txt)|*.txt||");

	CFileDialog dlg(TRUE, "txt", szStartFile, 
					OFN_HIDEREADONLY| OFN_PATHMUSTEXIST, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		szFilename = dlg.m_ofn.lpstrFile;
		szFilename.TrimLeft();
		szFilename.TrimRight();
		if (szFilename.GetLength())				//  Must exist at this point
		{
			szNewFile = szFilename;
			bRet = true;
		}
		else
			MessageBox("ERROR:  Invalid file name entered.  Unable to save to file.",
						"File Name Error", MB_ICONEXCLAMATION);
	}
	return bRet;

}
