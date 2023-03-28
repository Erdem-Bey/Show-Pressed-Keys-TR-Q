#pragma once
#ifndef WINDOWS_CLASSES__STATIC_H
#define WINDOWS_CLASSES__STATIC_H

#include <string>
#include "BaseWindowClass.h"

class Static : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		Static();
		Static(		int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(L""),
					 WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~Static();

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



	protected:
};

#endif	// WINDOWS_CLASSES__STATIC_H

