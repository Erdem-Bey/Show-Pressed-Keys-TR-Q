#include "..\..\Settings\Settings.h"

#include "..\..\IniFile\IniFile.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Settings\UsageWindow\S_UsageWindow.h"


const std::wstring	Settings_UsageWindow::KEY_WP__USAGE_X			(std::wstring(L"UsageWindow_LastPosition_X"));
const std::wstring	Settings_UsageWindow::KEY_WP__USAGE_Y			(std::wstring(L"UsageWindow_LastPosition_Y"));
int					Settings_UsageWindow::UsgeWnd_X;
int					Settings_UsageWindow::UsgeWnd_Y;
const std::wstring	Settings_UsageWindow::USGEWND_CLASS				(std::wstring(L"UsageWindowClass"));
const std::wstring	Settings_UsageWindow::USGEWND_TITLE				(std::wstring(L"Usage"));
const DWORD			Settings_UsageWindow::USGEWND_STYLES			= WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_TABSTOP | WS_GROUP | WS_VISIBLE;
const DWORD			Settings_UsageWindow::USGEWND_EXSTYLES			= WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT | WS_EX_LEFT | WS_EX_LTRREADING;
const DWORD			Settings_UsageWindow::USGEWND_CLASS_STYLES		= CS_HREDRAW | CS_VREDRAW;


void Settings_UsageWindow::LoadDefaults()
{
	UsgeWnd_X	= 200;
	UsgeWnd_Y	= 200;
}

void Settings_UsageWindow::LoadFromFile(const IniFile & SettingsIni)
{
	UsgeWnd_X	= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__USAGE_X);
	UsgeWnd_Y	= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__USAGE_Y);
}

void Settings_UsageWindow::SaveToFile(IniFile & SettingsIni)
{
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__USAGE_X,	UsgeWnd_X);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__USAGE_Y,	UsgeWnd_Y);
}
