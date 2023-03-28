#include "G_Main.h"

#include <string>
#include <windows.h>

#include "..\..\KeySize.h"
#include "G_Main_LowLevelInputData.h"


LRESULT CALLBACK WindowMain::LowLevelMouseProc(	_In_ int    nCode,
												_In_ WPARAM wParam,
												_In_ LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(Llid::hHookM, nCode, wParam, lParam);
	}

	if (nCode != HC_ACTION)
	{
		return CallNextHookEx(Llid::hHookM, nCode, wParam, lParam);
	}

	if (wParam == WM_MOUSEMOVE)
	{
		return CallNextHookEx(Llid::hHookM, nCode, wParam, lParam);
	}

	const LRESULT Return = CallNextHookEx(Llid::hHookM, nCode, wParam, lParam);

	MSLLHOOKSTRUCT & MllHook = *reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);
	WindowMain & Window = *static_cast<WindowMain *>(Llid::pWindow);

	if (Window.bProcessIsTerminating)
	{
		return Return;
	}

	/*typedef struct tagMSLLHOOKSTRUCT {
		POINT     pt;
		DWORD     mouseData;
		DWORD     flags;
		DWORD     time;
		ULONG_PTR dwExtraInfo;
	} MSLLHOOKSTRUCT, *LPMSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;*/

	bool bUpdate = false;

	switch (wParam)
	{
		case WM_MOUSEMOVE:
			// Do nothing.
			break;
		case WM_LBUTTONDOWN:
			Llid::MouseL = true;
			bUpdate = true;
			break;
		case WM_LBUTTONUP:
			Llid::MouseL = false;
			bUpdate = true;
			break;
		case WM_MBUTTONDOWN:
			Llid::MouseM = true;
			bUpdate = true;
			break;
		case WM_MBUTTONUP:
			Llid::MouseM = false;
			bUpdate = true;
			break;
		case WM_RBUTTONDOWN:
			Llid::MouseR = true;
			bUpdate = true;
			break;
		case WM_RBUTTONUP:
			Llid::MouseR = false;
			bUpdate = true;
			break;
		case WM_MOUSEWHEEL:
			Llid::nWheelDelta = static_cast<int>(static_cast<signed short>(HIWORD(MllHook.mouseData)));
			Window.Repaint_MouseWheel();
			//CallWindowProcW(/*[in] WNDPROC lpPrevWndFunc	*/	(WNDPROC) GetWindowLongPtrW(Window.Window.hWnd, GWLP_WNDPROC),
			//				/*[in] HWND    hWnd				*/	Window.Window.hWnd,
			//				/*[in] UINT    Msg				*/	Llid::WM_USER_MOUSE_WHEEL,
			//				/*[in] WPARAM  wParam			*/	0,
			//				/*[in] LPARAM  lParam			*/	0);
			bUpdate = false;
			break;
		case WM_MOUSEHWHEEL:
			// Do nothing.
			break;
		default:
			
			break;
	}

	if (bUpdate)
	{
		std::future<void> & Future = Llid::CleanUpCompletedThreadsAndGetMeAnIdleFutre();
		//static_cast<WindowMain *>(Llid::pWindow)->UpdateGraphics();
		Future = std::async(std::launch::async, &WindowMain::UpdateGraphics, static_cast<WindowMain *>(Llid::pWindow));

		//CallWindowProcW(/*[in] WNDPROC lpPrevWndFunc	*/	(WNDPROC) GetWindowLongPtrW(Window.Window.hWnd, GWLP_WNDPROC),
		//				/*[in] HWND    hWnd				*/	Window.Window.hWnd,
		//				/*[in] UINT    Msg				*/	Llid::WM_USER_MOUSE,
		//				/*[in] WPARAM  wParam			*/	0,
		//				/*[in] LPARAM  lParam			*/	0);
	}
	
	return Return;
}

