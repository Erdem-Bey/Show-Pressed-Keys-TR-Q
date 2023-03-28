#pragma once
#ifndef WINDOWS_CLASSES__LISTBOX_H
#define WINDOWS_CLASSES__LISTBOX_H

#include <string>
#include <vector>
#include "BaseWindowClass.h"

class ListBox : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		ListBox();
		ListBox(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		= 0,
					DWORD					Styles			= DEFAULT_STYLES,
					DWORD					ExtendedStyles	= DEFAULT_EXSTYLES);
		~ListBox();

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

		std::vector<std::wstring> Items;

		//LRESULT AddItem(const std::wstring & ItemText);
		void ReloadItems();
		void DeleteAllItems();
		void DeleteItem(UINT ItemId);
		UINT GetItemCount() const;
		void SelectItem(UINT ItemId);
		std::vector<int> GetSelectedItems() const;
		LRESULT GetSelectedItem() const;

	protected:


};

#endif	// WINDOWS_CLASSES__LISTBOX_H

