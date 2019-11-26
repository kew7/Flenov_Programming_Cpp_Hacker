// TCPServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <winsock2.h>
#include "TCPServer.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI NetThread(LPVOID lpParam)
{
    SOCKET sServerListen;
	SOCKET ClientSockets[50];
	int TotalSocket=0;

    struct sockaddr_in localaddr,
                       clientaddr;
    int           iSize;

	sServerListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sServerListen == SOCKET_ERROR)
    {
		MessageBox(0, "Can't load WinSock", "Error", 0);
        return 0;
    }

	ULONG ulBlock;
	ulBlock = 1;
	if (ioctlsocket(sServerListen, FIONBIO, &ulBlock) == SOCKET_ERROR)
	{
		return 0;
	}

    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localaddr.sin_family = AF_INET;
    localaddr.sin_port = htons(5050);

    if (bind(sServerListen, (struct sockaddr *)&localaddr, 
            sizeof(localaddr)) == SOCKET_ERROR)
    {
		MessageBox(0, "Can't bind", "Error", 0);
        return 1;
    }
    
    MessageBox(0, "Bind OK", "Error", 0);

    listen(sServerListen, 4);

    MessageBox(0, "Listen OK", "Error", 0);

	FD_SET ReadSet;
	int ReadySock;

    while (1)
    {
		FD_ZERO(&ReadSet);
		FD_SET(sServerListen, &ReadSet);

		for (int i=0; i<TotalSocket; i++)
			if (ClientSockets[i] != INVALID_SOCKET)
				FD_SET(ClientSockets[i], &ReadSet);


		if ((ReadySock = select(0, &ReadSet, NULL, NULL, NULL)) == SOCKET_ERROR)
		{
			MessageBox(0, "Select filed", "Error", 0);
		}

		//We have new connection
		if (FD_ISSET(sServerListen, &ReadSet))
		{
			iSize = sizeof(clientaddr);
	        ClientSockets[TotalSocket] = accept(sServerListen, (struct sockaddr *)&clientaddr,
				            &iSize);        
			if (ClientSockets[TotalSocket] == INVALID_SOCKET)
	        {        
				MessageBox(0, "Accept filed", "Error", 0);
	            break;
			}
			TotalSocket++;
		}
		//We have data from client
		for (int i=0; i<TotalSocket; i++)
		{
			if (ClientSockets[i] == INVALID_SOCKET)
				continue;
			if (FD_ISSET(ClientSockets[i], &ReadSet))
			{
			    char szRecvBuff[1024],
					 szSendBuff[1024];

				int ret = recv(ClientSockets[i], szRecvBuff, 1024, 0);
        if (ret == 0)
		{
            closesocket(ClientSockets[i]);
			ClientSockets[i]=INVALID_SOCKET;
			break;
		}
        else if (ret == SOCKET_ERROR)
        {
			MessageBox(0, "Recive data filed", "Error", 0);
            break;
        }
        szRecvBuff[ret] = '\0';

		strcpy(szSendBuff, "Command get OK");

        ret = send(ClientSockets[i], szSendBuff, sizeof(szSendBuff), 0);
        if (ret == SOCKET_ERROR)
        {
           break;
        }
			}
		}

    }
    closesocket(sServerListen);
    return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TCPSERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_TCPSERVER);

    WSADATA       wsd;
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		MessageBox(0, "Can't load WinSock", "Error", 0);
		return 0;
	}

    HANDLE        hNetThread;
    DWORD         dwNetThreadId;
	hNetThread = CreateThread(NULL, 0, NetThread, 
                    0, 0, &dwNetThreadId);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
    }
    
    WSACleanup();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TCPSERVER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_TCPSERVER;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
