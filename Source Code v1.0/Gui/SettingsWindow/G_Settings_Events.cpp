#include "G_Settings.h"

#include "..\..\Controller\Controller.h"


void WindowSettings::OptionBox_SelectionChanged()
{
	switch (Model::SettingsWindow::LastPanelId)
	{
		case 0:
			HidePanel_00();
			break;
		case 1:
			HidePanel_01();
			break;
	}

	Model::SettingsWindow::LastPanelId = Gui::SettWnd.ListBx.GetSelectedItem();

	switch (Model::SettingsWindow::LastPanelId)
	{
		case 0:
			ShowPanel_00();
			break;
		case 1:
			ShowPanel_01();
			break;
	}
}

void WindowSettings::SaveButton_Clicked()
{
	Controller::SettingsWindow::SaveSettings();
	Gui::SettWnd.bt00Save.Disable();
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EVENTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WindowSettings::OnClick_Panel01_Radio_Language(const Languages & /*SelectedLanguage*/)
{
	Gui::SettWnd.bt00Save.Enable();
}

