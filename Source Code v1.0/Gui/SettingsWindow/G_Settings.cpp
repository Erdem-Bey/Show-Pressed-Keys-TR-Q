#include "G_Settings.h"

#include <Windows.h>
#include <sstream>

#include "..\..\Gui\Gui.h"
#include "..\..\Resource.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Gui\((WindowClasses))\Utility.h"

WindowSettings::WindowSettings()
	:	IsCreated	(false)
{
}

WindowSettings::~WindowSettings()
{
}

void WindowSettings::Create()
{
	if (IsCreated)
	{
		return;
	}
	Window.Create(	/*const std::wstring &	WindowClassName*/	Settings::SettingsWindow::SETTWND_CLASS,
					/*const std::wstring &	WindowTitle*/		Settings::SettingsWindow::SETTWND_TITLE,
					/*HINSTANCE				hInstance*/			Gui::hInstance,
																WindowSettings::MessageProcessor,
					/*int					x*/					Settings::SettingsWindow::SettWnd_X,
					/*int					y*/					Settings::SettingsWindow::SettWnd_Y,
					/*int					Width*/				Settings::SettingsWindow::SETTWND_W,
					/*int					Height*/			Settings::SettingsWindow::SETTWND_H,
					/*DWORD					Styles*/			Settings::SettingsWindow::SETTWND_STYLES,
					/*DWORD					ExtendedStyles*/	Settings::SettingsWindow::SETTWND_EXSTYLES,
					/*DWORD					ClassStyles*/		Settings::SettingsWindow::SETTWND_CLASS_STYLES,
					/*HICON					hIcon*/				LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_SETTINGS_BIG)),
					/*HICON					hSmallIcon*/		LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_SETTINGS_SMALL)),
					/*HCURSOR				hCursor*/			LoadCursor(NULL, IDC_ARROW),
					/*HBRUSH				hBackground*/		(HBRUSH) /*CreateSolidBrush(RGB(212,208,200)),//*/COLOR_WINDOW,
					/*LPCWSTR				MenuName*/			NULL,
					/*HMENU					hMenu*/				NULL);
	CreateChildren();
	bt00Save.Disable();
	Gui::MainWnd.Disable_Menu_File_Settings();
	IsCreated = true;
}

void WindowSettings::Destroy()
{
	if (IsCreated == false)
	{
		return;
	}
	DestroyWindow(Window.hWnd);
	Gui::MainWnd.Enable_Menu_File_Settings();
	IsCreated = false;
}

void WindowSettings::ChangeGuiLanguage()
{

}

