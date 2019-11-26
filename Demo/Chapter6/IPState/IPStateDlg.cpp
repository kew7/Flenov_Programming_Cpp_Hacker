// IPStateDlg.cpp : implementation file
//

#include "stdafx.h"
#include <iphlpapi.h>
#include <assert.h>
#include <winsock2.h>
#include "IPState.h"
#include "IPStateDlg.h"

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


// CIPStateDlg dialog



CIPStateDlg::CIPStateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPStateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lList);
}

BEGIN_MESSAGE_MAP(CIPStateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CIPStateDlg message handlers

BOOL CIPStateDlg::OnInitDialog()
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

void CIPStateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPStateDlg::OnPaint() 
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
HCURSOR CIPStateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIPStateDlg::OnBnClickedButton1()
{
    DWORD dwStatus = NO_ERROR;
    PMIB_TCPTABLE pTcpTable = NULL;
    DWORD dwActualSize = 0;

    dwStatus = GetTcpTable(pTcpTable, &dwActualSize, TRUE);

    pTcpTable = (PMIB_TCPTABLE) malloc(dwActualSize);
    assert(pTcpTable);
        
    dwStatus = GetTcpTable(pTcpTable, &dwActualSize, TRUE);
    if (dwStatus != NO_ERROR)
    {
        AfxMessageBox("Couldn't get tcp connection table.");
        free(pTcpTable);
        return;
    }

    CString strState;
    struct in_addr inadLocal, inadRemote;
    DWORD dwRemotePort = 0;
    char szLocalIp[1000];
    char szRemIp[1000];

    if (pTcpTable != NULL)
    {
		lList.AddString("=================================================");
		lList.AddString("TCP table:");
        for (int i = 0; i < pTcpTable->dwNumEntries; i++)
        {
            dwRemotePort = 0;
            switch (pTcpTable->table[i].dwState)
            {
            case MIB_TCP_STATE_LISTEN:
				strState="Listen";
                dwRemotePort = pTcpTable->table[i].dwRemotePort;
                break;
            case MIB_TCP_STATE_CLOSED:
				strState="Closed";
                break;
            case MIB_TCP_STATE_TIME_WAIT:
				strState="Time wait";                
                break;
            case MIB_TCP_STATE_LAST_ACK:
				strState="Last ACK";
                break;
            case MIB_TCP_STATE_CLOSING:
				strState="Closing";
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
				strState="Close Wait";
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
				strState="FIN wait";
                break;
            case MIB_TCP_STATE_ESTAB:
				strState="EStab";
                break;
            case MIB_TCP_STATE_SYN_RCVD:
				strState="SYN Received";
                break;
            case MIB_TCP_STATE_SYN_SENT:
				strState="SYN Sent";
                break;
            case MIB_TCP_STATE_DELETE_TCB:
				strState="Delete";
                break;
            }
            inadLocal.s_addr = pTcpTable->table[i].dwLocalAddr;
            inadRemote.s_addr = pTcpTable->table[i].dwRemoteAddr;
            strcpy(szLocalIp, inet_ntoa(inadLocal));
            strcpy(szRemIp, inet_ntoa(inadRemote));

			char prtStr[1000];
			sprintf(prtStr, "Loc Addr %1s; Loc Port %1u; Rem Addr %1s; Rem Port %1u; State %s;", 
                szLocalIp,  ntohs((unsigned short)(0x0000FFFF & pTcpTable->table[i].dwLocalPort)),
                szRemIp, ntohs((unsigned short)(0x0000FFFF & dwRemotePort)),
                strState);
			lList.AddString(prtStr);
        }
    }
    free(pTcpTable);
}

void CIPStateDlg::OnBnClickedButton2()
{
    DWORD dwStatus = NO_ERROR;
    PMIB_UDPTABLE pUdpTable = NULL;
    DWORD dwActualSize = 0;

    dwStatus = GetUdpTable(pUdpTable, &dwActualSize, TRUE);

    pUdpTable = (PMIB_UDPTABLE) malloc(dwActualSize);
    assert(pUdpTable);
        
    dwStatus = GetUdpTable(pUdpTable, &dwActualSize, TRUE);
    
	if (dwStatus != NO_ERROR)
    {
        AfxMessageBox("Couldn't get udp connection table.");
        free(pUdpTable);
        return;
    }

    struct in_addr inadLocal;
    if (pUdpTable != NULL)
    {
		lList.AddString("=================================================");
		lList.AddString("UDP table:");
        for (UINT i = 0; i < pUdpTable->dwNumEntries; ++i)
        {
            inadLocal.s_addr = pUdpTable->table[i].dwLocalAddr;

            char prtStr[1000];
            sprintf(prtStr, "Loc Addr %1s; Loc Port %1u", 
                  inet_ntoa(inadLocal), ntohs((unsigned short)(0x0000FFFF & pUdpTable->table[i].dwLocalPort)));
            lList.AddString(prtStr);
        }
    }
    free(pUdpTable);
}
