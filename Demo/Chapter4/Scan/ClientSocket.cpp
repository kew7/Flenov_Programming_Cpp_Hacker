// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCScan.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions

void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CSocket::OnConnect(nErrorCode);
}
