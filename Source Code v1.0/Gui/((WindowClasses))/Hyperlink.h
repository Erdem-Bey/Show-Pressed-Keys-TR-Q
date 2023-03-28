#pragma once
#ifndef WINDOWS_CLASSES__HYPERLINK_H
#define WINDOWS_CLASSES__HYPERLINK_H

#include <string>
#include "BaseWindowClass.h"

class Hyperlink : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		Hyperlink();
		Hyperlink(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(),
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~Hyperlink();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					const std::wstring &	Content			= std::wstring(),
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();
		
		/*void SetRange(INT Min, INT Max);
		INT GetLowRange() const;
		INT GetHighRange() const;
		void SetPosition(INT NewPosition);
		void IncreasePosition(DWORD Increment);
		void SetStepSize(DWORD StepSize);
		void SetStepIt();*/

	protected:

};

#endif	// WINDOWS_CLASSES__HYPERLINK_H
