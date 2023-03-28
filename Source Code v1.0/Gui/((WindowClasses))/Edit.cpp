#include "Edit.h"

DWORD Edit::DEFAULT_STYLES		= ES_LEFT | WS_VISIBLE | WS_CHILD;
DWORD Edit::DEFAULT_EXSTYLES	= WS_EX_CLIENTEDGE;

Edit::Edit()
{
}

Edit::Edit(			int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			/*= std::wstring(L"")*/,
					WORD					Identifier		/*= 0*/,
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
											Identifier		/*= 0*/,
											Styles			/*= DEFAULT_STYLES*/,
											ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void Edit::Create(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			/*= std::wstring(L"")*/,
					WORD					Identifier		/*= 0*/,
					DWORD					Styles			/*= DEFAULT_STYLES*/,
					DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	L"EDIT",
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
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void Edit::Destroy()
{
	//SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
	DestroyWindow(hWnd);
}

Edit::~Edit()
{
	Destroy();
}

// Edit::Edit(	int				x,
// 			int				y,
// 			int				Width,
// 			int				Height,
// 			HINSTANCE		hInstance,
// 			HWND			hWndParent,
// 			std::wstring	Content			/*= std::wstring(L"")*/,
// 			DWORD			Styles			/*= DEFAULT_STYLES*/,
// 			DWORD			ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
// {
// 	ClassName = L"EDIT";
// 	hWnd = CreateWindowExW(	ExtendedStyles,
// 							ClassName.c_str(),
// 							Content.c_str(),
// 							Styles,
// 							x,
// 							y,
// 							Width,
// 							Height,
// 							hWndParent,
// 							NULL,
// 							hInstance,
// 							NULL);
// 	ChooseDefaultFont();
// }
// 
// Edit::~Edit()
// {
// 	
// }
