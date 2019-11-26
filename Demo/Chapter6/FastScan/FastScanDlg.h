// FastScanDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CFastScanDlg dialog
class CFastScanDlg : public CDialog
{
// Construction
public:
	CFastScanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FASTSCAN_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CEdit chStartPort;
	CEdit chEndPort;
	CEdit chHostName;
	CListBox m_PortList;
};
