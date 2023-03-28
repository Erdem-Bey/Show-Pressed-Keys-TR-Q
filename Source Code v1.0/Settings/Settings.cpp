#include "Settings.h"

#include <Windows.h>

#include "..\IniFile\IniFile.h"


const		std::wstring					Settings::SETTINGS_FILE					(std::wstring(L"Settings.ini"));
const		std::wstring					Settings::HEADER_WP__WINDOW_PROPERTIES	(std::wstring(L"WindowProperties"));

constexpr	wchar_t							Settings::QUOTE;
constexpr	std::array<unsigned char, 3267>	Settings::DefaultSettingsFileBytes;


void Settings::LoadDefaults()
{
	//Settings::Program		::LoadDefaults();
	Settings::MainWindow	::LoadDefaults();
	//Settings::SettingsWindow::LoadDefaults();
	//Settings::UsageWindow	::LoadDefaults();
	//Settings::AboutWindow	::LoadDefaults();
}

void Settings::LoadFromFile()
{
	if (!Settings::DoesFileExist(SETTINGS_FILE))
	{
		CreateDefaultSettingsFile();
	}
	try
	{
		IniFile SettingsIni(SETTINGS_FILE);
		//Settings::Program		::LoadFromFile(SettingsIni);
		Settings::MainWindow	::LoadFromFile(SettingsIni);
		//Settings::SettingsWindow::LoadFromFile(SettingsIni);
		//Settings::UsageWindow	::LoadFromFile(SettingsIni);
		//Settings::AboutWindow	::LoadFromFile(SettingsIni);
	}
	catch (...)
	{
		try
		{
			CreateDefaultSettingsFile();
			IniFile SettingsIni(SETTINGS_FILE);
			//Settings::Program		::LoadFromFile(SettingsIni);
			Settings::MainWindow	::LoadFromFile(SettingsIni);
			//Settings::SettingsWindow::LoadFromFile(SettingsIni);
			//Settings::UsageWindow	::LoadFromFile(SettingsIni);
			//Settings::AboutWindow	::LoadFromFile(SettingsIni);
		}
		catch (...)
		{
			MessageBoxW(HWND_DESKTOP, L"Error opening the settings file.", L"Loading Settings", MB_ICONERROR | MB_OK);
		}
	}
}

void Settings::SaveToFile()
{
	try
	{
		IniFile SettingsIni(SETTINGS_FILE);
		//Settings::Program		::SaveToFile(SettingsIni);
		Settings::MainWindow	::SaveToFile(SettingsIni);
		//Settings::SettingsWindow::SaveToFile(SettingsIni);
		//Settings::UsageWindow	::SaveToFile(SettingsIni);
		//Settings::AboutWindow	::SaveToFile(SettingsIni);
		SettingsIni.SaveToFile();
	}
	catch (...)
	{
		MessageBoxW(HWND_DESKTOP, L"Error opening the settings file.", L"Saving Settings", MB_ICONERROR | MB_OK);
	}
}

void Settings::CreateDefaultSettingsFile()
{
	std::ofstream SettingsFileStream(SETTINGS_FILE, /*std::ios::out |*/ std::ifstream::binary | std::ios::trunc);
	std::copy(DefaultSettingsFileBytes.cbegin(), DefaultSettingsFileBytes.cend(), std::ostreambuf_iterator<std::ostream::char_type>(SettingsFileStream));
	SettingsFileStream.close();
}

void Settings::MakeUpperCase(std::wstring & String)
{
	for (std::wstring::iterator it=String.begin(); it!=String.end(); ++it)
	{
		if ((L'a' <= *it) && (*it <= L'z'))
		{
			*it -= wchar_t(0x0020);
		}
		else
		{
			switch (*it)
			{
				case L'ç':
					*it = L'Ç';
					break;
				case L'ð':
					*it = L'Ð';
					break;
				case L'ý':
					*it = L'I';
					break;
				case L'ö':
					*it = L'Ö';
					break;
				case L'þ':
					*it = L'Þ';
					break;
				case L'ü':
					*it = L'Ü';
					break;
			}
		}
	}
}

std::wstring Settings::ReturnUpperCase(const std::wstring & String)
{
	std::wstring Return(String);
	MakeUpperCase(Return);
	return Return;
}

void Settings::AddQuotes(std::wstring & String)
{
	if ((String.front() != QUOTE) && (String.back() != QUOTE))
	{
		String.insert(0, 1, QUOTE);
		String.push_back(QUOTE);
	}
}

std::wstring Settings::ReturnWithQuotes(const std::wstring & String)
{
	std::wstring Return(String);
	AddQuotes(Return);
	return Return;
}

void Settings::RemoveQuotes(std::wstring & String)
{
	if (String.length() < 2)
	{
		return;
	}
	if ((String.front() == QUOTE) && (String.back() == QUOTE))
	{
		String.erase(0, 1);
		String.pop_back();
	}
}

std::wstring Settings::ReturnWithoutQuotes(const std::wstring & String)
{
	std::wstring Return(String);
	RemoveQuotes(Return);
	return Return;
}

