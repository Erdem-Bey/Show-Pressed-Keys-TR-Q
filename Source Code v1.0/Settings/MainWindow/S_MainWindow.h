#pragma once
#ifndef HANCOPY__SETTINGS_MAIN_WINDOW_H
#define HANCOPY__SETTINGS_MAIN_WINDOW_H

#include <stdint.h>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>
#include <Gdiplus.h>

#include "..\..\IniFile\IniFile.h"


class Settings_MainWindow
{
	public:
		Settings_MainWindow()								= delete;
		Settings_MainWindow(const Settings_MainWindow &)	= delete;

		// Settings file header and key names.
		
		//static const std::wstring				HEADER__WINDOW_PROPERTIES;						//(std::wstring(L"WindowProperties"));
		static const std::wstring				HEADER__LAST_USAGE;								//(std::wstring(L"LastUsage_MainWindow"));
		static const std::wstring				HEADER__COLORS;									//(std::wstring(L"Colors"));

		static const std::wstring				KEY_WP__MAIN_X;									//(std::wstring(L"MainWindow_LastPosition_X"));
		static const std::wstring				KEY_WP__MAIN_Y;									//(std::wstring(L"MainWindow_LastPosition_Y"));
		static const std::wstring				KEY_WP__MAIN_W;									//(std::wstring(L"MainWindow_LastSize_W"));
		static const std::wstring				KEY_WP__MAIN_H;									//(std::wstring(L"MainWindow_LastSize_H"));
		static const std::wstring				KEY_WP__OPACITY;								//(std::wstring(L"MainWindow_Opacity"));

		static void LoadDefaults();
		static void LoadFromFile(const	IniFile & SettingsIni);
		static void SaveToFile(			IniFile & SettingsIni);

		// Unmodifiable data
		static constexpr	int					MAINWND_NOMINAL_W		= 1000;
		static constexpr	int					MAINWND_NOMINAL_H		= 540;
		static constexpr	DWORD				MAINWND_STYLES			= WS_CLIPCHILDREN | WS_CAPTION*0 | WS_MINIMIZEBOX*0 | WS_SYSMENU*0 | WS_TABSTOP*0 | WS_GROUP*0 | WS_VISIBLE | WS_BORDER*0 | WS_THICKFRAME | WS_OVERLAPPEDWINDOW*0;
		static constexpr	DWORD				MAINWND_EXSTYLES		= WS_EX_ACCEPTFILES*0 | WS_EX_CONTROLPARENT*0 | WS_EX_LEFT*0 | WS_EX_LTRREADING*0 | WS_EX_LAYERED;
		static constexpr	DWORD				MAINWND_CLASS_STYLES	= CS_HREDRAW | CS_VREDRAW;
		static const		std::wstring		MAINWND_CLASS;
		static const		std::wstring		MAINWND_TITLE;
		static constexpr	HBRUSH				MAINWND_BACKGROUND		= reinterpret_cast<HBRUSH>(COLOR_WINDOW);

		// Modifiable data
		static int								MainWnd_X;
		static int								MainWnd_Y;
		static int								MainWnd_W;
		static int								MainWnd_H;
		static BYTE								Opacity;

	private:



};

#endif // HANCOPY__SETTINGS_MAIN_WINDOW_H
