// FastScan.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FastScan.h"
#include "FastScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFastScanApp

BEGIN_MESSAGE_MAP(CFastScanApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFastScanApp construction

CFastScanApp::CFastScanApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CFastScanApp object

CFastScanApp theApp;


// CFastScanApp initialization

BOOL CFastScanApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CFastScanDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
