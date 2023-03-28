#pragma once
#ifndef WINDOWS_CLASSES__MONTH_CALENDAR_H
#define WINDOWS_CLASSES__MONTH_CALENDAR_H

#include "BaseWindowClass.h"

#include <string>
#include <CommCtrl.h>

// View
//#define MCMV_MONTH      0
//#define MCMV_YEAR       1
//#define MCMV_DECADE     2
//#define MCMV_CENTURY    3
//#define MCMV_MAX        MCMV_CENTURY

class MonthCalendar : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		MonthCalendar();
		MonthCalendar(	int						x,
						int						y,
						//int					Width,
						//int					Height,
						HINSTANCE				hInstance,
						HWND					hWndParent,
						WORD					Identifier		= 0,
						DWORD					Styles			= DEFAULT_STYLES,
						DWORD					ExtendedStyles	= DEFAULT_EXSTYLES,
						DWORD					CurrentView		= MCMV_MONTH);
		~MonthCalendar();

		void Create(	int						x,
						int						y,
						//int					Width,
						//int					Height,
						HINSTANCE				hInstance,
						HWND					hWndParent,
						WORD					Identifier		= 0,
						DWORD					Styles			= DEFAULT_STYLES,
						DWORD					ExtendedStyles	= DEFAULT_EXSTYLES,
						DWORD					CurrentView		= MCMV_MONTH);

		void Destroy();
		
		//void SetRange(INT Min, INT Max);
		//INT GetLowRange() const;
		//INT GetHighRange() const;
		//void SetPosition(INT NewPosition);
		//void IncreasePosition(DWORD Increment);
		//void SetStepSize(DWORD StepSize);
		//void SetStepIt();

	protected:

};

#endif	// WINDOWS_CLASSES__MONTH_CALENDAR_H

