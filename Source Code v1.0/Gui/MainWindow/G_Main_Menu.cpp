#include "G_Main.h"

//#include <cstring>
#include <cwchar>
#include <string>
#include <windows.h>

#include "..\..\Strings\Strings.h"


//wchar_t WindowMain::NAME_MENU_FILE			[]	= Strings::MainWindow::Menu_File.c_str();
//wchar_t WindowMain::NAME_MENU_FILE			[]	= L"File";
//wchar_t WindowMain::NAME_MENU_FILE_SETTINGS	[]	= L"Settings...";
//wchar_t WindowMain::NAME_MENU_FILE_EXIT		[]	= L"Exit";
//wchar_t WindowMain::NAME_MENU_HELP			[]	= L"Help";
//wchar_t WindowMain::NAME_MENU_HELP_USAGE		[]	= L"Usage...";
//wchar_t WindowMain::NAME_MENU_HELP_ABOUT		[]	= L"About...";
wchar_t	*	WindowMain::NAME_MENU_FILE			= nullptr;
wchar_t	*	WindowMain::NAME_MENU_FILE_SETTINGS	= nullptr;
wchar_t	*	WindowMain::NAME_MENU_FILE_EXIT		= nullptr;
wchar_t	*	WindowMain::NAME_MENU_HELP			= nullptr;
wchar_t	*	WindowMain::NAME_MENU_HELP_USAGE	= nullptr;
wchar_t	*	WindowMain::NAME_MENU_HELP_ABOUT	= nullptr;

void WindowMain::CreateMenu()
{
	hMenuBar	= ::CreateMenu();
	hMenuFile	= ::CreateMenu();
	hMenuHelp	= ::CreateMenu();
	
	{
		const std::wstring & File			= static_cast<std::wstring>(Strings::MainWindow::Menu_File);
		const std::wstring & FileSettings	= static_cast<std::wstring>(Strings::MainWindow::Menu_File_Settings);
		const std::wstring & FileExit		= static_cast<std::wstring>(Strings::MainWindow::Menu_File_Exit);
		const std::wstring & Help			= static_cast<std::wstring>(Strings::MainWindow::Menu_Help);
		const std::wstring & HelpUsage		= static_cast<std::wstring>(Strings::MainWindow::Menu_Help_Usage);
		const std::wstring & HelpAbout		= static_cast<std::wstring>(Strings::MainWindow::Menu_Help_About);
		
		delete [] NAME_MENU_FILE;
		delete [] NAME_MENU_FILE_SETTINGS;
		delete [] NAME_MENU_FILE_EXIT;
		delete [] NAME_MENU_HELP;
		delete [] NAME_MENU_HELP_USAGE;
		delete [] NAME_MENU_HELP_ABOUT;
		
		NAME_MENU_FILE			= new wchar_t[File			.size()	+ 1];
		NAME_MENU_FILE_SETTINGS	= new wchar_t[FileSettings	.size()	+ 1];
		NAME_MENU_FILE_EXIT		= new wchar_t[FileExit		.size()	+ 1];
		NAME_MENU_HELP			= new wchar_t[Help			.size()	+ 1];
		NAME_MENU_HELP_USAGE	= new wchar_t[HelpUsage		.size()	+ 1];
		NAME_MENU_HELP_ABOUT	= new wchar_t[HelpAbout		.size()	+ 1];
	
		std::wcsncpy(NAME_MENU_FILE,			File		.c_str(),	File		.size()	+ 1);
		std::wcsncpy(NAME_MENU_FILE_SETTINGS,	FileSettings.c_str(),	FileSettings.size()	+ 1);
		std::wcsncpy(NAME_MENU_FILE_EXIT,		FileExit	.c_str(),	FileExit	.size()	+ 1);
		std::wcsncpy(NAME_MENU_HELP,			Help		.c_str(),	Help		.size()	+ 1);
		std::wcsncpy(NAME_MENU_HELP_USAGE,		HelpUsage	.c_str(),	HelpUsage	.size()	+ 1);
		std::wcsncpy(NAME_MENU_HELP_ABOUT,		HelpAbout	.c_str(),	HelpAbout	.size()	+ 1);
	}

	MENUITEMINFOW	mii;

	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_FILE;
	/*HMENU*/		mii.hSubMenu		= hMenuFile;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_FILE;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_FILE) / sizeof(*NAME_MENU_FILE)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuBar,
					/*_In_ UINT				uItem*/			ORDER_MENU_FILE,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);

	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_HELP;
	/*HMENU*/		mii.hSubMenu		= hMenuHelp;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_HELP;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_HELP) / sizeof(*NAME_MENU_HELP)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuBar,
					/*_In_ UINT				uItem*/			ORDER_MENU_HELP,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);


	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_FILE_SETTINGS;
	/*HMENU*/		mii.hSubMenu		= NULL;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_FILE_SETTINGS;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_FILE_SETTINGS) / sizeof(*NAME_MENU_FILE_SETTINGS)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuFile,
					/*_In_ UINT				uItem*/			ORDER_MENU_FILE_SETTINGS,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);

	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_FILE_EXIT;
	/*HMENU*/		mii.hSubMenu		= NULL;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_FILE_EXIT;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_FILE_EXIT) / sizeof(*NAME_MENU_FILE_EXIT)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuFile,
					/*_In_ UINT				uItem*/			ORDER_MENU_FILE_EXIT,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);

	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_HELP_USAGE;
	/*HMENU*/		mii.hSubMenu		= NULL;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_HELP_USAGE;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_HELP_USAGE) / sizeof(*NAME_MENU_HELP_USAGE)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuHelp,
					/*_In_ UINT				uItem*/			ORDER_MENU_HELP_USAGE,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);

	/*UINT*/		mii.cbSize			= sizeof(mii);
	/*UINT*/		mii.fMask			= MIIM_STRING | MIIM_STATE | MIIM_ID;
	/*UINT*/		mii.fType			= MFT_STRING;
	/*UINT*/		mii.fState			= MFS_ENABLED;
	/*UINT*/		mii.wID				= ID_MENU_HELP_ABOUT;
	/*HMENU*/		mii.hSubMenu		= NULL;
	/*HBITMAP*/		mii.hbmpChecked		= NULL;
	/*HBITMAP*/		mii.hbmpUnchecked	= NULL;
	/*ULONG_PTR*/	mii.dwItemData		= NULL;
	/*LPWSTR*/		mii.dwTypeData		= NAME_MENU_HELP_ABOUT;
	/*UINT*/		mii.cch				= (sizeof(NAME_MENU_HELP_ABOUT) / sizeof(*NAME_MENU_HELP_ABOUT)) - 1;
	/*HBITMAP*/		mii.hbmpItem		= NULL;
	InsertMenuItemW(/*_In_ HMENU			hMenu*/			hMenuHelp,
					/*_In_ UINT				uItem*/			ORDER_MENU_HELP_ABOUT,
					/*_In_ BOOL				fByPosition*/	TRUE,
					/*_In_ LPCMENUITEMINFOW	lpmii*/			&mii);
}


void WindowMain::Disable_Menu_File()
{
	//MENUITEMINFOW mii;
	//GetMenuItemInfoW(	/*_In_		HMENU*/				hMenuBar,
	//					/*_In_		UINT*/				ID_MENU_FILE,
	//					/*_In_		BOOL*/				FALSE,
	//					/*_Inout_	LPMENUITEMINFOW*/	&mii);
	//mii.fState &= ~MFS_ENABLED;
	//mii.fState |= MFS_DISABLED;
	//SetMenuItemInfoW(	/*_In_		HMENU*/				hMenuBar,
	//					/*_In_		UINT*/				ID_MENU_FILE,
	//					/*_In_		BOOL*/				FALSE,
	//					/*_In_		LPMENUITEMINFO*/	&mii);
	EnableMenuItem(hMenuBar,	ID_MENU_FILE,			MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Disable_Menu_File_Settings()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_SETTINGS,	MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Disable_Menu_File_Exit()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_EXIT,		MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Disable_Menu_Help()
{
	EnableMenuItem(hMenuBar,	ID_MENU_HELP,			MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Disable_Menu_Help_About()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_ABOUT,		MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Disable_Menu_Help_Usage()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_USAGE,		MF_BYCOMMAND | MF_DISABLED);
}

void WindowMain::Gray_Menu_File()
{
	EnableMenuItem(hMenuBar,	ID_MENU_FILE,			MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Gray_Menu_File_Settings()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_SETTINGS,	MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Gray_Menu_File_Exit()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_EXIT,		MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Gray_Menu_Help()
{
	EnableMenuItem(hMenuBar,	ID_MENU_HELP,			MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Gray_Menu_Help_About()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_ABOUT,		MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Gray_Menu_Help_Usage()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_USAGE,		MF_BYCOMMAND | MF_GRAYED);
}

void WindowMain::Enable_Menu_File()
{
	EnableMenuItem(hMenuBar,	ID_MENU_FILE,			MF_BYCOMMAND | MF_ENABLED);
}

void WindowMain::Enable_Menu_File_Settings()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_SETTINGS,	MF_BYCOMMAND | MF_ENABLED);
}

void WindowMain::Enable_Menu_File_Exit()
{
	EnableMenuItem(hMenuFile,	ID_MENU_FILE_EXIT,		MF_BYCOMMAND | MF_ENABLED);
}

void WindowMain::Enable_Menu_Help()
{
	EnableMenuItem(hMenuBar,	ID_MENU_HELP,			MF_BYCOMMAND | MF_ENABLED);
}

void WindowMain::Enable_Menu_Help_About()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_ABOUT,		MF_BYCOMMAND | MF_ENABLED);
}

void WindowMain::Enable_Menu_Help_Usage()
{
	EnableMenuItem(hMenuHelp,	ID_MENU_HELP_USAGE,		MF_BYCOMMAND | MF_ENABLED);
}






