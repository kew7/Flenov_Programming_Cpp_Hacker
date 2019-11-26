// NetNeighbourDlg.cpp : implementation file
//
#include "stdafx.h"
#include "NetNeighbour.h"
#include "NetNeighbourDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CNetNeighbourDlg dialog
CNetNeighbourDlg::CNetNeighbourDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetNeighbourDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetNeighbourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_NetTree);
}

BEGIN_MESSAGE_MAP(CNetNeighbourDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnTvnItemexpandingTree1)
END_MESSAGE_MAP()

TCHAR* MakeDynamic( LPTSTR sData )
{
	TCHAR * sRet;
	if( sData )
	{
		sRet = new TCHAR[_tcslen(sData)+1];
		ASSERT(sRet);
		_tcscpy( sRet, sData );
	}
	else
		sRet=NULL;
	return sRet;
}

// CNetNeighbourDlg message handlers
BOOL CNetNeighbourDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if( !m_ImageListTree.Create(IDB_BITMAP1, 17, 1, RGB( 255, 255, 255 )))
		AfxMessageBox("Image list creation fault");
	m_NetTree.SetImageList(&m_ImageListTree, TVSIL_NORMAL);

	m_hNetworkRoot = InsertTreeItem(TVI_ROOT, NULL, "My Net", DRIVE_RAMDISK+1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

HTREEITEM CNetNeighbourDlg::InsertTreeItem(HTREEITEM hParent, NETRESOURCE *const pNetResource, CString sText, int iImage)
{
	TVINSERTSTRUCT InsertStruct;
	InsertStruct.hParent		= hParent;	
	InsertStruct.hInsertAfter	= TVI_LAST;
	InsertStruct.itemex.mask	= TVIF_IMAGE | TVIF_TEXT | TVIF_CHILDREN | 
								  TVIF_PARAM;
	InsertStruct.itemex.pszText	= sText.GetBuffer(sText.GetLength());  
	InsertStruct.itemex.iImage	= iImage;
	InsertStruct.itemex.cChildren= 1;
	InsertStruct.itemex.lParam	= (LPARAM)pNetResource;
	sText.ReleaseBuffer();
	return m_NetTree.InsertItem( &InsertStruct );
}

void CNetNeighbourDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CNetNeighbourDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetNeighbourDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CNetNeighbourDlg::GetItemPath( HTREEITEM hItem ) 
{
	CString sRet;
	do
	{
		NETRESOURCE *const pNetResource = (NETRESOURCE *)(m_NetTree.GetItemData( hItem ) );
		if (pNetResource)
		{
			sRet = CString(pNetResource->lpRemoteName) + _T('\\')+ sRet; 		
			break;
		}

		sRet = m_NetTree.GetItemText(hItem) + _T('\\')+ sRet; 
		hItem = m_NetTree.GetParentItem(hItem);
	} while(hItem);
	return sRet;
}

void CNetNeighbourDlg::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CWaitCursor CursorWaiting;
	ASSERT(pNMTreeView);
	ASSERT(pResult);

	if (pNMTreeView->action == 2)
	{
		CString sPath = GetItemPath(pNMTreeView->itemNew.hItem);

		if( !m_NetTree.GetChildItem(pNMTreeView->itemNew.hItem))
		{
			EnumNetwork(pNMTreeView->itemNew.hItem);
			if( m_NetTree.GetSelectedItem( ) != pNMTreeView->itemNew.hItem)
				m_NetTree.SelectItem(pNMTreeView->itemNew.hItem);
		}
	}

	*pResult = 0;
}

bool CNetNeighbourDlg::EnumNetwork(HTREEITEM hParent)
{
	bool bGotChildren = false;	

	NETRESOURCE *const pNetResource = (NETRESOURCE *)(m_NetTree.GetItemData(hParent));

	DWORD dwResult;      
	HANDLE hEnum;      
	DWORD cbBuffer = 16384;
	DWORD cEntries = 0xFFFFFFFF;      
	LPNETRESOURCE lpnrDrv;      
	DWORD i;
	dwResult = WNetOpenEnum(pNetResource ?  RESOURCE_GLOBALNET : RESOURCE_CONTEXT,
							RESOURCETYPE_ANY, 0,                               
							pNetResource ? 	pNetResource: NULL,
							&hEnum );      
	if (dwResult != NO_ERROR)      
	{
		return false;
	}
	do      
	{
		lpnrDrv = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer);
		dwResult = WNetEnumResource(hEnum, &cEntries, lpnrDrv, &cbBuffer);
		if (dwResult == NO_ERROR)         
		{
			for(i = 0; i<cEntries; i++)
			{
				CString sNameRemote = lpnrDrv[i].lpRemoteName;
				int nType = 9;
				if(sNameRemote.IsEmpty())
				{
					sNameRemote = lpnrDrv[i].lpComment;
					nType = 8;
				}
				if (sNameRemote.GetLength() > 0 && sNameRemote[0] == _T('\\'))
				    sNameRemote = sNameRemote.Mid(1);
				if (sNameRemote.GetLength() > 0 && sNameRemote[0] == _T('\\'))
					sNameRemote = sNameRemote.Mid(1);

				if (lpnrDrv[i].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE)
				{
					int nPos = sNameRemote.Find( _T('\\'));
					if(nPos >= 0)
						sNameRemote = sNameRemote.Mid(nPos+1);
					InsertTreeItem(hParent, NULL, sNameRemote, DRIVE_NO_ROOT_DIR);
				}
				else
				{
					NETRESOURCE* pResource = new NETRESOURCE;
					ASSERT(pResource);
					*pResource = lpnrDrv[i];
					pResource->lpLocalName	= MakeDynamic(pResource->lpLocalName);
					pResource->lpRemoteName = MakeDynamic(pResource->lpRemoteName);
					pResource->lpComment	= MakeDynamic(pResource->lpComment);
					pResource->lpProvider	= MakeDynamic(pResource->lpProvider);
					InsertTreeItem(hParent, pResource, sNameRemote, pResource->dwDisplayType+7);
				}
				bGotChildren = true;
			}
		}         
		GlobalFree((HGLOBAL)lpnrDrv);
		if (dwResult != ERROR_NO_MORE_ITEMS)
			break;         
	}
	while (dwResult != ERROR_NO_MORE_ITEMS);
	WNetCloseEnum(hEnum);   
	return bGotChildren;
}

