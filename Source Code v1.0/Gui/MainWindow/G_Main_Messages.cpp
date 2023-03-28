#include "G_Main.h"

#include <thread>
#include <vector>
#include <string>
#include <windows.h>

#include <gdiplus.h>
//#pragma comment (lib, "gdiplus")

#include "..\..\Settings\Settings.h"
#include "..\..\Gui\Gui.h"
#include "G_Main_LowLevelInputData.h"


LRESULT CALLBACK WindowMain::MessageProcessor(	_In_ HWND	hWnd,
												_In_ UINT	uMsg,
												_In_ WPARAM	wParam,
												_In_ LPARAM	lParam)
{
	WORD wmId, wmEvent;
	LRESULT lResult;
	static bool bMouseDown = false;
	static POINT pointMouseLastLocation;
	
	switch (uMsg)
	{
		/*case Llid::WM_USER_KEYBOARD:
		case Llid::WM_USER_MOUSE:
			Gui::MainWnd.UpdateGraphics();
			break;
		case Llid::WM_USER_MOUSE_WHEEL:
			Gui::MainWnd.Repaint_MouseWheel();
			break;*/
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case ID_BT_Close:
					switch (wmEvent)
					{
						case BN_CLICKED:
							UnhookWindowsHookEx(Llid::hHookK);
							UnhookWindowsHookEx(Llid::hHookM);
							Gui::MainWnd.bProcessIsTerminating = true;
							Llid::WaitForAllThreadsToComplete();
							Gui::MainWnd.Destroy();
							DestroyWindow(Gui::MainWnd.Window.hWnd);
							break;
					}
					break;
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_WINDOWPOSCHANGED:
			//if (uMsg == 5) // SIZE_RESTORED)
			{
				const WINDOWPOS & Wp = *reinterpret_cast<WINDOWPOS *>(lParam);
				Settings::MainWindow::MainWnd_X = Wp.x;
				Settings::MainWindow::MainWnd_Y = Wp.y;
				Settings::MainWindow::MainWnd_W = Wp.cx;
				Settings::MainWindow::MainWnd_H = Wp.cy;
				Gui::MainWnd.UpdateGraphics();
			}
			//RedrawWindow(reinterpret_cast<WindowMain*>(Llid::pWindow)->tbOpacity.hWnd, NULL, NULL, RDW_INTERNALPAINT);
			//UpdateWindow(reinterpret_cast<WindowMain*>(Llid::pWindow)->tbOpacity.hWnd);
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;/**/
		/*case WM_SIZE:
			if (uMsg == 5) // SIZE_RESTORED)
			{
				RECT Rect;
				GetWindowRect(hWnd, &Rect);
				//const WINDOWPOS & Wp = *reinterpret_cast<WINDOWPOS *>(lParam);
				Settings::MainWindow::MainWnd_X = Rect.left;
				Settings::MainWindow::MainWnd_Y = Rect.right;
				Settings::MainWindow::MainWnd_W = LOWORD(lParam);
				Settings::MainWindow::MainWnd_H = HIWORD(lParam);
				Gui::MainWnd.UpdateGraphics();
			}
			//RedrawWindow(reinterpret_cast<WindowMain*>(Llid::pWindow)->tbOpacity.hWnd, NULL, NULL, RDW_INTERNALPAINT);
			//UpdateWindow(reinterpret_cast<WindowMain*>(Llid::pWindow)->tbOpacity.hWnd);
			//return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;*/
		case WM_NCHITTEST:
		{
			LRESULT hit = DefWindowProc(hWnd, uMsg, wParam, lParam);
			if (hit == HTCLIENT) hit = HTCAPTION;
			return hit;
		}
		case WM_HSCROLL:
		{
			const WORD wEvent = LOWORD(wParam);
			switch (wEvent)
			{
				case TB_THUMBPOSITION:
				case TB_THUMBTRACK:
					const WORD wPosition = HIWORD(wParam);
					Settings::MainWindow::Opacity = wPosition;
					reinterpret_cast<WindowMain*>(Llid::pWindow)->UpdateGraphics();
					break;
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
			break;
		case WM_ERASEBKGND:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		/*case WM_CTLCOLORBTN:
		case WM_CTLCOLORSTATIC:
		{
			wchar_t  class_Name[100];
			GetClassName(hWnd, class_Name, 100);
			WNDCLASS lpcls{};
			GetClassInfo(Gui::hInstance, class_Name, &lpcls);
			return  (LRESULT) lpcls.hbrBackground;
		}*/
		case WM_PAINT:
		{
			Gui::MainWnd.UpdateGraphics();
			LRESULT lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);
			return lResult;
			break;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}


