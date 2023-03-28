#pragma once
#ifndef WINDOWS_CLASSES__LISTVIEW_H
#define WINDOWS_CLASSES__LISTVIEW_H

#include <stdint.h>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <stdint.h>
#include <initializer_list>
#include <windows.h>
#include <CommCtrl.h>
#include "BaseWindowClass.h"

class ListView : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;
		static bool  COMMON_CONTROL_INITIALIZED;
		
		ListView();
		ListView(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~ListView();

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
		
		void Resize(int									Rows,
					int									Columns,
					std::initializer_list<std::wstring>	HeaderTexts,
					std::initializer_list<int>			ColumnSizes);

		void SetText(	int								Row,
						int								Column,
						const std::wstring &			Text);

	protected:
		std::wstring ClassName;

};

#endif	// WINDOWS_CLASSES__LISTVIEW_H


