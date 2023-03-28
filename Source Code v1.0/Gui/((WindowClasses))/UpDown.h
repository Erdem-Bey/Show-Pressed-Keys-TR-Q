#pragma once
#ifndef WINDOWS_CLASSES__UPDOWN_H
#define WINDOWS_CLASSES__UPDOWN_H

#include <string>
#include <vector>
#include "BaseWindowClass.h"
#include "Edit.h"

class UpDown : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		UpDown();
		UpDown(		int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~UpDown();

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

		/*void AlignTo(	const BaseWindowClass & ReferenceWindow,
						BaseWindowClass::ALIGN_SIDE WhichSideToAlign,
						BaseWindowClass::ALIGN_TYPE HowToAlign,
						int SpaceToLeaveBetween);*/

		std::vector<UINT> SpeedIncrements;
		std::vector<UINT> IncrementTimes;
		
		void SetRange(INT Low, INT High);
		void SetPosition(INT NewPosition);
		INT  GetPosition() const;
		void UpdateSpeedIncrements();
		
		void			SetText(const std::wstring & Text);
		std::wstring	GetText() const;
		int64_t			GetInteger() const;
		uint64_t		GetUInteger() const;
		double			GetDouble() const;

	protected:
		Edit BuddyWindow;


};

#endif	// WINDOWS_CLASSES__UPDOWN_H

