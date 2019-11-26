// RenewIPAddressDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRenewIPAddressDlg dialog
class CRenewIPAddressDlg : public CDialog
{
// Construction
public:
	CRenewIPAddressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RENEWIPADDRESS_DIALOG };

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
	CListBox lAdapters;
	afx_msg void OnBnClickedButton2();
	CEdit sAdapterIndex;
	afx_msg void OnBnClickedButton3();
};
