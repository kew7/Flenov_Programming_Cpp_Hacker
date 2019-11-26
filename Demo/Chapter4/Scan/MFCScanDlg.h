// MFCScanDlg.h : header file
//

#include "ClientSocket.h"
#include "afxwin.h"

#pragma once


// CMFCScanDlg dialog
class CMFCScanDlg : public CDialog
{
// Construction
public:
	CMFCScanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCSCAN_DIALOG };

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
	afx_msg void OnBnClickedScanButton();
	CListBox PortsList;
};
