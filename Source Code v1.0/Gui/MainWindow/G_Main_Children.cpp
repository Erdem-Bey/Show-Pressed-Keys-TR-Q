#include "G_Main.h"

#include <string>
#include <windows.h>

#include "..\..\Gui\Gui.h"
#include "..\..\Settings\Settings.h"
#include "G_Main_LowLevelInputData.h"


void WindowMain::CreateChildren()
{
	LoadLayout_Turkish();

	Llid::rcLogo.left		= 490;	// x
	Llid::rcLogo.right		= 300;	// y
	Llid::rcLogo.top		= 500;	// w
	Llid::rcLogo.bottom		= 190;	// h

	Llid::rcTrackbar.left	= 525;
	Llid::rcTrackbar.right	= 500;
	Llid::rcTrackbar.top	= 385;
	Llid::rcTrackbar.bottom	= 30;
	
	Llid::rcClose.left		= Llid::rcTrackbar.left + Llid::rcTrackbar.top + 50;
	Llid::rcClose.right		= Llid::rcTrackbar.right - 5;
	Llid::rcClose.top		= Llid::rcTrackbar.bottom;
	Llid::rcClose.bottom	= Llid::rcTrackbar.bottom;

	Llid::rcBuddy000.left	= Llid::rcTrackbar.left - 20;
	Llid::rcBuddy000.right	= Llid::rcTrackbar.right;
	Llid::rcBuddy000.top	= 20;
	Llid::rcBuddy000.bottom	= 20;

	Llid::rcBuddy255.left	= Llid::rcTrackbar.left + Llid::rcTrackbar.top;
	Llid::rcBuddy255.right	= Llid::rcTrackbar.right;
	Llid::rcBuddy255.top	= 20;
	Llid::rcBuddy255.bottom	= 20;

	btClose		.Create(Llid::rcClose.left,		Llid::rcClose.right,	Llid::rcClose.top,		Llid::rcClose.bottom,		Gui::hInstance, Window.hWnd,	L"X",		ID_BT_Close,		Button::DEFAULT_STYLES,				Button::DEFAULT_EXSTYLES);
	//stLogo	.Create(Llid::rcLogo.left,		Llid::rcLogo.right,		Llid::rcLogo.top,		Llid::rcLogo.bottom,		Gui::hInstance, Window.hWnd,	L"Logo",	ID_ST_Logo,			Static::DEFAULT_STYLES,				Static::DEFAULT_EXSTYLES);
	tbOpacity	.Create(Llid::rcTrackbar.left,	Llid::rcTrackbar.right,	Llid::rcTrackbar.top,	Llid::rcTrackbar.bottom,	Gui::hInstance, Window.hWnd,	/*L"ABC",	ID_TB_Opacity,*/	TrackBar::DEFAULT_STYLES,			TrackBar::DEFAULT_EXSTYLES);
	st000		.Create(Llid::rcBuddy000.left,	Llid::rcBuddy000.right,	Llid::rcBuddy000.top,	Llid::rcBuddy000.bottom,	Gui::hInstance, Window.hWnd,	L"0",		ID_ST_000,			Static::DEFAULT_STYLES | SS_RIGHT,	Static::DEFAULT_EXSTYLES);
	st255		.Create(Llid::rcBuddy255.left,	Llid::rcBuddy255.right,	Llid::rcBuddy255.top,	Llid::rcBuddy255.bottom,	Gui::hInstance, Window.hWnd,	L"255",		ID_ST_255,			Static::DEFAULT_STYLES | SS_LEFT,	Static::DEFAULT_EXSTYLES);

	tbOpacity.SetRange(0, 255);
	tbOpacity.SetPosition(Settings::MainWindow::Opacity);
	tbOpacity.SetBodyWindows(st000.hWnd, st255.hWnd);
}
