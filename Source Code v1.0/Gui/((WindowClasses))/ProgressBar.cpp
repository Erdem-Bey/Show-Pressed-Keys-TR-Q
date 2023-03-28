#include "ProgressBar.h"

#include <CommCtrl.h>


DWORD ProgressBar::DEFAULT_STYLES	= PBS_SMOOTH | WS_VISIBLE | WS_CHILD;
DWORD ProgressBar::DEFAULT_EXSTYLES	= 0;
bool  ProgressBar::COMMON_CONTROL_INITIALIZED = false;

ProgressBar::ProgressBar()
{
}

ProgressBar::ProgressBar(	int							x,
							int							y,
							int							Width,
							int							Height,
							HINSTANCE					hInstance,
							HWND						hWndParent,
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
														Styles			/*= DEFAULT_STYLES*/,
														ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void ProgressBar::Create(	int							x,
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
		iccx.dwICC  = ICC_PROGRESS_CLASS;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	PROGRESS_CLASSW,
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		NULL,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void ProgressBar::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

ProgressBar::~ProgressBar()
{
	Destroy();
}

void ProgressBar::SetRange(INT Min, INT Max)
{
	SendMessageW(hWnd, PBM_SETRANGE32, (WPARAM) Min, (LPARAM) Max);
}

INT ProgressBar::GetLowRange() const
{
	return (INT) SendMessageW(hWnd, PBM_GETRANGE, (WPARAM) TRUE, (LPARAM) NULL);
}

INT ProgressBar::GetHighRange() const
{
	return (INT) SendMessageW(hWnd, PBM_GETRANGE, (WPARAM) FALSE, (LPARAM) NULL);
}

void ProgressBar::SetPosition(INT NewPosition)
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

void ProgressBar::IncreasePosition(DWORD Increment)
{
	SendMessageW(hWnd, PBM_DELTAPOS, (WPARAM) Increment, (LPARAM) NULL);
}

void ProgressBar::SetStepSize(DWORD StepSize)
{
	SendMessageW(hWnd, PBM_SETSTEP, (WPARAM) StepSize, (LPARAM) NULL);
}

void ProgressBar::SetStepIt()
{
	SendMessageW(hWnd, PBM_STEPIT, (WPARAM) NULL, (LPARAM) NULL);
}
