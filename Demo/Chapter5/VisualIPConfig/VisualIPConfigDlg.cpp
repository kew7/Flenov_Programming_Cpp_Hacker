// VisualIPConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Iphlpapi.h"
#include "iptypes.h"
#include "VisualIPConfig.h"
#include "VisualIPConfigDlg.h"

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


// CVisualIPConfigDlg dialog



CVisualIPConfigDlg::CVisualIPConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVisualIPConfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVisualIPConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, eHostName);
	DDX_Control(pDX, IDC_EDIT2, DNSServers);
	DDX_Control(pDX, IDC_EDIT3, eNodeType);
	DDX_Control(pDX, IDC_EDIT4, eIPRouting);
	DDX_Control(pDX, IDC_EDIT5, eWinsProxy);
	DDX_Control(pDX, IDC_LIST1, eAdaptersInfo);
}

BEGIN_MESSAGE_MAP(CVisualIPConfigDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CVisualIPConfigDlg message handlers

BOOL CVisualIPConfigDlg::OnInitDialog()
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

void CVisualIPConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVisualIPConfigDlg::OnPaint() 
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
HCURSOR CVisualIPConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVisualIPConfigDlg::OnBnClickedButton1()
{
    PFIXED_INFO pFixedInfo;
    ULONG iFixedInfo;

    PIP_ADAPTER_INFO pAdapterInfo, pAdapter;
    ULONG iAdapterInfo;
    PIP_ADDR_STRING chAddr;

	CString Str;	 
	TCHAR lpszText[1024];
	int iErr;

    if ((iErr = GetNetworkParams(NULL, &iFixedInfo)) != 0)
    {
        if (iErr != ERROR_BUFFER_OVERFLOW)
        {
			AfxMessageBox("GetNetworkParams failed");
            return;
        }
    }

    if ((pFixedInfo=(PFIXED_INFO)GlobalAlloc(GPTR, iFixedInfo))==NULL)
    {
        AfxMessageBox("Memory allocation error");
        return;
    }

    if (GetNetworkParams(pFixedInfo, &iFixedInfo) != 0)
	{
        AfxMessageBox("GetNetworkParams failed");
        return;
    }

    eHostName.SetWindowText(pFixedInfo->HostName);

    CString s=pFixedInfo->DnsServerList.IpAddress.String;
    chAddr = pFixedInfo->DnsServerList.Next;
    while(chAddr)
    {
        s=s+" "+chAddr->IpAddress.String;
        chAddr = chAddr->Next;
    }
    DNSServers.SetWindowText(s);

    switch (pFixedInfo->NodeType)
    {
        case 1:
            eNodeType.SetWindowText("Broadcast");
            break;
        case 2:
            eNodeType.SetWindowText("Peer to peer");
            break;
        case 4:
            eNodeType.SetWindowText("Mixed");
            break;
        case 8:
            eNodeType.SetWindowText("Hybrid");
            break;
        default:
            eNodeType.SetWindowText("Don't know");
    }

    eIPRouting.SetWindowText(pFixedInfo->EnableRouting ? "Enabled" : "Disabled");
    eWinsProxy.SetWindowText(pFixedInfo->EnableProxy ? "Enabled" : "Disabled");        

    iAdapterInfo = 0;
	iErr=GetAdaptersInfo(NULL, &iAdapterInfo);
    if ((iErr!= 0) && (iErr != ERROR_BUFFER_OVERFLOW))
    {
		AfxMessageBox("GetAdaptersInfo failed");
		return;
    }

    if ((pAdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc(GPTR, iAdapterInfo)) == NULL)
    {
        AfxMessageBox("Memory allocation error\n");
        return;
    }

    if (GetAdaptersInfo(pAdapterInfo, &iAdapterInfo) != 0)
    {
        AfxMessageBox("GetAdaptersInfo failed");
        return;
    }

    pAdapter = pAdapterInfo;

	eAdaptersInfo.AddString("===========================");

	while (pAdapter)
    {
        switch (pAdapter->Type)
        {
            case MIB_IF_TYPE_ETHERNET:
				Str="Ethernet adapter: "; break;
            case MIB_IF_TYPE_PPP:
				Str="PPP adapter: "; break;
            case MIB_IF_TYPE_LOOPBACK:
				Str="Loopback adapter: "; break;
            case MIB_IF_TYPE_TOKENRING:
				Str="Token Ring adapter: "; break;
            case MIB_IF_TYPE_FDDI:
				Str="FDDI adapter: "; break;
            case MIB_IF_TYPE_SLIP:
				Str="Slip adapter: "; break;
            case MIB_IF_TYPE_OTHER:
            default: Str="Other adapter: ";
        }
        eAdaptersInfo.AddString(Str+pAdapter->AdapterName);

		Str= "Description: ";
		eAdaptersInfo.AddString(Str+pAdapter->Description); 

		Str="Physical Address: ";
        for (UINT i=0; i<pAdapter->AddressLength; i++)
        {
            if (i == (pAdapter->AddressLength - 1))
                sprintf(lpszText, "%.2X",(int)pAdapter->Address[i]);
            else
                sprintf(lpszText, "%.2X",(int)pAdapter->Address[i]);
			Str=Str+lpszText;
        }        
		eAdaptersInfo.AddString(Str);

        sprintf(lpszText, "DHCP Enabled: %s", (pAdapter->DhcpEnabled ? "yes" : "no"));
		eAdaptersInfo.AddString(lpszText);

        chAddr = &(pAdapter->IpAddressList);
        while(chAddr)
        {
			Str="IP Address: ";
			eAdaptersInfo.AddString(Str+chAddr->IpAddress.String);
            
			Str="Subnet Mask: ";
			eAdaptersInfo.AddString(Str+chAddr->IpMask.String);

			chAddr = chAddr->Next;
        }

		Str="Default Gateway: ";
		eAdaptersInfo.AddString(Str+pAdapter->GatewayList.IpAddress.String);
        
        chAddr = pAdapter->GatewayList.Next;
        while(chAddr)
        {
            //print next Gateway
            chAddr = chAddr->Next;
        }

		Str="DHCP Server: ";
		eAdaptersInfo.AddString(Str+pAdapter->DhcpServer.IpAddress.String);
        
		Str="Primary WINS Server: ";
		eAdaptersInfo.AddString(Str+pAdapter->PrimaryWinsServer.IpAddress.String);

		Str="Secondary WINS Server: ";
		eAdaptersInfo.AddString(Str+pAdapter->SecondaryWinsServer.IpAddress.String);

		eAdaptersInfo.AddString("===========================");
        pAdapter = pAdapter->Next;
    }
}
