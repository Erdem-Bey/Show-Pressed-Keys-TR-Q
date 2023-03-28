#include "G_Main.h"

#include <Windows.h>

#include "..\..\Types.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Gui\Gui.h"
#include "..\..\Controller\Controller.h"
#include "..\..\Utility\SerialPort.h"
#include "..\..\Utility\SerialPortListener.h"
#include "..\..\Utility\Crc8.h"


// WINDOW EVENTS

void WindowMain::Button_Refresh_OnClick()
{
	cbPort.Items = SerialPort::EnumerateSerialPorts();
	cbPort.ReloadItems();
	
	/*cbPort.Items.clear();
	cbPort.Items.push_back(L"COM3");
	cbPort.Items.push_back(L"COM4");
	cbPort.Items.push_back(L"COM5");
	cbPort.ReloadItems();*/
}

void WindowMain::Button_Connect_OnClick()
{
	const size_t NumberOfPorts = cbPort.Items.size();
	if (NumberOfPorts == 0)
	{
		ShowComError(L"I couldn't find any COM ports your computer!\r\nMaybe there is a driver problem, or you forgot to connect the device, or the device is broken. Make sure that your computer can detect COM devices properly.");
		return;
	}
	const size_t SelectedPortIndex = cbPort.GetSelectedItem();
	if (SelectedPortIndex >= NumberOfPorts)
	{
		ShowComError(L"Don't forgetto select a port from the list!");
		return;
	}
	const std::wstring SelectedPortName = cbPort.Items[SelectedPortIndex];


	// Try to open the port.
	SerialPort::Errors Error = CommPort.Open(L"\\\\.\\" + SelectedPortName);
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error);
		return;
	}
	
	// Read the user's port settigns.
	SerialPort::BaudRates	BaudRate;
	SerialPort::Parity		Parity;
	BYTE					ByteSize;
	SerialPort::StopBits	StopBits;
	GetComPortSettings(BaudRate, Parity, ByteSize, StopBits);

	// Apply the default settings. This may not be necessary.
	CommPort.SetDeafultSettings();

	// Baud rate.
	Error = CommPort.SetBaudRate(BaudRate);
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error, L"Error changing the baud rate!");
		return;
	}

	// Parity.
	Error = CommPort.SetParity(Parity);
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error, L"Error changing the parity option!");
		return;
	}

	// Number of data bits in a byte.
	Error = CommPort.SetByteSize(ByteSize);
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error, L"Error changing the number of data bits!");
		return;
	}

	// Number of stop bits.
	Error = CommPort.SetStopBits(StopBits);
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error, L"Error changing the number of stop bits!");
		return;
	}

	// If we could reach here, change the GUI accordingly.
	stUartStatus.SetText(L"Connected");
	stUartMessage.Hide();
	btConnect.Disable();
	btDisconnect.Enable();
}

void WindowMain::OnNewByteReceived(SerialPort & SerialPort)
{
	Controller::MainWindow::OnNewByteReceived(SerialPort);
}

void WindowMain::ShowComError(const SerialPort::Errors & Error)
{
	const std::wstring ErrorText	= SerialPort::GetErrorText(Error)
									+ L"\r\n GetLastError() returned: "
									+ std::to_wstring(CommPort.LastError);
	stUartMessage.Show();
	stUartStatus.SetText(L"ERROR");
	stUartMessage.SetText(ErrorText);
}

void WindowMain::ShowComError(const std::wstring & ErrorText)
{
	stUartMessage.Show();
	stUartStatus.SetText(L"ERROR");
	stUartMessage.SetText(ErrorText);
}

void WindowMain::ShowComError(const SerialPort::Errors & Error, const std::wstring & ErrorNote)
{
	const std::wstring ErrorText	= SerialPort::GetErrorText(Error)
									+ L"\r\n GetLastError() returned: "
									+ std::to_wstring(CommPort.LastError);
	stUartMessage.Show();
	stUartStatus.SetText(L"ERROR");
	stUartMessage.SetText(ErrorNote + L"\r\n" + ErrorText);
}

void WindowMain::Button_Disconnect_OnClick()
{
	// Try to close the port.
	SerialPort::Errors Error = CommPort.Close();
	if (Error != SerialPort::Errors::Success)
	{
		ShowComError(Error);
		return;
	}

	// If we could reach here, change the GUI accordingly.
	stUartStatus.SetText(L"Disconnected.");
	stUartMessage.Hide();
	btConnect.Enable();
	btDisconnect.Disable();
}

void WindowMain::Button_ApplyChanges_OnClick()
{

}

void WindowMain::Button_On_OnClick(const size_t GpioId)
{
	Controller::MainWindow::WriteToGpio(GpioId, true);
}

void WindowMain::Button_Off_OnClick(const size_t GpioId)
{
	Controller::MainWindow::WriteToGpio(GpioId, false);
}

void WindowMain::Button_In_OnClick(const size_t GpioId)
{
	Controller::MainWindow::SetGpioDirection(GpioId, true);
}

void WindowMain::Button_Out_OnClick(const size_t GpioId)
{
	Controller::MainWindow::SetGpioDirection(GpioId, false);
}

void WindowMain::Button_Debug0_OnClick()
{
	std::vector<ByteType> Package;
	Package.push_back(Constants::Package_Sender_DeviceToPc);
	Package.push_back(Constants::Package_Type_Read);
	Package.push_back(0b1100'0011);
	Package.push_back(0b0101'1010);
	Package.push_back(0b0000'1111);
	Package.push_back(0b0011'0000);
	Package.push_back(Crc8::Calculate(Package));
	Package.push_back(Constants::END_FLAG);
	Controller::MainWindow::ParsePackage(Package, false);
}

void WindowMain::Button_Debug1_OnClick()
{
	std::vector<ByteType> Package;
	Package.push_back(Constants::Package_Sender_DeviceToPc);
	Package.push_back(Constants::Package_Type_Read);
	Package.push_back(0b1001'0011);
	Package.push_back(0b0110'1100);
	Package.push_back(0b0110'1100);
	Package.push_back(0b1001'0011);
	Package.push_back(Crc8::Calculate(Package));
	Package.push_back(Constants::END_FLAG);
	Controller::MainWindow::ParsePackage(Package, false);
}

void WindowMain::Button_Debug2_OnClick()
{
	std::vector<ByteType> Package;
	Package.push_back(Constants::Package_Sender_DeviceToPc);
	Package.push_back(Constants::Package_Type_Read);
	Package.push_back(0b1111'0000);
	Package.push_back(0b0000'1111);
	Package.push_back(0b1111'0000);
	Package.push_back(0b0000'1111);
	Package.push_back(Crc8::Calculate(Package));
	Package.push_back(Constants::END_FLAG);
	Controller::MainWindow::ParsePackage(Package, false);
}

void WindowMain::Button_Debug3_OnClick()
{
	std::vector<ByteType> Package;
	Package.push_back(Constants::Package_Sender_DeviceToPc);
	Package.push_back(Constants::Package_Type_Read);
	Package.push_back(0b0000'0000);
	Package.push_back(0b0000'0000);
	Package.push_back(0b1111'1111);
	Package.push_back(0b1111'1111);
	Package.push_back(Crc8::Calculate(Package));
	Package.push_back(Constants::END_FLAG);
	Controller::MainWindow::ParsePackage(Package, false);
}


/*void WindowMain::Radio_Count_Selected()
{
	//Controller::MainWindow::UpdateGui_TimingPlan(Model::MainWindow::TIMING_PLAN::COUNTDOWN);
	Gui::MainWnd.Enable_Countdown_Controls();
	Gui::MainWnd.Disable_DateTime_Controls();
	Controller::MainWindow::GuiUpdated_TimingPlan(TIMING_PLAN::COUNTDOWN);
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Type Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Countdown");
}

void WindowMain::Radio_Count_Indeterminate()
{
}

void WindowMain::Radio_Count_Unselected()
{
}

void WindowMain::Radio_Date_Selected()
{
	//Controller::MainWindow::UpdateGui_TimingPlan(Model::MainWindow::TIMING_PLAN::DATETIME);
	Gui::MainWnd.Enable_DateTime_Controls();
	Gui::MainWnd.Disable_Countdown_Controls();
	Controller::MainWindow::GuiUpdated_TimingPlan(TIMING_PLAN::DATETIME);
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Type Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Date/Time");
}

void WindowMain::Radio_Date_Indeterminate()
{
}

void WindowMain::Radio_Date_Unselected()
{
}

void WindowMain::Edit_Count_Days_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Days: Changed");
	Controller::MainWindow::Countdown::GuiUpdated_Days(Gui::MainWnd.edCD_Days.GetContent<Model::MainWindow::Countdown::TypeDays>());
}

void WindowMain::Edit_Count_Days_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Days: Got Focus");
}

void WindowMain::Edit_Count_Days_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Days: Lost Focus");
}

void WindowMain::Edit_Count_Hours_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Changed");
	Controller::MainWindow::Countdown::GuiUpdated_Hours(Gui::MainWnd.edCD_Hours.GetContent<Model::MainWindow::Countdown::TypeHours>());
}

void WindowMain::Edit_Count_Hours_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Got Focus");
}

void WindowMain::Edit_Count_Hours_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Lost Focus");
}

void WindowMain::Edit_Count_Minutes_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Changed");
	Controller::MainWindow::Countdown::GuiUpdated_Minutes(Gui::MainWnd.edCD_Minutes.GetContent<Model::MainWindow::Countdown::TypeMinutes>());
}

void WindowMain::Edit_Count_Minutes_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Got Focus");
}

void WindowMain::Edit_Count_Minutes_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Lost Focus");
}

void WindowMain::Edit_Count_Seconds_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Changed");
	Controller::MainWindow::Countdown::GuiUpdated_Seconds(Gui::MainWnd.edCD_Seconds.GetContent<Model::MainWindow::Countdown::TypeSeconds>());
}

void WindowMain::Edit_Count_Seconds_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Got Focus");
}

void WindowMain::Edit_Count_Seconds_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Countdown Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Lost Focus");
}

void WindowMain::Edit_Date_Hours_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Changed");
}

void WindowMain::Edit_Date_Hours_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Got Focus");
}

void WindowMain::Edit_Date_Hours_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hours: Lost Focus");
}

void WindowMain::Edit_Date_Minutes_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Changed");
}

void WindowMain::Edit_Date_Minutes_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Got Focus");
}

void WindowMain::Edit_Date_Minutes_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Minutes: Lost Focus");
}

void WindowMain::Edit_Date_Seconds_OnChange()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Changed");
}

void WindowMain::Edit_Date_Seconds_OnFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Got Focus");
}

void WindowMain::Edit_Date_Seconds_OnLoseFocus()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Date/Time Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Seconds: Lost Focus");
}

void WindowMain::Radio_Type_Shutdown_Selected()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Mode Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Shutdown");
	Controller::MainWindow::GuiUpdated_Termination(TERMINATION::SHUTDOWN);
	cbUpdates.Enable();
}

void WindowMain::Radio_Type_Shutdown_Indeterminate()
{
}

void WindowMain::Radio_Type_Shutdown_Unselected()
{
}

void WindowMain::Radio_Type_Restart_Selected()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Mode Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Restart");
	Controller::MainWindow::GuiUpdated_Termination(TERMINATION::RESTART);
	cbUpdates.Enable();
}

void WindowMain::Radio_Type_Restart_Indeterminate()
{
}

void WindowMain::Radio_Type_Restart_Unselected()
{
}

void WindowMain::Radio_Type_Logout_Selected()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Mode Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Logout");
	Controller::MainWindow::GuiUpdated_Termination(TERMINATION::LOGOUT);
	cbUpdates.Disable();
}

void WindowMain::Radio_Type_Logout_Indeterminate()
{
}

void WindowMain::Radio_Type_Logout_Unselected()
{
}

void WindowMain::Radio_Type_Sleep_Selected()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Mode Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Sleep");
	Controller::MainWindow::GuiUpdated_Termination(TERMINATION::SLEEP);
	cbUpdates.Disable();
}

void WindowMain::Radio_Type_Sleep_Indeterminate()
{
}

void WindowMain::Radio_Type_Sleep_Unselected()
{
}

void WindowMain::Radio_Type_Hibernate_Selected()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Mode Changed");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Hibernate");
	Controller::MainWindow::GuiUpdated_Termination(TERMINATION::HIBERNATE);
}

void WindowMain::Radio_Type_Hibernate_Indeterminate()
{
}

void WindowMain::Radio_Type_Hibernate_Unselected()
{
}

void WindowMain::CheckBox_Force_Checked()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Check Box");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Force: Checked");
	Controller::MainWindow::GuiUpdated_Force(true);
}

void WindowMain::CheckBox_Force_Indeterminate()
{
}

void WindowMain::CheckBox_Force_Unchecked()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Check Box");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Force: Unchecked");
	Controller::MainWindow::GuiUpdated_Force(false);
}

void WindowMain::CheckBox_Updates_Checked()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Check Box");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Install Updates: Checked");
	Controller::MainWindow::GuiUpdated_Updates(true);
}

void WindowMain::CheckBox_Updates_Indeterminate()
{
}

void WindowMain::CheckBox_Updates_Unchecked()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Check Box");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Install Updates: Unchecked");
	Controller::MainWindow::GuiUpdated_Updates(false);
}

void WindowMain::Button_Start_OnClick()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Start Button");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Clicked");
	Controller::MainWindow::GuiUpdated_StartButton();
	Gui::MainWnd.Paint_Button_Stop(Gui::MainWnd.btStop.hWnd);
	Gui::MainWnd.Paint_StatusBar_Progress();
	Gui::MainWnd.SttsBar.SetPartText(0, L"Running...");
}

void WindowMain::Button_Stop_OnClick()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Stop Button");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Clicked");
	Controller::MainWindow::GuiUpdated_StopButton();
	Gui::MainWnd.Paint_Button_Start(Gui::MainWnd.btStart.hWnd);
	Gui::MainWnd.SttsBar.SetPartText(0, L"Stopped.");
	//HANDLE hImage = LoadImageW(Gui::hInstance, L"Graphics\\Approve.ico",	IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	//Gui::MainWnd.TrayIcon.Balloon(	L"Button 2",
	//L"You have just clicked the Button #2.",
	//(HICON) hImage,
	//SystemTrayIcon::BALLOON_ICON_TYPE::BIT_USER_DEFINED,
	//20000U,
	//true,
	//true,
	//false);
}

void WindowMain::Calendar_OnSelectionChange()
{
	SYSTEMTIME SystemTime;
	SendMessageW(cdCalendar.hWnd, MCM_GETCURSEL, 0, reinterpret_cast<LPARAM>(&SystemTime));
	std::wostringstream Woss;
	Woss.fill(L'0');
	Woss << std::setw(4) << SystemTime.wYear			<< L'-';
	Woss << std::setw(2) << SystemTime.wMonth			<< L'-';
	Woss << std::setw(2) << SystemTime.wDay;
	//Woss << SystemTime.wDayOfWeek;
	Woss												<< L'_';
	Woss << std::setw(2) << SystemTime.wHour			<< L':';
	Woss << std::setw(2) << SystemTime.wMinute			<< L':';
	Woss << std::setw(2) << SystemTime.wSecond			<< L'.';
	Woss << std::setw(3) << SystemTime.wMilliseconds;
	Controller::MainWindow::DateTime::GuiUpdated_Calendar(SystemTime);
	Gui::MainWnd.SttsBar.SetPartText(0, Woss.str());
	//Gui::MainWnd.SttsBar.SetPartText(3, woss.str().c_str());
}*/


// MENU EVENTS

void WindowMain::Menu_File()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"File");
}

void WindowMain::Menu_File_Settings()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"File > Settings");
	Gui::SettWnd.Create();
}

void WindowMain::Menu_File_Exit()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"File > Exit");
	DestroyWindow(Gui::MainWnd.GetHandle());
}

void WindowMain::Menu_Help()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Help");
}

void WindowMain::Menu_Help_Usage()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Help > Usage");
	Gui::UsgeWnd.Create();
}

void WindowMain::Menu_Help_About()
{
	//Gui::MainWnd.SttsBar.SetPartText(2, L"Menu");
	//Gui::MainWnd.SttsBar.SetPartText(3, L"Help > About");
	Gui::AbutWnd.Create();
}

