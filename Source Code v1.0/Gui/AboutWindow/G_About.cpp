#include "G_About.h"

#include <Windows.h>
#include <gdiplus.h>
//#pragma comment (lib, "gdiplus")

#include "..\..\Resource.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Gui\Gui.h"


// Gdiplus::Image WindowAbout::image(L"Graphics\\About.jpg");
// int WindowAbout::image_x = (Settings::ABUTWND_W - image.GetWidth()) / 2;
// int WindowAbout::image_y = 5;

WindowAbout::WindowAbout()
	:	IsCreated	(false)
{
}

WindowAbout::~WindowAbout()
{
}

void WindowAbout::Create()
{
	if (IsCreated)
	{
		return;
	}
	Window.Create(	/*const std::wstring &	WindowClassName*/	Settings::AboutWindow::ABUTWND_CLASS,
					/*const std::wstring &	WindowTitle*/		Settings::AboutWindow::ABUTWND_TITLE,
					/*HINSTANCE				hInstance*/			Gui::hInstance,
																WindowAbout::MessageProcessor,
					/*int					x*/					Settings::AboutWindow::AbutWnd_X,
					/*int					y*/					Settings::AboutWindow::AbutWnd_Y,
					/*int					Width*/				Settings::AboutWindow::ABUTWND_W,
					/*int					Height*/			Settings::AboutWindow::ABUTWND_H,
					/*DWORD					Styles*/			Settings::AboutWindow::ABUTWND_STYLES,
					/*DWORD					ExtendedStyles*/	Settings::AboutWindow::ABUTWND_EXSTYLES,
					/*DWORD					ClassStyles*/		Settings::AboutWindow::ABUTWND_CLASS_STYLES,
					/*HICON					hIcon*/				LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_ABOUT_BIG)),
					/*HICON					hSmallIcon*/		LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_ABOUT_SMALL)),
					/*HCURSOR				hCursor*/			LoadCursor(NULL, IDC_ARROW),
					/*HBRUSH				hBackground*/		(HBRUSH) /*CreateSolidBrush(RGB(212,208,200)),//*/COLOR_WINDOW,
					/*LPCWSTR				MenuName*/			NULL,
					/*HMENU					hMenu*/				NULL);
	CreateChildren();
	//hLogo = (HICON) LoadImageW(Gui::hInstance, L"Graphics\\About.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT*0);
	//DWORD dwError = GetLastError();
	//Gui::MainWnd.Disable_Menu_Help_About();
	IsCreated = true;// + dwError;
}

void WindowAbout::Destroy()
{
	if (IsCreated == false)
	{
		return;
	}
	DestroyWindow(Window.hWnd);
	//DestroyIcon(hLogo);
	//Gui::MainWnd.Enable_Menu_Help_About();
	IsCreated = false;
}

LRESULT CALLBACK WindowAbout::MessageProcessor(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	WORD wmId, wmEvent;
	LRESULT lResult;
	NMHDR * pNmHdr;
	LPNMLISTVIEW pNmLv;
	//PAINTSTRUCT ps;
	//HDC hdc;
	switch (uMsg)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			//switch (wmId)
			//{
			//	case ID_BUTTON1:
			//		Gui::GI()->SettWnd.SttsBar.SetPartText(2, L"Button 1");
			//		switch (wmEvent)
			//		{
			//			case BN_CLICKED:
			//				Gui::GI()->SettWnd.SttsBar.SetPartText(3, L"Clicked");
			//				break;
			//		}
			//		break;
			//}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
			// 	case WM_PAINT:
			// 		hdc = BeginPaint(hWnd, &ps);
			// 		// TODO: Add any drawing code here...
			// 		EndPaint(hWnd, &ps);
			// 		break;
		case WM_DRAWITEM:
			//DrawIconEx(((LPDRAWITEMSTRUCT) lParam)->hDC, LOGO_X, LOGO_Y, Gui::GI()->AbutWnd.hLogo, 0, 0, 0, NULL, DI_NORMAL);
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		case WM_PAINT:
		{
			ULONG_PTR gdiplusToken;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			{/* Scope to ensure Graphics and Image are destructed before GdiplusShutdown */
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Image image(L"Graphics\\About.jpg");
				graphics.DrawImage(&image, (Settings::AboutWindow::ABUTWND_W - image.GetWidth()) / 2, 10);
			}
			Gdiplus::GdiplusShutdown(gdiplusToken);
			EndPaint(hWnd, &ps); 
			break;
		}
		case WM_DESTROY:
			Gui::AbutWnd.Destroy();
			break;
		case WM_NOTIFY:
			switch (((LPNMHDR)lParam)->code)
			{
				case NM_CLICK:
				case NM_RETURN:
				{
					NMLINK &	NmLink = *((PNMLINK) lParam);
					LITEM &		item    = NmLink.item;
					NMHDR &		hdr		= NmLink.hdr;
					if ((((LPNMHDR)lParam)->hwndFrom == Gui::AbutWnd.Web.hWnd) && (item.iLink == 0))
					{
						ShellExecuteW(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
					}
				}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
		case WM_MOVE:
			RECT Rect;
			GetWindowRect(hWnd, &Rect);
			Settings::AboutWindow::AbutWnd_X = Rect.left;
			Settings::AboutWindow::AbutWnd_Y = Rect.top;
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void WindowAbout::ChangeGuiLanguage()
{

}

