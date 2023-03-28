#include "TrackBar.h"

#include <CommCtrl.h>


DWORD TrackBar::DEFAULT_STYLES		= TBS_AUTOTICKS | WS_VISIBLE | WS_CHILD | TBS_HORZ;
DWORD TrackBar::DEFAULT_EXSTYLES	= 0;
bool  TrackBar::COMMON_CONTROL_INITIALIZED = false;

TrackBar::TrackBar()
{
}

TrackBar::TrackBar(		int							x,
						int							y,
						int							Width,
						int							Height,
						HINSTANCE					hInstance,
						HWND						hWndParent,
						DWORD						Styles			/*= DEFAULT_STYLES*/,
						DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(											x,
													y,
													Width,
													Height,
													hInstance,
													hWndParent,
													Styles			/*= DEFAULT_STYLES*/,
													ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void TrackBar::Create(	int							x,
						int							y,
						int							Width,
						int							Height,
						HINSTANCE					hInstance,
						HWND						hWndParent,
						DWORD						Styles			/*= DEFAULT_STYLES*/,
						DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_BAR_CLASSES;
		//iccx.dwICC  = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	TRACKBAR_CLASSW,
							/*_In_opt_	LPCTSTR*/	L"Trackbar Control",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) 12745,//NULL,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	//ChooseDefaultFont();
}

void TrackBar::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

TrackBar::~TrackBar()
{
	Destroy();
}

void TrackBar::SetRange(INT Min, INT Max)
{
	SendMessageW(hWnd, TBM_SETRANGEMIN, (WPARAM) TRUE, (LPARAM) Min);
	SendMessageW(hWnd, TBM_SETRANGEMAX, (WPARAM) TRUE, (LPARAM) Max);
}

INT TrackBar::GetLowRange() const
{
	return (INT) SendMessageW(hWnd, TBM_GETRANGEMIN, (WPARAM) NULL, (LPARAM) NULL);
}

INT TrackBar::GetHighRange() const
{
	return (INT) SendMessageW(hWnd, TBM_GETRANGEMAX, (WPARAM) NULL, (LPARAM) NULL);
}

void TrackBar::SetPosition(INT NewPosition)
{
	INT RangeLow  = GetLowRange();
	INT RangeHigh = GetHighRange();
	if (NewPosition > RangeHigh)
	{
		NewPosition = RangeHigh;
	} 
	else if (NewPosition < RangeLow)
	{
		NewPosition = RangeLow;
	}
	SendMessageW(hWnd, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) NewPosition);
}

void TrackBar::SetBodyWindows(const HWND & hWndLeft, const HWND & hWndRight)
{
	SendMessageW(hWnd, TBM_SETBUDDY, TRUE,	(LPARAM) hWndLeft);
	SendMessageW(hWnd, TBM_SETBUDDY, FALSE,	(LPARAM) hWndRight);
}

