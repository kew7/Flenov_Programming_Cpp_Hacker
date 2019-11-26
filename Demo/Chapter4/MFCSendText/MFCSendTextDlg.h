// MFCSendTextDlg.h : header file
//

#pragma once
#include "afxwin.h"

class CServerSocket;
class CClientSocket;

// CMFCSendTextDlg dialog
class CMFCSendTextDlg : public CDialog
{
// Construction
public:
	CMFCSendTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCSENDTEXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CServerSocket* m_sSocket;
	CClientSocket* m_cSocket;
	CClientSocket* m_scSocket;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton m_SendButton;
	afx_msg void OnBnClickedButton4();
	void AddConnection();
};
