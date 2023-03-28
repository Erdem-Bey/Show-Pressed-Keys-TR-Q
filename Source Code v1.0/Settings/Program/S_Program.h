#pragma once
#ifndef HANCOPY__SETTINGS_PROGRAM_H
#define HANCOPY__SETTINGS_PROGRAM_H

#include <stdint.h>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>

//#include "..\..\Types.h"
#include "..\..\IniFile\IniFile.h"


class Settings_Program
{
	public:
		Settings_Program()							= delete;
		Settings_Program(const Settings_Program &)	= delete;
		~Settings_Program() {};
		
		static const std::wstring				HEADER__PROGRAM;			//(std::wstring(L"Program"));
		static const std::wstring				KEY__LANGUAGE;				//(std::wstring(L"Language"));
		

		//static void Initialize();
		
		static void LoadDefaults();
		static void LoadFromFile(const	IniFile & SettingsIni);
		static void SaveToFile(			IniFile & SettingsIni);

		//static Languages Language;

		

	private:
		
		
		
		
		
};

#endif // HANCOPY__SETTINGS_PROGRAM_H
