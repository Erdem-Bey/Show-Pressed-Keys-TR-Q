#include "ListView.h"

#include <stdint.h>
#include <string>
#include <list>
#include <array>
#include <stdint.h>
#include <windows.h>
#include <CommCtrl.h>

DWORD ListView::DEFAULT_STYLES		= 0 | LVS_SORTDESCENDING*0 | LVS_REPORT | WS_VISIBLE | WS_CHILD;/*
DWORD ListView::DEFAULT_EXSTYLES	= LVS_EX_AUTOCHECKSELECT
									| LVS_EX_AUTOSIZECOLUMNS
									| LVS_EX_BORDERSELECT
									| LVS_EX_COLUMNSNAPPOINTS
									| LVS_EX_DOUBLEBUFFER
									| LVS_EX_FULLROWSELECT
									| LVS_EX_GRIDLINES;*/
DWORD ListView::DEFAULT_EXSTYLES	= LVS_EX_AUTOCHECKSELECT
									| 0
									| 0
									| 0
									| LVS_EX_DOUBLEBUFFER
									| LVS_EX_FULLROWSELECT
									| LVS_EX_GRIDLINES;
bool  ListView::COMMON_CONTROL_INITIALIZED = false;

ListView::ListView()
{
}

ListView::ListView(	int							x,
					int							y,
					int							Width,
					int							Height,
					HINSTANCE					hInstance,
					HWND						hWndParent,
					WORD						Identifier		/*= 0*/,
					DWORD						Styles			/*= DEFAULT_STYLES*/,
					DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(										x,
												y,
												Width,
												Height,
												hInstance,
												hWndParent,
												Identifier		/*= 0*/,
												Styles			/*= DEFAULT_STYLES*/,
												ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void ListView::Create(	int						x,
						int						y,
						int						Width,
						int						Height,
						HINSTANCE				hInstance,
						HWND					hWndParent,
						WORD					Identifier		/*= 0*/,
						DWORD					Styles			/*= DEFAULT_STYLES*/,
						DWORD					ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	WC_LISTVIEWW,
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
	SendMessageW(hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM) ExtendedStyles, (LPARAM) ExtendedStyles);
}

void ListView::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

ListView::~ListView()
{
	Destroy();
}

void ListView::Resize(	int Rows, int Columns,
						std::initializer_list<std::wstring>	HeaderTexts,
						std::initializer_list<int>			ColumnSizes)
{
	// Check sanity of arguments.
	if ((Columns != HeaderTexts.size()) || (Columns != ColumnSizes.size()))
	{
		return;
	}
	// Delete all items.
	SendMessageW(hWnd, LVM_DELETEALLITEMS, (WPARAM) 0,    (LPARAM) 0);
	// Item count is the number of rows.
	SendMessageW(hWnd, LVM_SETITEMCOUNT,   (WPARAM) Rows, (LPARAM) LVSICF_NOINVALIDATEALL);
	// Initialize a LVCOLUMN struct.
	LVCOLUMNW Lvc;
	Lvc.mask		= (UINT)	LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM*0 | LVCF_IMAGE*0 | LVCF_ORDER | LVCF_MINWIDTH | LVCF_DEFAULTWIDTH | LVCF_IDEALWIDTH;
	Lvc.fmt			= (int)		LVCFMT_LEFT;
	Lvc.cx			= (int)		0; 
	Lvc.pszText		= (LPWSTR)	L"";
	Lvc.cchTextMax	= (int)		0;
	Lvc.iSubItem	= (int)		-1;
	Lvc.iImage		= (int)		-1;
	Lvc.iOrder		= (int)		0;
	Lvc.cxMin		= (int)		0;
	Lvc.cxDefault	= (int)		0;
	Lvc.cxIdeal		= (int)		0;
	// Insert columns.
	std::wstring HeaderText;
	int ColunSize;
	for (int i=0; i<Columns; i++)
	{
		ColunSize		= *(ColumnSizes.begin() + i);
		HeaderText		= *(HeaderTexts.begin() + i);
		Lvc.cx			= (int)		ColunSize; 
		Lvc.pszText		= (LPWSTR)	HeaderText.c_str();
		Lvc.cchTextMax	= (int)		HeaderText.size();
		Lvc.iOrder		= (int)		i;
		Lvc.cxMin		= (int)		ColunSize;
		Lvc.cxDefault	= (int)		ColunSize;
		Lvc.cxIdeal		= (int)		ColunSize;
		SendMessageW(hWnd, LVM_INSERTCOLUMN, (WPARAM) Lvc.iOrder, (LPARAM) &Lvc);
	}
	// Initialize a LVITEM struct.
	LVITEMW Lvi;
	Lvi.mask		= (UINT)	LVIF_COLFMT*0 | LVIF_COLUMNS*0 | LVIF_DI_SETITEM*0 | LVIF_GROUPID*0 | LVIF_IMAGE*0 | LVIF_INDENT*0 | LVIF_NORECOMPUTE | LVIF_PARAM*0 | LVIF_STATE*0 | LVIF_TEXT;
	Lvi.iItem		= (int)		0;
	Lvi.iSubItem	= (int)		0;
	Lvi.state		= (UINT)	0;
	Lvi.stateMask	= (UINT)	0;
	Lvi.pszText		= (LPWSTR)	L"";
	Lvi.cchTextMax	= (int)		0;
	Lvi.iImage		= (int)		-1;
	Lvi.lParam		= (LPARAM)	0;
	Lvi.iIndent		= (int)		-1;
	Lvi.iGroupId	= (int)		-1;
	Lvi.cColumns	= (UINT)	Columns;
	Lvi.puColumns	= (PUINT)	NULL;	/*UINT uColumns[3] = {0, 1, 2};*/
	Lvi.piColFmt	= (int*)	NULL;	/*int  iColFmt[3]  = {0, 0, 0};*/
	Lvi.iGroup		= (int)		0;
	// Insert rows.
	Lvi.mask		= (UINT)	LVIF_TEXT;
	if (Columns > 1)
	{
		for (int r=0; r<Rows; r++)
		{
			Lvi.iItem = r;
			Lvi.iSubItem = 0;
			SendMessageW(hWnd, LVM_INSERTITEM, (WPARAM) 0, (LPARAM) &Lvi);
			for (int c=1; c<Columns; c++)
			{
				Lvi.iSubItem = c;
				SendMessageW(hWnd, LVM_SETITEMW, (WPARAM) 0, (LPARAM) &Lvi);
			}
		}
	}
}

void ListView::SetText(int Row, int Column, const std::wstring & Text)
{
	LVITEMW Lvi;
	Lvi.mask		= (UINT)	LVIF_TEXT;
	Lvi.iItem		= (int)		Row;
	Lvi.iSubItem	= (int)		Column;
	Lvi.pszText		= (LPWSTR)	Text.c_str();
	Lvi.cchTextMax	= (int)		Text.size();
	SendMessageW(hWnd, LVM_SETITEMW, (WPARAM) 0, (LPARAM) &Lvi);
}





