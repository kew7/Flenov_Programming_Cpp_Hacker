// WinSockInfoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CWinSockInfoDlg dialog
class CWinSockInfoDlg : public CDialog
{
// Construction
public:
	CWinSockInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINSOCKINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit mVersion;
	CEdit mHighVersion;
	CEdit mDescription;
	CEdit mSystemStatus;
	afx_msg void OnBnClickedButton1();
};
