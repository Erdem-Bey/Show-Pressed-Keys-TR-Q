#include "ComboBox.h"

DWORD ComboBox::DEFAULT_STYLES		= CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VISIBLE | WS_CHILD;
DWORD ComboBox::DEFAULT_EXSTYLES	= 0;


ComboBox::ComboBox()
{
}

ComboBox::ComboBox(			int						x,
							int						y,
							int						Width,
							int						Height,
							HINSTANCE				hInstance,
							HWND					hWndParent,
							WORD					Id,
							DWORD					Styles			/*= DEFAULT_STYLES*/,
							DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(											x,
													y,
													Width,
													Height,
													hInstance,
													hWndParent,
													Id,
													Styles			/*= DEFAULT_STYLES*/,
													ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void ComboBox::Create(		int						x,
							int						y,
							int						Width,
							int						Height,
							HINSTANCE				hInstance,
							HWND					hWndParent,
							WORD					Id,
							DWORD					Styles			/*= DEFAULT_STYLES*/,
							DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	L"COMBOBOX",
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Id,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void ComboBox::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

ComboBox::~ComboBox()
{
	Destroy();
}

void ComboBox::ReloadItems()
{
	DeleteAllItems();
	for (std::vector<std::wstring>::const_iterator it=Items.begin(); it<Items.end(); ++it)
	{
		SendMessageW(hWnd, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) it->c_str());
	}
}

void ComboBox::DeleteAllItems()
{
	//Doesn't work:
	//SendMessageW(hWnd, (UINT) CB_RESETCONTENT, (WPARAM) 0, (LPARAM) 0);
	size_t ItemCount = GetItemCount();
	for (size_t i=0; i<ItemCount; i++)
	{
		DeleteItem(0);
	}
}

void ComboBox::DeleteItem(size_t ItemId)
{
	SendMessageW(hWnd, CB_DELETESTRING, ItemId, NULL);
}

size_t ComboBox::GetItemCount() const
{
	return SendMessageW(hWnd, CB_GETCOUNT, NULL, NULL);
}

void ComboBox::SelectItem(size_t ItemId)
{
	SendMessage(hWnd, CB_SETCURSEL, (WPARAM) ItemId, (LPARAM) NULL);
}

size_t ComboBox::GetSelectedItem() const
{
	return SendMessageW(hWnd, CB_GETCURSEL, (WPARAM) NULL, (LPARAM) NULL);
}

std::wstring ComboBox::GetSelectedItemText() const
{
	const size_t SelectedIndex		= GetSelectedItem();
	const size_t SelectedTextLenght	= (size_t) SendMessage(hWnd, CB_GETLBTEXTLEN, (WPARAM) SelectedIndex, (LPARAM) NULL);
	std::wstring SelectedText;
	if (SelectedTextLenght == 0)
	{
		return SelectedText;
	}
	wchar_t * wcSelectedText = new wchar_t[SelectedTextLenght + 1];
	SelectedText.assign(wcSelectedText);
	delete[] wcSelectedText;
	return SelectedText;
}
