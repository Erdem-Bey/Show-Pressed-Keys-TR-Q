#include "MonthCalendar.h"

#include <CommCtrl.h>


DWORD MonthCalendar::DEFAULT_STYLES	= WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_DAYSTATE;
DWORD MonthCalendar::DEFAULT_EXSTYLES	= 0;
bool  MonthCalendar::COMMON_CONTROL_INITIALIZED = false;

MonthCalendar::MonthCalendar()
{
}

MonthCalendar::MonthCalendar(	int							x,
								int							y,
								//int						Width,
								//int						Height,
								HINSTANCE					hInstance,
								HWND						hWndParent,
								WORD						Identifier		/*= 0*/,
								DWORD						Styles			/*= DEFAULT_STYLES*/,
								DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/,
								DWORD						CurrentView		/*= MCMV_MONTH*/)
	: BaseWindowClass()
{
	Create(													x,
															y,
								//							Width,
								//							Height,
															hInstance,
															hWndParent,
															Identifier		/*= 0*/,
															Styles			/*= DEFAULT_STYLES*/,
															ExtendedStyles	/*= DEFAULT_EXSTYLES*/,
															CurrentView		/*= MCMV_MONTH*/);
}

void MonthCalendar::Create(		int							x,
								int							y,
								//int						Width,
								//int						Height,
								HINSTANCE					hInstance,
								HWND						hWndParent,
								WORD						Identifier		/*= 0*/,
								DWORD						Styles			/*= DEFAULT_STYLES*/,
								DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/,
								DWORD						CurrentView		/*= MCMV_MONTH*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_DATE_CLASSES;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	MONTHCAL_CLASSW,
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Identifier,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	RECT Rect;
	MonthCal_GetMinReqRect(hWnd, &Rect);
	SetWindowPos(hWnd, NULL, x, y, Rect.right, Rect.bottom, SWP_NOZORDER);
	StorePositionAndSize(x, y, Rect.right - x, Rect.bottom - y);
	MonthCal_SetCurrentView(hWnd, CurrentView);
	ChooseDefaultFont();
}

void MonthCalendar::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

MonthCalendar::~MonthCalendar()
{
	Destroy();
}

/*
void MonthCalendar::SetRange(INT Min, INT Max)
{
	SendMessageW(hWnd, PBM_SETRANGE32, (WPARAM) Min, (LPARAM) Max);
}

INT MonthCalendar::GetLowRange() const
{
	return (INT) SendMessageW(hWnd, PBM_GETRANGE, (WPARAM) TRUE, (LPARAM) NULL);
}

INT MonthCalendar::GetHighRange() const
{
	return (INT) SendMessageW(hWnd, PBM_GETRANGE, (WPARAM) FALSE, (LPARAM) NULL);
}

void MonthCalendar::SetPosition(INT NewPosition)
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
	SendMessageW(hWnd, PBM_SETPOS, (WPARAM) NewPosition, (LPARAM) NULL);
}

void MonthCalendar::IncreasePosition(DWORD Increment)
{
	SendMessageW(hWnd, PBM_DELTAPOS, (WPARAM) Increment, (LPARAM) NULL);
}

void MonthCalendar::SetStepSize(DWORD StepSize)
{
	SendMessageW(hWnd, PBM_SETSTEP, (WPARAM) StepSize, (LPARAM) NULL);
}

void MonthCalendar::SetStepIt()
{
	SendMessageW(hWnd, PBM_STEPIT, (WPARAM) NULL, (LPARAM) NULL);
}
*/
