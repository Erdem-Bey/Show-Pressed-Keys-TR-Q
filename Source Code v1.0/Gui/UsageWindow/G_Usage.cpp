#include "G_Usage.h"

#include <Windows.h>

#include "..\..\Resource.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Gui\Gui.h"


WindowUsage::WindowUsage()
	:	IsCreated	(false)
{
}

WindowUsage::~WindowUsage()
{
}

void WindowUsage::Create()
{
	if (IsCreated)
	{
		return;
	}
	Window.Create(	/*const std::wstring &	WindowClassName*/	Settings::UsageWindow::USGEWND_CLASS,
					/*const std::wstring &	WindowTitle*/		Settings::UsageWindow::USGEWND_TITLE,
					/*HINSTANCE				hInstance*/			Gui::hInstance,
																WindowUsage::MessageProcessor,
					/*int					x*/					Settings::UsageWindow::UsgeWnd_X,
					/*int					y*/					Settings::UsageWindow::UsgeWnd_Y,
					/*int					Width*/				Settings::UsageWindow::USGEWND_W,
					/*int					Height*/			Settings::UsageWindow::USGEWND_H,
					/*DWORD					Styles*/			Settings::UsageWindow::USGEWND_STYLES,
					/*DWORD					ExtendedStyles*/	Settings::UsageWindow::USGEWND_EXSTYLES,
					/*DWORD					ClassStyles*/		Settings::UsageWindow::USGEWND_CLASS_STYLES,
					/*HICON					hIcon*/				LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_USAGE_BIG)),
					/*HICON					hSmallIcon*/		LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_USAGE_SMALL)),
					/*HCURSOR				hCursor*/			LoadCursor(NULL, IDC_ARROW),
					/*HBRUSH				hBackground*/		(HBRUSH) /*CreateSolidBrush(RGB(212,208,200)),//*/COLOR_WINDOW,
					/*LPCWSTR				MenuName*/			NULL,
					/*HMENU					hMenu*/				NULL);
	CreateChildren();
	Gui::MainWnd.Disable_Menu_Help_Usage();
	IsCreated = true;// + dwError;
}

void WindowUsage::Destroy()
{
	if (IsCreated == false)
	{
		return;
	}
	DestroyWindow(Window.hWnd);
	Gui::MainWnd.Enable_Menu_Help_Usage();
	Lines.clear();
	IsCreated = false;
}

void WindowUsage::CreateChildren()
{
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Command Line Options"));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Syntax:"));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT2,	Static(),	L"<ExecutableLocation> [TimingPlan=<TimingPlanType>] [Termination=<TerminationType>] [Countdown=<d.hh:mm:ss> | DateTime=<yyyy-mm-dd.hh:mm:ss>] [AutoStart=Yes] [Force=<Choice>] [InstallUpdates=<Choice>]"));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"ExecutableLocation: Location of the EXE file on the disk. If the path contains the space character, it must be encolosed with quotes (\")."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"TimingPlan: Either \"Countdown\" or \"DateTime\"."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Termination: Either \"Shutdown\", \"Restart\", \"Sleep\", \"Hibernate\" or \"Logout\" (or \"Logoff\")."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Countdown: Number of days (d), hours (hh), minutes (mm) and seconds (ss) untill the desired shutdown operation."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT2,	Static(),	L"DateTime: The date when the shutdown operation to occur. 'yyyy' is the year, the first 'mm' is the month, 'dd' is the day of the month, 'hh' is the hour, the last 'mm' is the minute and 'ss' is the second."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT2,	Static(),	L"AutoStart: Will the countdown start as soon as the program starts? Valid values are \"Yes\", \"No\", \"1\" and \"0\". The default value is \"No\"."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Force: Either \"Yes\", \"No\", \"1\" or \"0\"."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"InstallUpdates: Either \"Yes\", \"No\", \"1\" or \"0\"."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Nothing in this syntax is case sensitive. Your can type \"hiBErnAte\", \"YES\" or \"datetime\"."));/**/
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Example Usage"));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Example 1: Hibernate the computer after one hour."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"\"C:\\Program Files\\Shutdown\\Shutdown.exe\" TimingPlan=Countdown Countdown=0.01:00:00 Termination=Hibernate AutoStart=Yes"));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L""));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"Example 2: Shutdown the computer on 2050, 21st Fabruary, at 18:45."));
	Lines.emplace_back(std::forward_as_tuple(TEXT_HEIGHT,	Static(),	L"\"C:\\Program Files\\Shutdown\\Shutdown.exe\" TimingPlan=DateTime DateTime=2050-02-21.18:45:00 Termination=Shutdown AutoStart=Yes"));
	
	constexpr	int	X0	= 10;
	constexpr	int	Y0	= 10;
				int	Y	= Y0;
	for (size_t i=0; i<Lines.size(); i++)
	{
		const	int				&	Height	= std::get<0>(Lines[i]);
				Static			&	Control	= std::get<1>(Lines[i]);
		const	std::wstring	&	Text	= std::get<2>(Lines[i]);
		Control.Create(X0, Y, TEXT_WIDTH, Height, Gui::hInstance, Window.hWnd, Text.c_str(), LINE_ID_START + i, Static::DEFAULT_STYLES | SS_LEFT,	Static::DEFAULT_EXSTYLES);
		Y += Height;
	}
	
	std::get<1>(Lines[ 0]).UpdateFontProperty_Weight(600);
	std::get<1>(Lines[15]).UpdateFontProperty_Weight(600);
}

LRESULT CALLBACK WindowUsage::MessageProcessor(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
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
		/*case WM_PAINT:
		{
			ULONG_PTR gdiplusToken;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			{	//Scope to ensure Graphics and Image are destructed before GdiplusShutdown
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Image image(L"Graphics\\About.jpg");
				graphics.DrawImage(&image, (Settings::UsageWindow::USGEWND_W - image.GetWidth()) / 2, 10);
			}
			Gdiplus::GdiplusShutdown(gdiplusToken);
			EndPaint(hWnd, &ps); 
			break;
		}*/
		case WM_DESTROY:
			Gui::UsgeWnd.Destroy();
			break;
		/*case WM_NOTIFY:
			switch (((LPNMHDR)lParam)->code)
			{
				case NM_CLICK:
				case NM_RETURN:
				{
					NMLINK &	NmLink = *((PNMLINK) lParam);
					LITEM &		item    = NmLink.item;
					NMHDR &		hdr		= NmLink.hdr;
					if ((((LPNMHDR)lParam)->hwndFrom == Gui::UsgeWnd.Web.hWnd) && (item.iLink == 0))
					{
						ShellExecuteW(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
					}
				}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}*/
		case WM_MOVE:
			RECT Rect;
			GetWindowRect(hWnd, &Rect);
			Settings::UsageWindow::UsgeWnd_X = Rect.left;
			Settings::UsageWindow::UsgeWnd_Y = Rect.top;
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void WindowUsage::ChangeGuiLanguage()
{

}

