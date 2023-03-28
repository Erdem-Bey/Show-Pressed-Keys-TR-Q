#include "..\..\Settings\Settings.h"

#include "..\..\Types.h"
#include "..\..\IniFile\IniFile.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Settings\UsageWindow\S_UsageWindow.h"
#include "..\..\Model\Model.h"


//Settings_Program::Languages Settings_Program::Language;


const std::wstring	Settings_Program::HEADER__PROGRAM	(std::wstring(L"Program"));
const std::wstring	Settings_Program::KEY__LANGUAGE		(std::wstring(L"Language"));


void Settings_Program::LoadDefaults()
{
	Model::SettingsWindow::Panel01_SelectedLanguage = Languages::English;
	//Language = Languages::Turkish;
}

void Settings_Program::LoadFromFile(const IniFile & SettingsIni)
{
	const std::wstring LanguageString	= SettingsIni.GetValueString	(HEADER__PROGRAM,	KEY__LANGUAGE);
	if		(LanguageString == L"English")
	{
		Model::SettingsWindow::Panel01_SelectedLanguage = Languages::English;
	}
	else if	(LanguageString == L"Türkçe")
	{
		Model::SettingsWindow::Panel01_SelectedLanguage = Languages::Turkish;
	}
	else if	(LanguageString == L"Arabic")
	{
		Model::SettingsWindow::Panel01_SelectedLanguage = Languages::Arabic;
	}
	else if	(LanguageString == L"Japanese")
	{
		Model::SettingsWindow::Panel01_SelectedLanguage = Languages::Japanese;
	}
}

void Settings_Program::SaveToFile(IniFile & SettingsIni)
{
	std::wstring LanguageString;
	switch (Model::SettingsWindow::Panel01_SelectedLanguage)
	{
		default:
		case Languages::English:
			LanguageString = L"English";
			break;
		case Languages::Turkish:
			LanguageString = L"Türkçe";
			break;
		case Languages::Arabic:
			LanguageString = L"Arabic";
			break;
		case Languages::Japanese:
			LanguageString = L"Japanese";
			break;
	}
	SettingsIni.SetValue(HEADER__PROGRAM,	KEY__LANGUAGE,	LanguageString);
}
