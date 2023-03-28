#pragma once
#ifndef WINDOWS_CLASSES__TRACKBAR_H
#define WINDOWS_CLASSES__TRACKBAR_H

#include <string>
#include "BaseWindowClass.h"

class TrackBar : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		TrackBar();
		TrackBar(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~TrackBar();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();
		
		void SetRange(INT Min, INT Max);
		INT GetLowRange() const;
		INT GetHighRange() const;
		void SetPosition(INT NewPosition);
		void SetBodyWindows(const HWND & hWndLeft, const HWND & hWndRight);

	protected:
		std::wstring	ClassName;

};

#endif	// WINDOWS_CLASSES__TRACKBAR_H

