// FastScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FastScan.h"
#include "FastScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_SOCKETS	40

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


// CFastScanDlg dialog



CFastScanDlg::CFastScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFastScanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFastScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STARTPORT, chStartPort);
	DDX_Control(pDX, IDC_ENDPORT, chEndPort);
	DDX_Control(pDX, IDC_EDITHOSTNAME, chHostName);
	DDX_Control(pDX, IDC_LIST1, m_PortList);
}

BEGIN_MESSAGE_MAP(CFastScanDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CFastScanDlg message handlers

BOOL CFastScanDlg::OnInitDialog()
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

void CFastScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFastScanDlg::OnPaint() 
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
HCURSOR CFastScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else
			return;
	}
}

void CFastScanDlg::OnBnClickedButton1()
{
	char tStr[255]; 
	SOCKET sock[MAX_SOCKETS];
	int busy[MAX_SOCKETS], port[MAX_SOCKETS];
	int iStartPort, iEndPort, iBusySocks = 0;
	struct sockaddr_in addr;
	fd_set fdWaitSet;

	WSADATA       wsd;
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		SetDlgItemText(IDC_STATUSTEXT, "Can't load WinSock");
		return;
	}

	SetDlgItemText(IDC_STATUSTEXT, "Resolving host");

	chStartPort.GetWindowText(tStr, 255);
	iStartPort = atoi(tStr);
	chEndPort.GetWindowText(tStr, 255);
	iEndPort = atoi(tStr);

	chHostName.GetWindowText(tStr, 255);

	struct hostent *host=NULL;
	host = gethostbyname(tStr);
	if (host == NULL)
	{
		SetDlgItemText(IDC_STATUSTEXT, "Unable to resolve host");
		return;
	}

	for (int i = 0; i < MAX_SOCKETS; i++)
	    busy[i] = 0;
	
	SetDlgItemText(IDC_STATUSTEXT, "Scanning");
	
	while (((iBusySocks) || (iStartPort <= iEndPort)))
	{
	    for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if (busy[i] == 0 && iStartPort <= iEndPort)
			{		
				sock[i] = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);				
				if (sock[i] < 0)
				{
					SetDlgItemText(IDC_STATUSTEXT, "Socket filed");
					return;
				}
				iBusySocks++;
				addr.sin_family = AF_INET;
				addr.sin_port = htons (iStartPort);
				CopyMemory(&addr.sin_addr, host->h_addr_list[0],
						host->h_length);

				ULONG ulBlock;
				ulBlock = 1;
				if (ioctlsocket(sock[i], FIONBIO, &ulBlock) == SOCKET_ERROR)
				{
					return;
				}

				connect (sock[i], (struct sockaddr *) &addr, sizeof (addr));
				if (WSAGetLastError() == WSAEINPROGRESS)
				{
					closesocket (sock[i]);
					iBusySocks--;
				}
				else
				{
					busy[i] = 1;
					port[i] = iStartPort;
				}
				iStartPort++;
			}
		}
		FD_ZERO (&fdWaitSet);
		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if (busy[i] == 1)
				FD_SET (sock[i], &fdWaitSet);
		}

		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		if (select (1, NULL, &fdWaitSet, NULL, &tv) == SOCKET_ERROR)
		{	  
			SetDlgItemText(IDC_STATUSTEXT, "Select error");
			return;
		}

		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if (busy[i] == 1)
			{
				if (FD_ISSET (sock[i], &fdWaitSet))
				{
					int opt;
					int Len = sizeof(opt);
					if (getsockopt(sock[i], SOL_SOCKET, SO_ERROR, (char*)&opt, &Len) == SOCKET_ERROR)
						SetDlgItemText(IDC_STATUSTEXT, "getsockopt error");

					if (opt == 0)
					{
						struct servent *tec;						
						itoa(port[i],tStr, 10);
						strcat(tStr, " (");
						tec = getservbyport(htons (port[i]), "tcp");
						if (tec==NULL)
							strcat(tStr, "Unknown");
						else
							strcat(tStr, tec->s_name);

						strcat(tStr, ") - open");
						m_PortList.AddString(tStr);
						busy[i] = 0;
						shutdown(sock[i], SD_BOTH);
						closesocket(sock[i]);
					}
					busy[i] = 0;
					shutdown (sock[i], SD_BOTH);
					closesocket (sock[i]);
					iBusySocks--;					
				}
				else
				{
						busy[i] = 0;
						closesocket(sock[i]);
						iBusySocks--;
				}
			}
		}
		ProcessMessages();
	}
	WSACleanup();
	SetDlgItemText(IDC_STATUSTEXT, "Scaning complete");
	return;
}
