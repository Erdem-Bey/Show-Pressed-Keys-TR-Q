#pragma once
#ifndef WINDOWS_CLASSES__STATUSBAR_H
#define WINDOWS_CLASSES__STATUSBAR_H

#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <CommCtrl.h>


#include "BaseWindowClass.h"

class StatusBar : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		StatusBar();
		StatusBar(	HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~StatusBar();

		void Create(HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();
		
		template <class T /*= std::vector<INT>*/>
		void SetPartLocations(T && PartLocations);
		inline
		const std::vector<INT> & GetPartLocations() const;
		inline
		const INT & GetPartLocation(INT PartId) const;

		//std::vector<INT> GetPartLocations() const;
		
		template <class T>
		void SetPartText(BYTE PartId, const T & Text);

	protected:
		std::wstring		ClassName;
		std::vector<INT>	PartLocations;

};

template <class T /*= std::vector<INT>*/>
void StatusBar::SetPartLocations(T && PartLocations)
{
	if (PartLocations.size())
	{
		SendMessageW(hWnd, SB_SETPARTS, (WPARAM) PartLocations.size(), (LPARAM) &(PartLocations[0]));
		this->PartLocations = std::forward<T>(PartLocations);
	}
}

const std::vector<INT> & StatusBar::GetPartLocations() const
{
	return PartLocations;
}

const INT & StatusBar::GetPartLocation(INT PartId) const
{
	try
	{
		return PartLocations.at(PartId);
	}
	catch (...)
	{
		return 0;
	}
	
}

template <class T>
void StatusBar::SetPartText(BYTE PartId, const T & Text)
{
	std::wstringstream ss;
	ss << Text;
	std::wstring Print(ss.str());
	//if (static_cast<std::vector<INT>::size_type>(PartId) < PartLocations.size())
	//{
		SendMessageW(hWnd, SB_SETTEXT, (WPARAM) MAKEWORD(PartId, 0), (LPARAM) Print.c_str());
	//}
}

#endif	// WINDOWS_CLASSES__STATUSBAR_H

