#include "G_Main.h"

#include <string>
#include <thread>
#include <windows.h>

#include "..\..\KeySize.h"
#include "G_Main_LowLevelInputData.h"

LRESULT CALLBACK WindowMain::LowLevelKeyboardProc(	_In_ int    nCode,
													_In_ WPARAM wParam,
													_In_ LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(Llid::hHookK, nCode, wParam, lParam);
	}

	const LRESULT Return = CallNextHookEx(Llid::hHookK, nCode, wParam, lParam);

	KBDLLHOOKSTRUCT & KllHook = *reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
	WindowMain & Window = *static_cast<WindowMain *>(Llid::pWindow);

	if (Window.bProcessIsTerminating)
	{
		return Return;
	}

	/*typedef struct tagKBDLLHOOKSTRUCT
	{
		DWORD     vkCode;
		DWORD     scanCode;
		DWORD     flags;
		DWORD     time;
		ULONG_PTR dwExtraInfo;
	} KBDLLHOOKSTRUCT, *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;*/

	bool bKeyDown = false;
	bool bKeyUp = false;

	switch (wParam)
	{
		case WM_KEYDOWN:
			bKeyDown = true;
			switch (KllHook.vkCode)
			{
				case VK_RETURN:
					if (KllHook.flags == 0x00)
					{
						KllHook.vkCode += 0xFF00;
						Llid::EnterPressed = true;
					}
					break;
				/*case VK_NUMLOCK:
					if ((GetKeyState(VK_NUMLOCK) & 0x0001) == 0x0001)
					{
						Llid::LedNumber = true;
					}
					break;
				case VK_CAPITAL:
					if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0x0001)
					{
						Llid::LedCaps = true;
					}
					break;
				case VK_SCROLL:
					if ((GetKeyState(VK_SCROLL) & 0x0001) == 0x0001)
					{
						Llid::LedScroll = true;
					}
					break;*/
			}
			break;
		case WM_KEYUP:
			bKeyUp = true;
			switch (KllHook.vkCode)
			{
				case VK_RETURN:
					if (KllHook.flags == 0x80)
					{
						KllHook.vkCode += 0xFF00;
						Llid::EnterPressed = false;
					}
					break;
				/*case VK_NUMLOCK:
					if ((GetKeyState(VK_NUMLOCK) & 0x0001) == 0x0000)
					{
						Llid::LedNumber = false;
					}
					break;
				case VK_CAPITAL:
					if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0x0000)
					{
						Llid::LedCaps = false;
					}
					break;
				case VK_SCROLL:
					if ((GetKeyState(VK_SCROLL) & 0x0001) == 0x0000)
					{
						Llid::LedScroll = false;
					}
					break;*/
			}
			break;
		case WM_SYSKEYDOWN:
			switch (KllHook.vkCode)
			{
				case VK_LMENU:
					bKeyDown = true;
					break;
				case VK_RMENU:
					bKeyDown = true;
					break;
			}
			break;
		case WM_SYSKEYUP:
			switch (KllHook.vkCode)
			{
				case VK_LMENU:
					bKeyUp = true;
					break;
				case VK_RMENU:
					bKeyUp = true;
					break;
			}
			break;
		default :
			
			break;
	}

	auto Lambda1 = [&] ()
	{
		for (size_t i=0; i<Llid::KeysLarge.size(); i++)
		{
			if (Llid::KeysLarge[i].VirtualKeyCode == KllHook.vkCode)
			{
				if (bKeyDown)
				{
					Llid::KeysLarge[i].Pressed = true;
				}
				else if (bKeyUp)
				{
					Llid::KeysLarge[i].Pressed = false;
				}
			}
		}
	};

	auto Lambda2 = [&] ()
	{
		for (size_t i=0; i<Llid::KeysSmall.size(); i++)
		{
			if (Llid::KeysSmall[i].VirtualKeyCode == KllHook.vkCode)
			{
				if (bKeyDown)
				{
					Llid::KeysSmall[i].Pressed = true;
				}
				else if (bKeyUp)
				{
					Llid::KeysSmall[i].Pressed = false;
				}
			}
		}
	};
	
	std::thread t1(Lambda1);
	std::thread t2(Lambda2);

	//auto Lambda3 = [&] ()
	{
		if ((GetKeyState(VK_NUMLOCK) & 0x0001) == 0x0001)
		{
			Llid::LedNumber = true;
		}
		else
		{
			Llid::LedNumber = false;
		}
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0x0001)
		{
			Llid::LedCaps = true;
		}
		else
		{
			Llid::LedCaps = false;
		}
		if ((GetKeyState(VK_SCROLL) & 0x0001) == 0x0001)
		{
			Llid::LedScroll = true;
		}
		else
		{
			Llid::LedScroll = false;
		}
	};
	
	t1.join();
	t2.join();

	std::future<void> & Future = Llid::CleanUpCompletedThreadsAndGetMeAnIdleFutre();
	//Window.UpdateGraphics();
	Future = std::async(std::launch::async, &WindowMain::UpdateGraphics, &Window);

	//CallWindowProcW(/*[in] WNDPROC lpPrevWndFunc	*/	(WNDPROC) GetWindowLongPtrW(Window.Window.hWnd, GWLP_WNDPROC),
	//				/*[in] HWND    hWnd				*/	Window.Window.hWnd,
	//				/*[in] UINT    Msg				*/	Llid::WM_USER_KEYBOARD,
	//				/*[in] WPARAM  wParam			*/	0,
	//				/*[in] LPARAM  lParam			*/	0);

	return Return;
}

