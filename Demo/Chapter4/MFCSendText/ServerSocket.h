#pragma once

#include "MFCSendTextDlg.h"

// CServerSocket command target

class CServerSocket : public CSocket
{
public:
	CServerSocket(CMFCSendTextDlg* Dlg);
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
protected:
	CMFCSendTextDlg* m_Dlg;
public:
	virtual void OnClose(int nErrorCode);
};


