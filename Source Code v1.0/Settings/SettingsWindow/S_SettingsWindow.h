#pragma once
#ifndef HANCOPY__SETTINGS_SETTINGS_WINDOW_H
#define HANCOPY__SETTINGS_SETTINGS_WINDOW_H

#include <string>
#include <Windows.h>

#include "..\..\IniFile\IniFile.h"


class Settings_SettingsWindow
{
	public:
		Settings_SettingsWindow()									= delete;
		Settings_SettingsWindow(const Settings_SettingsWindow &)	= delete;
		~Settings_SettingsWindow() {};

		static const std::wstring				KEY_WP__SETTINGS_X;				//(std::wstring(L"SettingsWindow_LastPosition_X"));
		static const std::wstring				KEY_WP__SETTINGS_Y;				//(std::wstring(L"SettingsWindow_LastPosition_Y"));

		static const std::wstring				KEY_WP__LAST_SELECTED;			//(std::wstring(L"Settings_LastSelectedOptionSet"));
		

		static constexpr int					SETTWND_W						= 700;
		static constexpr int					SETTWND_H						= 520;
		static const std::wstring				SETTWND_CLASS;
		static const std::wstring				SETTWND_TITLE;
		static const DWORD						SETTWND_STYLES;
		static const DWORD						SETTWND_EXSTYLES;
		static const DWORD						SETTWND_CLASS_STYLES;

		static int								SettWnd_X;
		static int								SettWnd_Y;
		

		//static void Initialize();
		
		static void LoadDefaults();
		static void LoadFromFile(const	IniFile & SettingsIni);
		static void SaveToFile(			IniFile & SettingsIni);


		

	private:
		
		
		
		
		
};

#endif // HANCOPY__SETTINGS_ABOUT_WINDOW_H
