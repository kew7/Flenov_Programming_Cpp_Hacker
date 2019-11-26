// ChangeIPAddressDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CChangeIPAddressDlg dialog
class CChangeIPAddressDlg : public CDialog
{
// Construction
public:
	CChangeIPAddressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHANGEIPADDRESS_DIALOG };

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
	CEdit eIPEdit;
	CEdit eMaskEdit;
	CEdit eContext;
	afx_msg void OnBnClickedButton2();
	CListBox lAdapters;
	afx_msg void OnBnClickedButton3();
};
