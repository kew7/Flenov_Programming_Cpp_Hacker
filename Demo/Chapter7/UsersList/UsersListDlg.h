// UsersListDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CUsersListDlg dialog
class CUsersListDlg : public CDialog
{
// Construction
public:
	CUsersListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_USERSLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	void GetUsersList();
	void GetGroupsList();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox cUsersList;
	CListBox cGroupList;
};
