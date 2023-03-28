#include "..\..\Settings\Settings.h"

#include "..\..\IniFile\IniFile.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Settings\AboutWindow\S_AboutWindow.h"


const std::wstring	Settings_AboutWindow::KEY_WP__ABOUT_X		(std::wstring(L"AboutWindow_LastPosition_X"));
const std::wstring	Settings_AboutWindow::KEY_WP__ABOUT_Y		(std::wstring(L"AboutWindow_LastPosition_Y"));

const int			Settings_AboutWindow::ABUTWND_W				= 400;
const int			Settings_AboutWindow::ABUTWND_H				= 400;
int					Settings_AboutWindow::AbutWnd_X;
int					Settings_AboutWindow::AbutWnd_Y;
const std::wstring	Settings_AboutWindow::ABUTWND_CLASS			(std::wstring(L"AboutWindowClass"));
const std::wstring	Settings_AboutWindow::ABUTWND_TITLE			(std::wstring(L"About"));
const DWORD			Settings_AboutWindow::ABUTWND_STYLES		= WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_TABSTOP | WS_GROUP | WS_VISIBLE;
const DWORD			Settings_AboutWindow::ABUTWND_EXSTYLES		= WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT | WS_EX_LEFT | WS_EX_LTRREADING;
const DWORD			Settings_AboutWindow::ABUTWND_CLASS_STYLES	= CS_HREDRAW | CS_VREDRAW;


void Settings_AboutWindow::LoadDefaults()
{
	AbutWnd_X	= 300;
	AbutWnd_Y	= 300;
}

void Settings_AboutWindow::LoadFromFile(const IniFile & SettingsIni)
{
	AbutWnd_X	= SettingsIni.GetValueInteger(Settings::HEADER_WP__WINDOW_PROPERTIES, KEY_WP__ABOUT_X);
	AbutWnd_Y	= SettingsIni.GetValueInteger(Settings::HEADER_WP__WINDOW_PROPERTIES, KEY_WP__ABOUT_Y);
}

void Settings_AboutWindow::SaveToFile(IniFile & SettingsIni)
{
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES, KEY_WP__ABOUT_X, AbutWnd_X);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES, KEY_WP__ABOUT_Y, AbutWnd_Y);
}
