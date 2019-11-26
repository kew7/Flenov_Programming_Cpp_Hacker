// ARPApplicationDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <iphlpapi.h>


// CARPApplicationDlg dialog
class CARPApplicationDlg : public CDialog
{
// Construction
public:
	CARPApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ARPAPPLICATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DWORD MyGetIpNetTable(PMIB_IPNETTABLE& pIpNetTable, bool fOrder);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edIPAddress;
	CEdit edMacAddress;
	afx_msg void OnBnClickedButton1();
	CListBox lbMessages;
	afx_msg void OnBnClickedButton2();
	CEdit edInterface;
	afx_msg void OnBnClickedButton3();
};
