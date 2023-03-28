#include "CheckBox.h"

#include <string>

DWORD CheckBox::DEFAULT_STYLES		= BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD;
DWORD CheckBox::DEFAULT_EXSTYLES	= 0;

CheckBox::CheckBox()
{

}


CheckBox::CheckBox(			int						x,
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
	Create(											x,
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

void CheckBox::Create(		int						x,
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
							/*_In_opt_	LPCTSTR*/	L"BUTTON",
							/*_In_opt_	LPCTSTR*/	(LPCWSTR) Content.c_str(),
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

void CheckBox::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

CheckBox::~CheckBox()
{
	Destroy();
}

void CheckBox::Check(bool bChecked)
{
	if (bChecked)
	{
		Check();
	}
	else
	{
		Uncheck();
	}
}

void CheckBox::Check()
{
	SendMessageW(hWnd, BM_SETCHECK, (WPARAM) BST_CHECKED, (LPARAM) NULL);
}

void CheckBox::Uncheck()
{
	SendMessageW(hWnd, BM_SETCHECK, (WPARAM) BST_UNCHECKED, (LPARAM) NULL);
}

bool CheckBox::IsChecked() const
{
	return (BST_CHECKED == SendMessageW(hWnd, BM_GETCHECK, (WPARAM) NULL, (LPARAM) NULL));
}

bool CheckBox::IsUnChecked() const
{
	return (BST_UNCHECKED == SendMessageW(hWnd, BM_GETCHECK, (WPARAM) NULL, (LPARAM) NULL));
}

bool CheckBox::IsIndeterminate() const
{
	return (BST_INDETERMINATE == SendMessageW(hWnd, BM_GETCHECK, (WPARAM) NULL, (LPARAM) NULL));
}
