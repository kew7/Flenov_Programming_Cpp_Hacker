#pragma once

#include "MFCSendTextDlg.h"


// CClientSocket command target

class CClientSocket : public CSocket
{
public:
	CClientSocket(CMFCSendTextDlg* Dlg);
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
protected:
	CMFCSendTextDlg* m_Dlg;
};


