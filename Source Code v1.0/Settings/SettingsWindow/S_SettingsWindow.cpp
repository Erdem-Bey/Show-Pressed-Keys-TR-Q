#include "..\..\Settings\Settings.h"

#include "..\..\IniFile\IniFile.h"
#include "..\..\Settings\SettingsWindow\S_SettingsWindow.h"


const std::wstring	Settings_SettingsWindow::KEY_WP__SETTINGS_X				(std::wstring(L"SettingsWindow_LastPosition_X"));
const std::wstring	Settings_SettingsWindow::KEY_WP__SETTINGS_Y				(std::wstring(L"SettingsWindow_LastPosition_Y"));

const std::wstring	Settings_SettingsWindow::KEY_WP__LAST_SELECTED			(std::wstring(L"Settings_LastSelectedOptionSet"));

int					Settings_SettingsWindow::SettWnd_X;
int					Settings_SettingsWindow::SettWnd_Y;
const std::wstring	Settings_SettingsWindow::SETTWND_CLASS			  (std::wstring(L"SettingsWindowClass"));
const std::wstring	Settings_SettingsWindow::SETTWND_TITLE			  (std::wstring(L"Settings"));
const DWORD			Settings_SettingsWindow::SETTWND_STYLES			= WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_TABSTOP | WS_GROUP | WS_VISIBLE;
const DWORD			Settings_SettingsWindow::SETTWND_EXSTYLES		= WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT | WS_EX_LEFT | WS_EX_LTRREADING;
const DWORD			Settings_SettingsWindow::SETTWND_CLASS_STYLES	= CS_HREDRAW | CS_VREDRAW;


void Settings_SettingsWindow::LoadDefaults()
{
	SettWnd_X							= 200;
	SettWnd_Y							= 200;
	Model::SettingsWindow::LastPanelId	= 0;
}

void Settings_SettingsWindow::LoadFromFile(const IniFile & SettingsIni)
{
	SettWnd_X							= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__SETTINGS_X);
	SettWnd_Y							= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__SETTINGS_Y);
	Model::SettingsWindow::LastPanelId	= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__LAST_SELECTED);
}

void Settings_SettingsWindow::SaveToFile(IniFile & SettingsIni)
{
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__SETTINGS_X,				SettWnd_X);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__SETTINGS_Y,				SettWnd_Y);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__LAST_SELECTED,			Model::SettingsWindow::LastPanelId);
}
