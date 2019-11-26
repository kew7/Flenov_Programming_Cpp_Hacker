// PingerDlg.cpp : implementation file
//

#include "stdafx.h"
#include <winsock2.h>
#include "Pinger.h"
#include "PingerDlg.h"

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


// CPingerDlg dialog



CPingerDlg::CPingerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPingerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edHost);
	DDX_Control(pDX, IDC_LIST1, lMessages);
}

BEGIN_MESSAGE_MAP(CPingerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CPingerDlg message handlers

BOOL CPingerDlg::OnInitDialog()
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

void CPingerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPingerDlg::OnPaint() 
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
HCURSOR CPingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Calculate check summ
u_short CheckSum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short answer;
	register int sum = 0;

	while( nleft > 1 )  {
		sum += *addr++;
		nleft -= 1;
	}

	sum += (sum >> 16);			
	answer = ~sum;				
	return (answer);
}

void CPingerDlg::OnBnClickedButton1()
{
	SOCKET	  rawSocket;
	LPHOSTENT lpHost;
	struct    sockaddr_in sDest;
	struct    sockaddr_in sSrc;
	DWORD	  dwElapsed;
	int       iRet;
	CString str;

    WSADATA       wsd;
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		AfxMessageBox("Can't load WinSock");
		return;
	}

	// Create socket
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR) 
	{
		AfxMessageBox("Socket error");
		return;
	}
	
	// Lookup host
	char strHost[255];
	edHost.GetWindowText(strHost, 255);
	lpHost = gethostbyname(strHost);
	if (lpHost == NULL)
	{
		AfxMessageBox("Host not found");
		return;
	}
	
	// Socket address
	sDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	sDest.sin_family = AF_INET;
	sDest.sin_port = 0;

	str.Format("Pinging %s [%s]",
				strHost, inet_ntoa(sDest.sin_addr));

	lMessages.AddString(str);

	// Send ICMP echo request
	static ECHOREQUEST echoReq;

	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.ID			= 0;
	echoReq.icmpHdr.Seq			= 0;
	echoReq.dwTime = GetTickCount();
	FillMemory(echoReq.cData, 64, 80);
	echoReq.icmpHdr.Checksum = CheckSum((u_short *)&echoReq, sizeof(ECHOREQUEST));

	// Send the echo request  								  
	sendto(rawSocket, (LPSTR)&echoReq, sizeof(ECHOREQUEST),
			0, (LPSOCKADDR)&sDest, sizeof(SOCKADDR_IN));   

	struct timeval tVal;
	fd_set readfds;
	readfds.fd_count = 1;
	readfds.fd_array[0] = rawSocket;
	tVal.tv_sec = 1;
    tVal.tv_usec = 0;

	iRet=select(1, &readfds, NULL, NULL, &tVal);

	if (!iRet)
	{
		lMessages.AddString("Request Timed Out");
	}
	else
	{
		// Receive reply
		ECHOREPLY echoReply;
		int nRet;
		int nAddrLen = sizeof(struct sockaddr_in);

		// Receive the echo reply
		iRet = recvfrom(rawSocket, (LPSTR)&echoReply,	
				sizeof(ECHOREPLY), 0, (LPSOCKADDR)&sSrc, &nAddrLen);

		if (iRet == SOCKET_ERROR) 
			AfxMessageBox("Recvfrom Error");

		// Calculate time
		dwElapsed = GetTickCount() - echoReply.echoRequest.dwTime;
		str.Format("Reply from: %s: bytes=%d time=%ldms TTL=%d", 
				inet_ntoa(sSrc.sin_addr), 64, dwElapsed, echoReply.ipHdr.TTL);
		lMessages.AddString(str);
	}
	
	iRet = closesocket(rawSocket);
	if (iRet == SOCKET_ERROR)
		AfxMessageBox("Closesocket error");

	WSACleanup();
}
