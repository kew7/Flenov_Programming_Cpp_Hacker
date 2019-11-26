// NetNeighbourDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CNetNeighbourDlg dialog
class CNetNeighbourDlg : public CDialog
{
// Construction
public:
	CNetNeighbourDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NETNEIGHBOUR_DIALOG };

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

private:
	CImageList	m_ImageListTree;
	HTREEITEM	m_hNetworkRoot;
	CString		m_sPath;

	HTREEITEM InsertTreeItem( HTREEITEM hParent, NETRESOURCE *const pNetResource, CString sText, int iImage);
	CString GetItemPath( HTREEITEM hItem );
	bool EnumNetwork( HTREEITEM hParent );
public:
	CTreeCtrl m_NetTree;
	afx_msg void OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
