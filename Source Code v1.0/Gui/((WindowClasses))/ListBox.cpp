#include "ListBox.h"

DWORD ListBox::DEFAULT_STYLES	= LBS_NOTIFY | LBS_EXTENDEDSEL*0 | LBS_MULTIPLESEL*0 | WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL;
DWORD ListBox::DEFAULT_EXSTYLES	= WS_EX_CLIENTEDGE;

ListBox::ListBox()
{
}

ListBox::ListBox(	int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		/*= 0*/,
					DWORD					Styles			/*= DEFAULT_STYLES*/,
					DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(									x,
											y,
											Width,
											Height,
											hInstance,
											hWndParent,
											Identifier		/*= 0*/,
											Styles			/*= DEFAULT_STYLES*/,
											ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void ListBox::Create(int						x,
					int						y,
					int						Width,
					int						Height,
					HINSTANCE				hInstance,
					HWND					hWndParent,
					WORD					Identifier		/*= 0*/,
					DWORD					Styles			/*= DEFAULT_STYLES*/,
					DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	L"LISTBOX",
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Identifier,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
}

void ListBox::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

ListBox::~ListBox()
{
	Destroy();
}

// LRESULT ListBox::AddItem(const std::wstring & ItemText)
// {
// 	SendMessageW(hWnd, (UINT) LB_ADDSTRING, (WPARAM) 0, (LPARAM) it->c_str());
// }

void ListBox::ReloadItems()
{
	DeleteAllItems();
	for (std::vector<std::wstring>::const_iterator it=Items.begin(); it<Items.end(); ++it)
	{
		SendMessageW(hWnd, (UINT) LB_ADDSTRING, (WPARAM) 0, (LPARAM) it->c_str());
	}
}

void ListBox::DeleteAllItems()
{
	//Doesn't work:
	//SendMessageW(hWnd, (UINT) CB_RESETCONTENT, (WPARAM) 0, (LPARAM) 0);
	UINT ItemCount = GetItemCount();
	for (UINT i=0; i<ItemCount; i++)
	{
		DeleteItem(0);
	}
}

void ListBox::DeleteItem(UINT ItemId)
{
	SendMessageW(hWnd, LB_DELETESTRING, ItemId, NULL);
}

UINT ListBox::GetItemCount() const
{
	return (UINT) SendMessageW(hWnd, LB_GETCOUNT, NULL, NULL);
}

void ListBox::SelectItem(UINT ItemId)
{
	SendMessageW(hWnd, LB_SETCURSEL, (WPARAM) ItemId, (LPARAM) NULL);
}

std::vector<int> ListBox::GetSelectedItems() const
{
	std::vector<int> Items;
	int ItemCount1 = SendMessageW(hWnd, LB_GETSELCOUNT, (WPARAM) NULL, (LPARAM) NULL);
	if (ItemCount1 == LB_ERR)
	{
		return Items;
	}
	int * pItems = new int[ItemCount1];
	int ItemCount2 = static_cast<int>(SendMessageW(hWnd, LB_GETSELITEMS, (WPARAM) ItemCount1, (LPARAM) pItems));
	if (ItemCount2 == LB_ERR)
	{
		return Items;
	}
	Items.assign(pItems, pItems + ItemCount2);
	delete[] pItems;
	return Items;
}

LRESULT ListBox::GetSelectedItem() const
{
	return SendMessageW(hWnd, LB_GETCURSEL, (WPARAM) NULL, (LPARAM) NULL);
}

