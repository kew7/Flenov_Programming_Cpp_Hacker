// MFCSendTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSendText.h"
#include "MFCSendTextDlg.h"
#include "ClientSocket.h"
#include "ServerSocket.h"

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


// CMFCSendTextDlg dialog



CMFCSendTextDlg::CMFCSendTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCSendTextDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSendTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_SendButton);
}

BEGIN_MESSAGE_MAP(CMFCSendTextDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCSendTextDlg message handlers

BOOL CMFCSendTextDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCSendTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCSendTextDlg::OnPaint() 
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
HCURSOR CMFCSendTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSendTextDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_sSocket=new CServerSocket(this);
	m_sSocket->Create(22345);
	m_sSocket->Listen();
	SetDlgItemText(IDC_STATIC, "Server started");
}

void CMFCSendTextDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_cSocket = new CClientSocket(this);
	m_cSocket->Create();
	if (m_cSocket->Connect("127.0.0.1", 22345))
		m_SendButton.EnableWindow(TRUE);
}

void CMFCSendTextDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	m_cSocket->Send("Hello", 100);

	int err=m_cSocket->GetLastError();
	if(err>0)
	{
		CString ErrStr ;
		ErrStr.Format("errcode=%d",err);
		AfxMessageBox(ErrStr);
	}
}

void CMFCSendTextDlg::AddConnection()
{
	m_scSocket = new CClientSocket(this);
    m_sSocket->Accept(*m_scSocket);
}

void CMFCSendTextDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_STATIC, "Disconnected");
	m_cSocket->Close();
}
