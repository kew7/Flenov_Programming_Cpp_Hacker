// UsersListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UsersList.h"
#include "UsersListDlg.h"
#include "lm.h"

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


// CUsersListDlg dialog


CUsersListDlg::CUsersListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsersListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsersListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, cUsersList);
	DDX_Control(pDX, IDC_LIST2, cGroupList);
}

BEGIN_MESSAGE_MAP(CUsersListDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUsersListDlg message handlers

BOOL CUsersListDlg::OnInitDialog()
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
	GetUsersList();
	GetGroupsList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUsersListDlg::GetUsersList()
{
	LPUSER_INFO_3 pBuf = NULL;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	NET_API_STATUS status;

	do
	{
		status = NetUserEnum(NULL, 3, FILTER_NORMAL_ACCOUNT, (LPBYTE*)&pBuf, 
			MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);

		if ((status != NERR_Success) && (status != ERROR_MORE_DATA))
			return;
		if (pBuf == NULL)
			return;

		for (DWORD i = 0; i< dwEntriesRead; i++)
		{
			cUsersList.AddString(pBuf[i].usri3_name);
		}
	} while (status == ERROR_MORE_DATA);
	
	NetApiBufferFree(pBuf);
}

void CUsersListDlg::GetGroupsList()
{
	LPGROUP_INFO_1 pBuf = NULL;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	NET_API_STATUS status;

	do
	{
		status = NetLocalGroupEnum(NULL, 1, (LPBYTE*)&pBuf, 
			MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);

		if ((status != NERR_Success) && (status != ERROR_MORE_DATA))
			return;
		if (pBuf == NULL)
			return;

		for (DWORD i = 0; i< dwEntriesRead; i++)
		{
			cGroupList.AddString(pBuf[i].grpi1_name);
		}
	} while (status == ERROR_MORE_DATA);
	
	NetApiBufferFree(pBuf);
}

void CUsersListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUsersListDlg::OnPaint()
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
HCURSOR CUsersListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

