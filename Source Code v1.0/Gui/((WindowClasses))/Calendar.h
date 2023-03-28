#pragma once
#ifndef WINDOWS_CLASSES__CALENDAR_H
#define WINDOWS_CLASSES__CALENDAR_H

#include <string>
#include "BaseWindowClass.h"

class Calendar : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		Calendar();
		Calendar(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(),
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~Calendar();

		void Create(int						x,
					int						y,
					int						Width,								// Unused. Has fixed width.
					int						Height,								// Unused. Has fixed height.
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(),	// Unused.
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();
		
		SYSTEMTIME	GetCurrentDateTime() const;
		void		SetCurrentDateTime(const SYSTEMTIME & SystemTime);

	protected:

};

#endif	// WINDOWS_CLASSES__CALENDAR_H
