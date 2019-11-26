// ARPApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include <winsock.h>
#include "ARPApplication.h"
#include "ARPApplicationDlg.h"

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


// CARPApplicationDlg dialog



CARPApplicationDlg::CARPApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CARPApplicationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CARPApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edIPAddress);
	DDX_Control(pDX, IDC_EDIT2, edMacAddress);
	DDX_Control(pDX, IDC_LIST1, lbMessages);
	DDX_Control(pDX, IDC_EDIT3, edInterface);
}

BEGIN_MESSAGE_MAP(CARPApplicationDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// CARPApplicationDlg message handlers

BOOL CARPApplicationDlg::OnInitDialog()
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

void CARPApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CARPApplicationDlg::OnPaint() 
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
HCURSOR CARPApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool AddrToStr(BYTE PhysAddr[], int PhysAddrLen, char str[])
{
    if (PhysAddr == NULL || PhysAddrLen == 0 || str == NULL)
        return FALSE;
    str[0] = '\0';
    
	for (DWORD dwIdx = 0; dwIdx < PhysAddrLen; dwIdx++)
    {
        if (dwIdx == PhysAddrLen-1)
            sprintf(str+(dwIdx*3), "%02X", ((int)PhysAddr[dwIdx])&0xff);
        else
            sprintf(str+(dwIdx*3), "%02X-", ((int)PhysAddr[dwIdx])&0xff);
        
    }
    
	return TRUE;
}

void CARPApplicationDlg::OnBnClickedButton1()
{
	DWORD dwStatus;
	PMIB_IPNETTABLE pIpArpTab=NULL;

	DWORD dwActualSize = 0;
	GetIpNetTable(pIpArpTab, &dwActualSize, true);
	
	pIpArpTab = (PMIB_IPNETTABLE) malloc(dwActualSize);
	if (GetIpNetTable(pIpArpTab, &dwActualSize, true) != NO_ERROR)
	{
		if (pIpArpTab)
			free (pIpArpTab);
		return;
	}

	DWORD i, dwCurrIndex;
	char sPhysAddr[256], sType[256], sAddr[256];
	PMIB_IPADDRTABLE pIpAddrTable = NULL;
	char Str[255];

	dwActualSize = 0;
	GetIpAddrTable(pIpAddrTable, &dwActualSize, true);
	pIpAddrTable = (PMIB_IPADDRTABLE) malloc(dwActualSize);
	GetIpAddrTable(pIpAddrTable, &dwActualSize, true);

	dwCurrIndex = -100;
    
	for (i = 0; i < pIpArpTab->dwNumEntries; ++i)
	{
		if (pIpArpTab->table[i].dwIndex != dwCurrIndex)
		{
			dwCurrIndex = pIpArpTab->table[i].dwIndex;

			
			struct in_addr in_ad;
			sAddr[0] = '\n';
			for (int i = 0; i < pIpAddrTable->dwNumEntries; i++)
			{
				if (dwCurrIndex != pIpAddrTable->table[i].dwIndex)
					continue;

				in_ad.s_addr = pIpAddrTable->table[i].dwAddr;
				strcpy(sAddr, inet_ntoa(in_ad));
			}

			sprintf(Str,"Interface: %s on Interface 0x%X", sAddr, dwCurrIndex);
			lbMessages.AddString(Str);
			lbMessages.AddString(" Internet Address | Physical Address | Type");	
		}

		AddrToStr(pIpArpTab->table[i].bPhysAddr, pIpArpTab->table[i].dwPhysAddrLen, sPhysAddr);
		
        switch (pIpArpTab->table[i].dwType)
        {
        case 1:
            strcpy(sType,"Other");
            break;
        case 2:
            strcpy(sType,"Invalidated");
            break;
        case 3:
            strcpy(sType,"Dynamic");
            break;
        case 4: 
            strcpy(sType,"Static");
            break;
        default:
            strcpy(sType,"");
        }

		struct in_addr in_ad;
		in_ad.s_addr = pIpArpTab->table[i].dwAddr;
        sprintf(Str, " %-16s | %-17s | %-11s", inet_ntoa(in_ad), sPhysAddr, sType);
		lbMessages.AddString(Str);
    }

	free(pIpArpTab);
}

void StrToMACAddr(char* sIn, char* sOut)
{
    register char c;    
    register int l;    

	for (int i = 0; i < 6; i++)
    {
        l = 0;
        c = toupper(sIn[i*3]);
        c = c - (isdigit(c) ? '0' : ('A' - 10)); 
        l += c;
        l = (l * 16);
        c = toupper(sIn[i*3 + 1]);
        c = c - (isdigit(c) ? '0' : ('A' - 10)); 
        l += c;
        sOut[i] = l;
    }
}

void CARPApplicationDlg::OnBnClickedButton2()
{
	char sPhysAddr[255],
		sInetAddr[255], 
		sMacAddr[255], 
		sInterface[255];

	edIPAddress.GetWindowText(sInetAddr, 255);
	edMacAddress.GetWindowText(sMacAddr, 255);
	edInterface.GetWindowText(sInterface, 255);


	if (sInetAddr == NULL || sMacAddr == NULL || sInterface == NULL)
	{
		AfxMessageBox("Fill IP address, MAC address and Interface");
		return;
	}

	DWORD dwInetAddr;
	dwInetAddr = inet_addr(sInetAddr);
	if (dwInetAddr == INADDR_NONE)
	{
		AfxMessageBox("Bad IP Address");
		return;
	}

	StrToMACAddr(sMacAddr, sPhysAddr);

	MIB_IPNETROW arpRow;
	sscanf(sInterface, "%X",&(arpRow.dwIndex));

	arpRow.dwPhysAddrLen = 6;
	memcpy(arpRow.bPhysAddr, sPhysAddr, 6);
	arpRow.dwAddr = dwInetAddr;
	arpRow.dwType = MIB_IPNET_TYPE_STATIC;

	if (SetIpNetEntry(&arpRow) != NO_ERROR)
		AfxMessageBox("Couldn't add ARP record");
}

void CARPApplicationDlg::OnBnClickedButton3()
{
	char sInetAddr[255], 
		sInterface[255];

	edIPAddress.GetWindowText(sInetAddr, 255);
	edInterface.GetWindowText(sInterface, 255);

	if (sInetAddr == NULL || sInterface == NULL)
	{
		AfxMessageBox("Fill IP address and Interface");
		return;
	}

	DWORD dwInetAddr;
	dwInetAddr = inet_addr(sInetAddr);
	if (dwInetAddr == INADDR_NONE)
	{
		printf("IpArp: Bad Argument %s\n", sInetAddr);
		return;
	}

	MIB_IPNETROW arpEntry;

	sscanf(sInterface, "%X",&(arpEntry.dwIndex));
	arpEntry.dwAddr = dwInetAddr;
    
	if (DeleteIpNetEntry(&arpEntry) != NO_ERROR)
		AfxMessageBox("Couldn't delete ARP record");
}
