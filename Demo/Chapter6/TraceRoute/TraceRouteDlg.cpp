// TraceRouteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TraceRoute.h"
#include "TraceRouteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

lpIcmpCreateFile CTraceRouteDlg::pIcmpCreateFile;
lpIcmpSendEcho CTraceRouteDlg::pIcmpSendEcho;
lpIcmpCloseHandle CTraceRouteDlg::pIcmpCloseHandle;

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


// CTraceRouteDlg dialog



CTraceRouteDlg::CTraceRouteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTraceRouteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTraceRouteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, edHostName);
	DDX_Control(pDX, IDC_LIST1, lbMessages);
}

BEGIN_MESSAGE_MAP(CTraceRouteDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CTraceRouteDlg message handlers

BOOL CTraceRouteDlg::OnInitDialog()
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

void CTraceRouteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTraceRouteDlg::OnPaint() 
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
HCURSOR CTraceRouteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTraceRouteDlg::OnBnClickedButton1()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
	{
		AfxMessageBox("Can't load a correct version of WinSock");
		return;
	}

	hIcmp = LoadLibrary("ICMP.DLL");
	if (hIcmp == NULL)
	{
		AfxMessageBox("Can't load ICMP DLL");
		return;
	}

	pIcmpCreateFile = (lpIcmpCreateFile) GetProcAddress(hIcmp,"IcmpCreateFile");
	pIcmpSendEcho = (lpIcmpSendEcho) GetProcAddress(hIcmp,"IcmpSendEcho" );
	pIcmpCloseHandle = (lpIcmpCloseHandle) GetProcAddress(hIcmp,"IcmpCloseHandle");

	in_addr	Address;
	if (pIcmpCreateFile == NULL)
	{
		AfxMessageBox("ICMP library error");
		return;
	}

	char chHostName[255];
	edHostName.GetWindowText(chHostName, 255);
	LPHOSTENT hp = gethostbyname(chHostName);
	if (hp== NULL)
	{
		AfxMessageBox("Host not found");
		return;
	}
	unsigned long	addr;
	memcpy(&addr, hp->h_addr, hp->h_length);

	BOOL bReachedHost = FALSE;
	for (UCHAR i=1; i<=50 && !bReachedHost; i++)
	{
		Address.S_un.S_addr = 0;

		int iPacketSize=32;
		int iRTT;

		HANDLE hIP = pIcmpCreateFile();
		if (hIP == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("Could not get a valid ICMP handle");
			return;
		}

		unsigned char* pBuf = new unsigned char[iPacketSize];
		FillMemory(pBuf, iPacketSize, 80);

		int iReplySize = sizeof(ICMP_ECHO_REPLY) + iPacketSize;
		unsigned char* pReplyBuf = new unsigned char[iReplySize];
		ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*) pReplyBuf;

  		IP_OPTION_INFORMATION ipOptionInfo;
		ZeroMemory(&ipOptionInfo, sizeof(IP_OPTION_INFORMATION));
		ipOptionInfo.Ttl = i;

		DWORD nRecvPackets = pIcmpSendEcho(hIP, addr, pBuf, iPacketSize, &ipOptionInfo, pReplyBuf, iReplySize, 30000);

		if (nRecvPackets != 1)
		{
			AfxMessageBox("Can't ping host");
			return;
		}
		Address.S_un.S_addr = pEchoReply->Address;
		iRTT = pEchoReply->RoundTripTime;

		pIcmpCloseHandle(hIP);

		delete [] pReplyBuf;
		delete [] pBuf;

		char lpszText[255];

		hostent* phostent = NULL;
		phostent = gethostbyaddr((char *)&Address.S_un.S_addr, 4, PF_INET);
	
		if (phostent)
			sprintf(lpszText, "%d: %d ms [%s] (%d.%d.%d.%d)", 
				i, iRTT, 
				phostent->h_name, Address.S_un.S_un_b.s_b1, Address.S_un.S_un_b.s_b2, 
				Address.S_un.S_un_b.s_b3, Address.S_un.S_un_b.s_b4);
		else
			sprintf(lpszText, "%d - %d ms (%d.%d.%d.%d)", 
				i, iRTT,
				Address.S_un.S_un_b.s_b1, Address.S_un.S_un_b.s_b2, Address.S_un.S_un_b.s_b3, 
				Address.S_un.S_un_b.s_b4);
 
		lbMessages.AddString(lpszText);

		if (addr == Address.S_un.S_addr)
			bReachedHost = TRUE;
	}

	if (hIcmp)
	{
		FreeLibrary(hIcmp);
		hIcmp = NULL;
	}

	WSACleanup();
}
