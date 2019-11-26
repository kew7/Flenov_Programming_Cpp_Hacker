// COMportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "COMport.h"
#include "COMportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HANDLE hCom;

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


// CCOMportDlg dialog



CCOMportDlg::CCOMportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCOMportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCOMportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cbPorts);
	DDX_Control(pDX, IDC_LIST1, lLogList);
	DDX_Control(pDX, IDC_EDIT1, eSendCommand);
}

BEGIN_MESSAGE_MAP(CCOMportDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OPENPORT_BUTTON, OnBnClickedOpenportButton)
	ON_BN_CLICKED(IDC_SENDCOMMAND_BUTTON, OnBnClickedSendcommandButton)
END_MESSAGE_MAP()


// CCOMportDlg message handlers

BOOL CCOMportDlg::OnInitDialog()
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
	
	cbPorts.AddString("COM1");
	cbPorts.AddString("COM2");
	cbPorts.AddString("COM3");
	cbPorts.AddString("COM4");
	cbPorts.AddString("COM5");
	cbPorts.SetDroppedWidth(5);
	hCom = INVALID_HANDLE_VALUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCOMportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCOMportDlg::OnPaint() 
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
HCURSOR CCOMportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCOMportDlg::OnBnClickedButton1()
{
	if (hCom == INVALID_HANDLE_VALUE)
		return;
 
	if (MessageBox("Close port?", "Warning", MB_YESNO) == IDYES)
	{
		TerminateThread(hThread, 0);
		CloseHandle(hCom);
		hCom = INVALID_HANDLE_VALUE;
	}
}

DWORD __stdcall ReadThread(LPVOID hwnd)
{
	DWORD iSize;
	char sReceivedChar;
	while(true)
	{
		ReadFile(hCom,&sReceivedChar,1,&iSize,0);
		SendDlgItemMessage((HWND)hwnd,IDC_EDIT2,WM_CHAR,sReceivedChar,0);
	}
}

void CCOMportDlg::OnBnClickedOpenportButton()
{
	if (hCom != INVALID_HANDLE_VALUE)
	{
		OnBnClickedButton1();
		Sleep(300);
	}

	char sPortName[10];
	cbPorts.GetWindowText(sPortName, 10);

	hCom = CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 
					0, NULL, OPEN_EXISTING, 0, NULL);

	if (hCom == INVALID_HANDLE_VALUE) 
		lLogList.AddString("Error opening port");
	else  
	{
		lLogList.AddString("Port successfully opened.");
		hThread = CreateThread(0, 0, ReadThread, (LPVOID)this, 0, 0);

		DCB dcb;
		GetCommState(hCom, &dcb);
		dcb.BaudRate = CBR_57600;
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT; 
		if (SetCommState(hCom, &dcb))
			lLogList.AddString("Configuring OK");
		else
			lLogList.AddString("Configuring Error");
	}
}

void CCOMportDlg::OnBnClickedSendcommandButton()
{
	if (hCom == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Open port before send command");
		return;
	}

	char sSend[10224];
	eSendCommand.GetWindowText(sSend, 1024);

	if (strlen(sSend)>0)
	{
			lLogList.AddString(sSend);	

			sSend[strlen(sSend)] = '\r';
			sSend[strlen(sSend)] = '\0';

			TerminateThread(hThread,0);
			DWORD iSize;
			WriteFile(hCom, sSend, strlen(sSend), &iSize,0);
			hThread = CreateThread(0, 0, ReadThread, (LPVOID)this, 0, 0);
	}
}
