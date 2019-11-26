// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSendText.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket(CMFCSendTextDlg* Dlg)
{
		m_Dlg = Dlg;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char recstr[1000];
	int r=Receive(recstr,1000);
	recstr[r]='\0';
	m_Dlg->SetDlgItemText(IDC_STATIC, recstr);

	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_Dlg->m_SendButton.EnableWindow(FALSE);

	CSocket::OnClose(nErrorCode);
}
