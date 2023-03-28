#include "..\..\Settings\Settings.h"

#include <Windows.h>
#include <fstream>

#include "..\..\IniFile\IniFile.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Settings\MainWindow\S_MainWindow.h"


const std::wstring	Settings_MainWindow::HEADER__LAST_USAGE								(std::wstring(L"LastUsage_MainWindow"));
const std::wstring	Settings_MainWindow::HEADER__COLORS									(std::wstring(L"Colors"));

const std::wstring	Settings_MainWindow::KEY_WP__MAIN_X									(std::wstring(L"MainWindow_LastPosition_X"));
const std::wstring	Settings_MainWindow::KEY_WP__MAIN_Y									(std::wstring(L"MainWindow_LastPosition_Y"));
const std::wstring	Settings_MainWindow::KEY_WP__MAIN_W									(std::wstring(L"MainWindow_LastSize_W"));
const std::wstring	Settings_MainWindow::KEY_WP__MAIN_H									(std::wstring(L"MainWindow_LastSize_H"));
const std::wstring	Settings_MainWindow::KEY_WP__OPACITY								(std::wstring(L"MainWindow_Opacity"));

int					Settings_MainWindow::MainWnd_X;
int					Settings_MainWindow::MainWnd_Y;
int					Settings_MainWindow::MainWnd_W;
int					Settings_MainWindow::MainWnd_H;
const std::wstring	Settings_MainWindow::MAINWND_CLASS									(std::wstring(L"MainWindowClass"));
const std::wstring	Settings_MainWindow::MAINWND_TITLE									(std::wstring(L"Han Software - Show Input Keys"));
BYTE				Settings_MainWindow::Opacity										(255);



void Settings_MainWindow::LoadDefaults()
{
	MainWnd_X														= 100;
	MainWnd_Y														= 100;
	MainWnd_W														= 1000;
	MainWnd_H														= 540;
	Opacity															= 255;
}

void Settings_MainWindow::LoadFromFile(const IniFile & SettingsIni)
{
	MainWnd_X														= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_X);
	MainWnd_Y														= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_Y);
	MainWnd_W														= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_W);
	MainWnd_H														= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_H);
	Opacity															= SettingsIni.GetValueInteger	(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__OPACITY);
}

void Settings_MainWindow::SaveToFile(IniFile & SettingsIni)
{
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_X,		MainWnd_X);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_Y,		MainWnd_Y);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_W,		MainWnd_W);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__MAIN_H,		MainWnd_H);
	SettingsIni.SetValue(Settings::HEADER_WP__WINDOW_PROPERTIES,	KEY_WP__OPACITY,	Opacity);
}

