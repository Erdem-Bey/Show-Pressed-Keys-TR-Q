#pragma once
#ifndef WINDOWS_CLASSES__COMBOBOX_H
#define WINDOWS_CLASSES__COMBOBOX_H

#include <string>
#include <vector>
#include "BaseWindowClass.h"

class ComboBox : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		ComboBox();
		ComboBox(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Id,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~ComboBox();

		void Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Id,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);

		void Destroy();

		std::vector<std::wstring> Items;

		/*ComboBox(	int x,
					int y,
					int Width,
					int Height,
					HINSTANCE hInstance,
					HWND hWndParent,
					DWORD Styles = DEFAULT_STYLES,
					DWORD ExtendedStyles = DEFAULT_EXSTYLES);
		~ComboBox();*/

		void ReloadItems();
		void DeleteAllItems();
		void DeleteItem(size_t ItemId);
		size_t GetItemCount() const;
		void SelectItem(size_t ItemId);
		size_t GetSelectedItem() const;
		std::wstring GetSelectedItemText() const;

	protected:

};

#endif	// WINDOWS_CLASSES__COMBOBOX_H

