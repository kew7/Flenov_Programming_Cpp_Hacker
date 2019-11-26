// RenewIPAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include <iphlpapi.h>
#include <winsock.h>
#include "RenewIPAddress.h"
#include "RenewIPAddressDlg.h"

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


// CRenewIPAddressDlg dialog



CRenewIPAddressDlg::CRenewIPAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenewIPAddressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenewIPAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lAdapters);
	DDX_Control(pDX, IDC_EDIT1, sAdapterIndex);
}

BEGIN_MESSAGE_MAP(CRenewIPAddressDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// CRenewIPAddressDlg message handlers

BOOL CRenewIPAddressDlg::OnInitDialog()
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

void CRenewIPAddressDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRenewIPAddressDlg::OnPaint() 
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
HCURSOR CRenewIPAddressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRenewIPAddressDlg::OnBnClickedButton1()
{
    PIP_ADAPTER_INFO pAdapterInfo, pAdapter;
	ULONG iAdapterInfo;
	int iErr;
	CString Str;	 

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
    lAdapters.AddString("======================");
	while (pAdapter)
	{
		Str="Adapter: ";
        lAdapters.AddString(Str+pAdapter->AdapterName);

		char s[20];
		Str=itoa(pAdapter->Index, s, 10);
		Str="Index: "+Str;
		lAdapters.AddString(Str);

		PIP_ADDR_STRING chAddr = &(pAdapter->IpAddressList);
		while(chAddr)
        {
            lAdapters.AddString("------------------------------");

			Str=itoa(chAddr->Context, s, 10);
			Str="Context: "+Str;
			lAdapters.AddString(Str);

			Str="IP Address: ";
			lAdapters.AddString(Str+chAddr->IpAddress.String);
            
			Str="Subnet Mask: ";
			lAdapters.AddString(Str+chAddr->IpMask.String);

			chAddr = chAddr->Next;
        }
        pAdapter = pAdapter->Next;
	}
}

void CRenewIPAddressDlg::OnBnClickedButton2()
{
	char sAdaptIndex[20];
	int iIndex;
	sAdapterIndex.GetWindowText(sAdaptIndex, 20);
	iIndex = atoi(sAdaptIndex);

    DWORD InterfaceInfoSize = 0;
    PIP_INTERFACE_INFO pInterfaceInfo;

	if (GetInterfaceInfo(NULL, &InterfaceInfoSize) != 
		ERROR_INSUFFICIENT_BUFFER)
	{
		AfxMessageBox("Error sizing buffer");
		return;
    }

    if ((pInterfaceInfo = (PIP_INTERFACE_INFO) GlobalAlloc(GPTR, InterfaceInfoSize)) == NULL)
    {
        AfxMessageBox("Can't allocate memory");
        return;
    }

    if (GetInterfaceInfo(pInterfaceInfo, &InterfaceInfoSize) != 0)
    {
        AfxMessageBox("GetInterfaceInfo failed");
        return;
    }


    for (int i = 0; i < pInterfaceInfo->NumAdapters; i++)
        if (iIndex == pInterfaceInfo->Adapter[i].Index)
        {
            if (IpReleaseAddress(&pInterfaceInfo->Adapter[i]) != 0)
            {
                AfxMessageBox("IpReleaseAddress failed");
                return;
            }
            break;
        }
}

void CRenewIPAddressDlg::OnBnClickedButton3()
{
	char sAdaptIndex[20];
	int iIndex;
	sAdapterIndex.GetWindowText(sAdaptIndex, 20);
	iIndex = atoi(sAdaptIndex);

    DWORD InterfaceInfoSize = 0;
    PIP_INTERFACE_INFO pInterfaceInfo;

	if (GetInterfaceInfo(NULL, &InterfaceInfoSize) != 
		ERROR_INSUFFICIENT_BUFFER)
	{
		AfxMessageBox("Error sizing buffer");
		return;
    }

    if ((pInterfaceInfo = (PIP_INTERFACE_INFO) GlobalAlloc(GPTR, InterfaceInfoSize)) == NULL)
    {
        AfxMessageBox("Can't allocate memory");
        return;
    }

    if (GetInterfaceInfo(pInterfaceInfo, &InterfaceInfoSize) != 0)
    {
        AfxMessageBox("GetInterfaceInfo failed");
        return;
    }


    for (int i = 0; i < pInterfaceInfo->NumAdapters; i++)
        if (iIndex == pInterfaceInfo->Adapter[i].Index)
        {
            if (IpRenewAddress(&pInterfaceInfo->Adapter[i]) != 0)
            {
                AfxMessageBox("IpRenewAddress failed");
                return;
            }
            break;
        }
}
