// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSendText.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket(CMFCSendTextDlg* Dlg)
{
	m_Dlg = Dlg;
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket member functions

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox("New connection accepted");
	m_Dlg->AddConnection();

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnConnect(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnClose(nErrorCode);
}
