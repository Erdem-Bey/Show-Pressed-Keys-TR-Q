#include "Calendar.h"

#include <CommCtrl.h>
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

DWORD Calendar::DEFAULT_STYLES				= WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_DAYSTATE;
DWORD Calendar::DEFAULT_EXSTYLES			= 0;
bool  Calendar::COMMON_CONTROL_INITIALIZED	= false;

Calendar::Calendar()
{
}

Calendar::Calendar(			int							x,
							int							y,
							int							Width,
							int							Height,
							HINSTANCE					hInstance,
							HWND						hWndParent,
							const std::wstring &		Content			/*= std::wstring()*/,
							WORD						Identifier		/*= 0*/,
							DWORD						Styles			/*= DEFAULT_STYLES*/,
							DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(												x,
														y,
														Width,
														Height,
														hInstance,
														hWndParent,
														Content			/*= std::wstring()*/,
														Identifier		/*= 0*/,
														Styles			/*= DEFAULT_STYLES*/,
														ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void Calendar::Create(		int							x,
							int							y,
							int							Width,
							int							Height,
							HINSTANCE					hInstance,
							HWND						hWndParent,
							const std::wstring &		Content			/*= std::wstring()*/,
							WORD						Identifier		/*= 0*/,
							DWORD						Styles			/*= DEFAULT_STYLES*/,
							DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_DATE_CLASSES;	// CommCtrl.h: #define ICC_LINK_CLASS 0x00000100
		/*bool bResult =*/ InitCommonControlsEx(&iccx);
		//DWORD dwError = GetLastError();
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	MONTHCAL_CLASSW, // CommCtrl.h: #define MONTHCAL_CLASSW L"SysMonthCal32"
							/*_In_opt_	LPCTSTR*/	Content.c_str(),
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Identifier,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	//DWORD dw = GetLastError();
	RECT Rect;
	MonthCal_GetMinReqRect	(hWnd, &Rect);
	SetWindowPos			(hWnd, NULL, x, y, Rect.right, Rect.bottom, SWP_NOZORDER);
	StorePositionAndSize	(x, y, Rect.right - x, Rect.bottom - y);
	MonthCal_SetCurrentView	(hWnd, MCMV_MONTH);
	ChooseDefaultFont();
}

void Calendar::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

Calendar::~Calendar()
{
	Destroy();
}

SYSTEMTIME Calendar::GetCurrentDateTime() const
{
	SYSTEMTIME SystemTime;
	SendMessageW(hWnd, MCM_GETCURSEL, static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(&SystemTime));
	return SystemTime;
}

void Calendar::SetCurrentDateTime(const SYSTEMTIME & SystemTime)
{
	SendMessageW(hWnd, MCM_SETCURSEL, static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(&SystemTime));
}
