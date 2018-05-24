// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		myhookdata[WH_KEYBOARD_LL].nType = WH_KEYBOARD_LL;
		myhookdata[WH_KEYBOARD_LL].hkprc = LowLevelKeyboardProc;
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

