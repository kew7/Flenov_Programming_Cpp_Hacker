// PingerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <winsock2.h>

#define ICMP_ECHOREQ	8


// CPingerDlg dialog
class CPingerDlg : public CDialog
{
// Construction
public:
	CPingerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PINGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edHost;
	afx_msg void OnBnClickedButton1();
	CListBox lMessages;
};

// ICMP Header - RFC 792
typedef struct tagICMPHDR
{
	u_char	Type;			
	u_char	Code;			
	u_short	Checksum;		
	u_short	ID;			
	u_short	Seq;			
	char	Data;			
}ICMPHDR, *PICMPHDR;

typedef struct tagECHOREQUEST
{
	ICMPHDR icmpHdr;
	DWORD	dwTime;
	char	cData[64];
}ECHOREQUEST, *PECHOREQUEST;

// IP Header -- RFC 791
typedef struct tagIPHDR
{
	u_char  VIHL;			
	u_char	TOS;			
	short	TotLen;			
	short	ID;			
	short	FlagOff;		
	u_char	TTL;			
	u_char	Protocol;		
	u_short	Checksum;		
	struct	in_addr iaSrc;
	struct	in_addr iaDst;	
}IPHDR, *PIPHDR;

typedef struct tagECHOREPLY
{
	IPHDR	ipHdr;
	ECHOREQUEST	echoRequest;
	char    cFiller[256];
}ECHOREPLY, *PECHOREPLY;
