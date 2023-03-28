#pragma once
#ifndef HANCOPY__SETTINGS_ABOUT_WINDOW_H
#define HANCOPY__SETTINGS_ABOUT_WINDOW_H

#include <stdint.h>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>

#include "..\..\IniFile\IniFile.h"


class Settings_AboutWindow
{
	public:
		Settings_AboutWindow()								= delete;
		Settings_AboutWindow(const Settings_AboutWindow &)	= delete;
		~Settings_AboutWindow() {};
		
		static const std::wstring				KEY_WP__ABOUT_X;				//(std::wstring(L"AboutWindow_LastPosition_X"));
		static const std::wstring				KEY_WP__ABOUT_Y;				//(std::wstring(L"AboutWindow_LastPosition_Y"));
		
		static const int						ABUTWND_W;
		static const int						ABUTWND_H;
		static const std::wstring				ABUTWND_CLASS;
		static const std::wstring				ABUTWND_TITLE;
		static const DWORD						ABUTWND_STYLES;
		static const DWORD						ABUTWND_EXSTYLES;
		static const DWORD						ABUTWND_CLASS_STYLES;

		static int								AbutWnd_X;
		static int								AbutWnd_Y;

		
		static void LoadDefaults();
		static void LoadFromFile(const	IniFile & SettingsIni);
		static void SaveToFile(			IniFile & SettingsIni);


		

	private:
		
		
		
		
		
};

#endif // HANCOPY__SETTINGS_ABOUT_WINDOW_H
