// OpenPassDLL.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
#include "stdafx.h"
#include "OpenPassDLL.h"

HHOOK SysHook;
HWND Wnd;
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
	//�������� ��������� ������ �������� � �������
	CallNextHookEx(SysHook, code, wParam, lParam);

	//�������� ���������
	if (code == HC_ACTION)
	{
		//������� ������������� ���� ���������������� ���������
		Wnd=((tagMSG*)lParam)->hwnd;

		//�������� ��� ���������. 
		//���� ���� ������ ����� ������ ���� 
		//� �������� ������ Control, �� ...
        if (((tagMSG*)lParam)->message == WM_LBUTTONDOWN)
		{
			SendMessage(Wnd, EM_SETPASSWORDCHAR, 100, 0); 
			InvalidateRect(Wnd, 0, true);
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////

DllExport void RunStopHook(bool State, HINSTANCE hInstance)
{
	if (true)
		SysHook = SetWindowsHookEx(WH_GETMESSAGE, &SysMsgProc, hInst, 0);
	else
        UnhookWindowsHookEx(SysHook);
}

