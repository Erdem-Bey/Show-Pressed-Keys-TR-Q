#pragma once
#ifndef WINDOWS_CLASSES__RADIO_H
#define WINDOWS_CLASSES__RADIO_H

#include <string>
#include "BaseWindowClass.h"

class Radio : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		Radio();
		Radio(		int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(L""),
					WORD					Identifer		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~Radio();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(L""),
					WORD					Identifer		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();

		bool IsChecked() const;
		
		void Check() const;
		void Uncheck() const;



	protected:

};

#endif	// WINDOWS_CLASSES__RADIO_H

