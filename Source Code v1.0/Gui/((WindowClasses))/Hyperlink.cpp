#include "Hyperlink.h"

#include <CommCtrl.h>
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

DWORD Hyperlink::DEFAULT_STYLES				= WS_VISIBLE | WS_CHILD | WS_TABSTOP;
DWORD Hyperlink::DEFAULT_EXSTYLES			= 0;
bool  Hyperlink::COMMON_CONTROL_INITIALIZED	= false;

Hyperlink::Hyperlink()
{
}

Hyperlink::Hyperlink(		int							x,
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

void Hyperlink::Create(		int							x,
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
		iccx.dwICC  = ICC_LINK_CLASS;	// CommCtrl.h: #define ICC_LINK_CLASS 0x00008000
		/*bool bResult =*/ InitCommonControlsEx(&iccx);
		//DWORD dwError = GetLastError();
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	WC_LINK, // CommCtrl.h: #define WC_LINK L"SysLink"
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
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void Hyperlink::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

Hyperlink::~Hyperlink()
{
	Destroy();
}

