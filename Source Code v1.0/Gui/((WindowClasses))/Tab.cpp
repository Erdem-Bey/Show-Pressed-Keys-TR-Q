#include "Tab.h"

#include <CommCtrl.h>

DWORD Tab::DEFAULT_STYLES				= 0 | WS_VISIBLE | WS_CHILD;
DWORD Tab::DEFAULT_EXSTYLES				= 0;
bool  Tab::COMMON_CONTROL_INITIALIZED	= false;


Tab::Tab()
{
}

Tab::Tab(			int							x,
					int							y,
					int							Width,
					int							Height,
					HINSTANCE					hInstance,
					HWND						hWndParent,
					WORD						Identifier		/*= 0*/,
					DWORD						Styles			/*= DEFAULT_STYLES*/,
					DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(			x,
					y,
					Width,
					Height,
					hInstance,
					hWndParent,
					Identifier		/*= 0*/,
					Styles			/*= DEFAULT_STYLES*/,
					ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

Tab::~Tab()
{
	Destroy();
}

void Tab::Create(	int							x,
					int							y,
					int							Width,
					int							Height,
					HINSTANCE					hInstance,
					HWND						hWndParent,
					WORD						Identifier		/*= 0*/,
					DWORD						Styles			/*= DEFAULT_STYLES*/,
					DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_TAB_CLASSES;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
						   /*_In_opt_	LPCTSTR*/	WC_TABCONTROLW,
						   /*_In_opt_	LPCTSTR*/	L"",
						   /*_In_		DWORD*/		Styles,
						   /*_In_		int*/		x,
						   /*_In_		int*/		y,
						   /*_In_		int*/		Width,
						   /*_In_		int*/		Height,
						   /*_In_opt_	HWND*/		hWndParent,
						   /*_In_opt_	HMENU*/		(HMENU) Identifier,
						   /*_In_opt_	HINSTANCE*/	hInstance,
						   /*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void Tab::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}
