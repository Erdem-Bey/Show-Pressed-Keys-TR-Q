#include "G_Settings.h"

#include <thread>

#include "..\..\Gui\Gui.h"
#include "..\..\Model\Model.h"


void WindowSettings::CreateChildren()
{
	// The List Box
	ListBx			.Create(0, 0,	LISTBOX_WIDTH,	400,	Gui::hInstance,	Window.hWnd,				ID_LISTBOX,		ListBox::DEFAULT_STYLES,	ListBox::DEFAULT_EXSTYLES);
	ListBx			.Items = std::vector<std::wstring>({L"Colors", L"Language"});
	ListBx			.ReloadItems();
	ListBx			.SelectItem(Model::SettingsWindow::LastPanelId);

	// The Save Button
	bt00Save		.Create(0,0,	100,			35,		Gui::hInstance,	Window.hWnd,	L"Save",	ID_BT00_SAVE,	Button::DEFAULT_STYLES,		Button::DEFAULT_EXSTYLES);
	bt00Save		.AlignTo(ListBx,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	0);

	/*new std::thread([&]()
	{
		Sleep(1000);
		bt00Save		.Disable();
	});*/

	OptionBox_SelectionChanged();
}

