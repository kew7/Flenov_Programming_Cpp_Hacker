// Start Button.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Start Button.h"
#define MAX_LOADSTRING 100

// Global Variables:
HWND hWnd;
HBITMAP startBitmap;
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void DrawStartButton()
{
 int i;
 int toppos=GetSystemMetrics(SM_CYSCREEN)-23;

 //Отображаем окно
 ShowWindow(hWnd, SW_SHOW);
 //Установить верхнюю позицию окна в левый нижний угол экрана.
 SetWindowPos(hWnd, HWND_TOPMOST, 4, toppos, 50, 20, SWP_SHOWWINDOW);
 UpdateWindow(hWnd);

 //Сейчас будем подымать кнопку
 // От 1 до 80 выполнять действия от begin до end for i:=1 to 80 do
 for (i=0; i<50; i++)
 {
		toppos=toppos-4;
		SetWindowPos(hWnd, HWND_TOPMOST, 4, toppos, 50, 20, SWP_SHOWWINDOW);
		Sleep(15);//Задержка в 5 миллисекунд
 }

 for (i=50; i>0; i--)
 {
		toppos=toppos+4;
		SetWindowPos(hWnd, HWND_TOPMOST, 4, toppos, 50, 20, SWP_SHOWWINDOW);
		Sleep(15);//Задержка в 5 миллисекунд
 }
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
	LoadString(hInstance, IDC_STARTBUTTON, szWindowClass, MAX_LOADSTRING);

    startBitmap = (HBITMAP)::LoadImage(hInstance, 
      MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);
	
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_STARTBUTTON);

	DrawStartButton();
    
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		DrawStartButton();
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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

	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_STARTBUTTON);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= "";
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
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   int Style;
   Style = GetWindowLong(hWnd, GWL_STYLE);
   Style=Style || WS_CAPTION;
   Style=Style || WS_SYSMENU;
   SetWindowLong(hWnd, GWL_STYLE, Style);

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
	HDC hdcBits;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
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
		Rectangle(hdc, 1,1,10,10);
		hdcBits=::CreateCompatibleDC(hdc);
		SelectObject(hdcBits,startBitmap);
		BitBlt(hdc, 0, 0, 50, 20, hdcBits, 0, 0, SRCCOPY);
		DeleteDC(hdcBits);
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
