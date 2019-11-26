// COMportDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCOMportDlg dialog
class CCOMportDlg : public CDialog
{
// Construction
public:
	CCOMportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMPORT_DIALOG };

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
	CComboBox cbPorts;
	HANDLE hThread;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOpenportButton();
	CListBox lLogList;
	afx_msg void OnBnClickedSendcommandButton();
	CEdit eSendCommand;
};
