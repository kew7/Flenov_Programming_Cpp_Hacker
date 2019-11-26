// TraceRouteDlg.h : header file
//

#pragma once
#include "afxwin.h"

typedef struct tagIP_OPTION_INFORMATION 
{
  unsigned char      Ttl;              
  unsigned char      Tos;              
  unsigned char      Flags;            
  unsigned char      OptionsSize;      
  unsigned char FAR *OptionsData;      
} IP_OPTION_INFORMATION;

typedef struct tagICMP_ECHO_REPLY 
{
  unsigned long         Address;   
  unsigned long         Status;    
  unsigned long         RoundTripTime;
  unsigned short        DataSize;     
  unsigned short        Reserved;     
  void FAR              *Data;        
  IP_OPTION_INFORMATION Options;      
} ICMP_ECHO_REPLY;

typedef IP_OPTION_INFORMATION FAR* LPIP_OPTION_INFORMATION;

typedef HANDLE (WINAPI IcmpCreateFile)(VOID);
typedef IcmpCreateFile* lpIcmpCreateFile;
typedef BOOL (WINAPI IcmpCloseHandle)(HANDLE IcmpHandle);
typedef IcmpCloseHandle* lpIcmpCloseHandle;
typedef DWORD (WINAPI IcmpSendEcho)(HANDLE IcmpHandle, unsigned long DestinationAddress,
                                    LPVOID RequestData, WORD RequestSize,
                                    LPIP_OPTION_INFORMATION RequestOptions,
                                    LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
typedef IcmpSendEcho* lpIcmpSendEcho;

// CTraceRouteDlg dialog
class CTraceRouteDlg : public CDialog
{
// Construction
public:
	CTraceRouteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRACEROUTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HINSTANCE hIcmp;

	static lpIcmpCreateFile pIcmpCreateFile;
	static lpIcmpSendEcho pIcmpSendEcho;
	static lpIcmpCloseHandle pIcmpCloseHandle;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
 	CEdit edHostName;
	CListBox lbMessages;
};

