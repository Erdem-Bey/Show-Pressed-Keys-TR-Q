#include "Radio.h"

#include <string>

DWORD Radio::DEFAULT_STYLES		= BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD;
DWORD Radio::DEFAULT_EXSTYLES	= 0;

Radio::Radio()
{
}

Radio::Radio(		int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			/*= std::wstring(L"")*/,
					WORD					Identifer		/*= 0*/,
					DWORD					Styles			/*= DEFAULT_STYLES*/,
					DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(									x,
											y,
											Width,
											Height,
											hInstance,
											hWndParent,
											Content			/*= std::wstring(L"")*/,
											Identifer		/*= 0*/,
											Styles			/*= DEFAULT_STYLES*/,
											ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void Radio::Create(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			/*= std::wstring(L"")*/,
					WORD					Identifer		/*= 0*/,
					DWORD					Styles			/*= DEFAULT_STYLES*/,
					DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	L"BUTTON",
							/*_In_opt_	LPCTSTR*/	Content.c_str(),
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Identifer,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void Radio::Destroy()
{
	//SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
	DestroyWindow(hWnd);
}

Radio::~Radio()
{
	Destroy();
}

bool Radio::IsChecked() const
{
	return (BST_CHECKED == SendMessageW(hWnd, BM_GETCHECK, (WPARAM) NULL, (LPARAM) NULL));
}

void Radio::Check() const
{
	SendMessageW(hWnd, BM_SETCHECK, (WPARAM) BST_CHECKED, (LPARAM) NULL);
}

void Radio::Uncheck() const
{
	SendMessageW(hWnd, BM_SETCHECK, (WPARAM) BST_UNCHECKED, (LPARAM) NULL);
}
