#pragma once



// CClientSocket command target

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnConnect(int nErrorCode);
};


