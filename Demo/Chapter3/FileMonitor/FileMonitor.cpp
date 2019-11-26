// FileMonitor.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
#include "stdafx.h"
#include "FileMonitor.h"

HHOOK SysHook;
HINSTANCE hInst;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	hInst=(HINSTANCE)hModule;
    return TRUE;
}

LRESULT CALLBACK SysMsgProc(

    int code,	// hook code
    WPARAM wParam,	// removal flag
    LPARAM lParam 	// address of structure with message
   )
{
	//ѕередать сообщение другим ловушкам в системе
	CallNextHookEx(SysHook, code, wParam, lParam);

	if (code == HCBT_ACTIVATE)
	{
		char windtext[255];
		HWND Wnd=((tagMSG*)lParam)->hwnd;
		GetWindowText(Wnd, windtext, 255);		
		
		//You can save active file title
	}

	if (code == HCBT_CREATEWND)
	{
		char windtext[255];
		HWND Wnd=((tagMSG*)lParam)->hwnd;
		GetWindowText(Wnd, windtext, 255);		
		
		//You can save active file title
	}
	return 0;
}

///////////////////////////////////////////////////////////////////

DllExport void RunStopHook(bool State, HINSTANCE hInstance)
{
	if (true)
		SysHook = SetWindowsHookEx(WH_CBT, &SysMsgProc, hInst, 0);
	else
        UnhookWindowsHookEx(SysHook);
}

