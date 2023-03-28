#include "G_Settings.h"

#include <Windows.h>
#include <sstream>

#include "..\..\Gui\Gui.h"
#include "..\..\Controller\Controller.h"
//#include "..\..\Resource.h"
//#include "..\..\Settings\Settings.h"
//#include "..\..\Strings\Strings.h"
#include "..\..\Gui\((WindowClasses))\Utility.h"


void WindowSettings::ShowPanel_01()
{
	st01Message	.Create(LISTBOX_WIDTH + 2 * COLUMN_WIDTH,   LINE_HEIGHT,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Choose your language.",			ID_ST01_MESSAGE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st01Message	.UpdateFontProperty_Weight(200);
	rd01English	.Create(0, 0, LABEL_WIDTH, LINE_HEIGHT, Gui::hInstance, Window.hWnd, Controller::SettingsWindow::GetLanguageName(Languages::English),	ID_RD01_ENGLISH, Radio::DEFAULT_STYLES, Radio::DEFAULT_EXSTYLES);
	rd01Turkish	.Create(0, 0, LABEL_WIDTH, LINE_HEIGHT, Gui::hInstance, Window.hWnd, Controller::SettingsWindow::GetLanguageName(Languages::Turkish),	ID_RD01_TURKISH, Radio::DEFAULT_STYLES, Radio::DEFAULT_EXSTYLES);
	rd01Arabic	.Create(0, 0, LABEL_WIDTH, LINE_HEIGHT, Gui::hInstance, Window.hWnd, Controller::SettingsWindow::GetLanguageName(Languages::Arabic),	ID_RD01_ENGLISH, Radio::DEFAULT_STYLES, Radio::DEFAULT_EXSTYLES);
	rd01Japanese.Create(0, 0, LABEL_WIDTH, LINE_HEIGHT, Gui::hInstance, Window.hWnd, Controller::SettingsWindow::GetLanguageName(Languages::Japanese),	ID_RD01_ENGLISH, Radio::DEFAULT_STYLES, Radio::DEFAULT_EXSTYLES);
	
	rd01English	.AlignTo(st01Message,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	rd01Turkish	.AlignTo(rd01English,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	rd01Arabic	.AlignTo(rd01Turkish,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	rd01Japanese.AlignTo(rd01Arabic,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);

	UpdatePanel01_Language(Controller::SettingsWindow::GetLanguage());
}

void WindowSettings::HidePanel_01()
{
	st01Message	.Destroy();
	rd01English	.Destroy();
	rd01Turkish	.Destroy();
	rd01Arabic	.Destroy();
	rd01Japanese.Destroy();
}

void WindowSettings::UpdatePanel01_Language(const Languages & SelectedLanguage)
{
	Gui::SettWnd.rd01English	.Uncheck();
	Gui::SettWnd.rd01Turkish	.Uncheck();
	Gui::SettWnd.rd01Arabic		.Uncheck();
	Gui::SettWnd.rd01Japanese	.Uncheck();
	switch (SelectedLanguage)
	{
		case Languages::English:
			Gui::SettWnd.rd01English	.Check();
			break;
		case Languages::Turkish:
			Gui::SettWnd.rd01Turkish	.Check();
			break;
		case Languages::Arabic:
			Gui::SettWnd.rd01Arabic		.Check();
			break;
		case Languages::Japanese:
			Gui::SettWnd.rd01Japanese	.Check();
			break;
	}
}

