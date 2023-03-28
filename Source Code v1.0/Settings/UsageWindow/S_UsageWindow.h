#pragma once
#ifndef HANCOPY__SETTINGS_USAGE_WINDOW_H
#define HANCOPY__SETTINGS_USAGE_WINDOW_H

#include <stdint.h>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>

#include "..\..\IniFile\IniFile.h"


class Settings_UsageWindow
{
	public:
		Settings_UsageWindow()								= delete;
		Settings_UsageWindow(const Settings_UsageWindow &)	= delete;
		~Settings_UsageWindow() {};

		static const std::wstring				KEY_WP__USAGE_X;				//(std::wstring(L"UsageWindow_LastPosition_X"));
		static const std::wstring				KEY_WP__USAGE_Y;				//(std::wstring(L"UsageWindow_LastPosition_Y"));

		static constexpr int					USGEWND_W	= 800;
		static constexpr int					USGEWND_H	= 600;

		static const std::wstring				USGEWND_CLASS;
		static const std::wstring				USGEWND_TITLE;
		static const DWORD						USGEWND_STYLES;
		static const DWORD						USGEWND_EXSTYLES;
		static const DWORD						USGEWND_CLASS_STYLES;

		static int								UsgeWnd_X;
		static int								UsgeWnd_Y;
		

		//static void Initialize();
		
		static void LoadDefaults();
		static void LoadFromFile(const	IniFile & SettingsIni);
		static void SaveToFile(			IniFile & SettingsIni);


		

	private:
		
		
		
		
		
};

#endif // HANCOPY__SETTINGS_USAGE_WINDOW_H
