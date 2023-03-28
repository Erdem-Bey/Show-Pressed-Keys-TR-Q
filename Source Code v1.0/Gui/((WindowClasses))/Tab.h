#pragma once
#ifndef WINDOWS_CLASSES__TAB_H
#define WINDOWS_CLASSES__TAB_H

#include <string>
#include "BaseWindowClass.h"


class Tab : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;

		Tab();
		Tab(		int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~Tab();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();


	protected:
		std::wstring	ClassName;


};

#endif	// WINDOWS_CLASSES__TAB_H

