#pragma once
#ifndef WINDOWS_CLASSES__CHECKBOX_H
#define WINDOWS_CLASSES__CHECKBOX_H

#include <string>
#include "BaseWindowClass.h"

class CheckBox : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		CheckBox();
		CheckBox(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(L""),
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~CheckBox();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(L""),
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();

		void Check(bool bChecked);
		void Check();
		void Uncheck();

		bool IsChecked()		const;
		bool IsUnChecked()		const;
		bool IsIndeterminate()	const;

	protected:

};

#endif	// WINDOWS_CLASSES__CHECKBOX_H

