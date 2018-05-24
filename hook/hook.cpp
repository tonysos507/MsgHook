// hook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Strsafe.h"

BOOL InstallHook(int HookType, HWND hWnd)
{
	if (myhookdata.find(HookType) != myhookdata.end())
	{
		HINSTANCE hinstDll;
		GetModuleHandleEx(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			(LPCTSTR)InstallHook,
			&hinstDll);

		if (hinstDll)
		{
			myhookdata[HookType].hhook = SetWindowsHookEx(myhookdata[HookType].nType,
				myhookdata[HookType].hkprc, hinstDll, 0);

			if (myhookdata[HookType].hhook)
			{
				myhookdata[HookType].hwnd = hWnd;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL UnInstallHook(int HookType)
{
	if (myhookdata.find(HookType) != myhookdata.end())
	{
		UnhookWindowsHookEx(myhookdata[HookType].hhook);
	}
	return TRUE;
}

LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (nCode < 0)
		return CallNextHookEx(myhookdata[WH_KEYBOARD_LL].hhook, nCode, wParam, lParam);

	HDC hdc;
	HRESULT hResult;
	TCHAR szBuf[128];
	size_t cch;
	hdc = GetDC(myhookdata[WH_KEYBOARD_LL].hwnd);
	
	hResult = StringCchPrintf(szBuf, 128 / sizeof(TCHAR), L"KEYBOARD - code: %d, vk: %d", nCode, ((PKBDLLHOOKSTRUCT)lParam)->vkCode);
	hResult = StringCchLength(szBuf, 128 / sizeof(TCHAR), &cch);

	TextOut(hdc, 2, 115, szBuf, cch);
	ReleaseDC(myhookdata[WH_KEYBOARD_LL].hwnd, hdc);

	return CallNextHookEx(myhookdata[WH_KEYBOARD_LL].hhook, nCode, wParam, lParam);
}