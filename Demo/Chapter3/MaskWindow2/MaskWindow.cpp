// MaskWindow.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MaskWindow.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP maskBitmap;
HWND hWnd;
bool dragging=false;
POINT MousePnt;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_MASKWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MASKWINDOW);

	//Следующий код вы должны добавить
	int Style;
	Style = GetWindowLong(hWnd, GWL_STYLE);
	Style=Style || WS_CAPTION;
	Style=Style || WS_SYSMENU;
	SetWindowLong(hWnd, GWL_STYLE, Style);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	maskBitmap = (HBITMAP)LoadImage(NULL, "mask.bmp", 
                               IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!maskBitmap) return NULL;

	BITMAP bi;
	BYTE bpp;
	DWORD TransPixel;
	DWORD pixel;
	int startx;
	INT i, j;
	HRGN Rgn, ResRgn = CreateRectRgn(0, 0, 0, 0);

	GetObject(maskBitmap, sizeof( BITMAP ), &bi);

	bpp = bi.bmBitsPixel >> 3;

	BYTE *pBits = new BYTE[ bi.bmWidth * bi.bmHeight * bpp ];

	int  p = GetBitmapBits( maskBitmap, bi.bmWidth * bi.bmHeight * bpp, pBits );

	TransPixel = *(DWORD*)pBits;

	TransPixel <<= 32 - bi.bmBitsPixel;

	for (i = 0; i < bi.bmHeight; i++)
	{
		startx=-1;
		for (j = 0; j < bi.bmWidth; j++)
		{
			pixel = *(DWORD*)(pBits + (i * bi.bmWidth +
					j) * bpp) << (32 - bi.bmBitsPixel);
			if (pixel != TransPixel)
			{
				if (startx<0)
				{
					startx = j;
				} else if (j == (bi.bmWidth - 1))
				{
					Rgn = CreateRectRgn( startx, i, j, i + 1 );
					CombineRgn( ResRgn, ResRgn, Rgn, RGN_OR);
					startx=-1;
				}
			} else if (startx>=0)
			{
				Rgn = CreateRectRgn(startx, i, j, i + 1);
				CombineRgn(ResRgn, ResRgn, Rgn, RGN_OR);
				startx=-1;
			}
		}
	}
	delete[] pBits;
	SetWindowRgn(hWnd, ResRgn, TRUE);
	InvalidateRect(hWnd, 0, false);
	//Конец добавляемого кода


   // Main message loop:
	while (GetMessage(&msg, NULL, 0, false)) 
	{
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MASKWINDOW);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 200, 200, NULL, NULL, hInstance, NULL);

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
	HDC hdcBits;

	RECT wndrect;
	POINT point;

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
		hdcBits=::CreateCompatibleDC(hdc);
		SelectObject(hdcBits, maskBitmap);
		BitBlt(hdc, 0, 0, 200, 200, hdcBits, 0, 0, SRCCOPY);
		DeleteDC(hdcBits);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
			GetCursorPos(&MousePnt);
			dragging = true;
			SetCapture(hWnd);
		break;
	case WM_MOUSEMOVE:
		if (dragging)
		{
			GetCursorPos(&point);
			GetWindowRect(hWnd, &wndrect);

			wndrect.left = wndrect.left+(point.x - MousePnt.x);
			wndrect.top  = wndrect.top +(point.y - MousePnt.y);

			SetWindowPos(hWnd, NULL, wndrect.left, wndrect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			MousePnt=point;
		}
		break;
	case WM_LBUTTONUP:
		if (dragging)
		{
			dragging=false;
			ReleaseCapture();
		}
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
