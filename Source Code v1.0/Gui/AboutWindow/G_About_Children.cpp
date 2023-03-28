#include "G_About.h"

#include <Windows.h>
#include <string>

#include "..\..\Gui\Gui.h"


void WindowAbout::CreateChildren()
{
	Web		.Create(50, 250, 200, 20,				Gui::hInstance, Window.hWnd, L"<A HREF=\"http://www.google.com\">Visit Project Home Page</A>", 9999, Hyperlink::DEFAULT_STYLES | LWS_USEVISUALSTYLE, Hyperlink::DEFAULT_EXSTYLES);
	
	const std::wstring Line00	(L"Technology: Visual C++ Project");
	const std::wstring Line01	(L"Programmer: Erdem Kargýn");
	const std::wstring Line02	(L"");
	const std::wstring Line03	(L"");
	
	Text00	.Create(0, 0, TEXT_WIDTH, TEXT_HEIGHT,	Gui::hInstance, Window.hWnd, Line00.c_str(),	ID_TEXT_00,		Static::DEFAULT_STYLES | SS_CENTER,	Static::DEFAULT_EXSTYLES);
	Text01	.Create(0, 0, TEXT_WIDTH, TEXT_HEIGHT,	Gui::hInstance, Window.hWnd, Line01.c_str(),	ID_TEXT_01,		Static::DEFAULT_STYLES | SS_CENTER,	Static::DEFAULT_EXSTYLES);
	Text02	.Create(0, 0, TEXT_WIDTH, TEXT_HEIGHT,	Gui::hInstance, Window.hWnd, Line02.c_str(),	ID_TEXT_02,		Static::DEFAULT_STYLES | SS_CENTER,	Static::DEFAULT_EXSTYLES);
	Text03	.Create(0, 0, TEXT_WIDTH, TEXT_HEIGHT,	Gui::hInstance, Window.hWnd, Line03.c_str(),	ID_TEXT_03,		Static::DEFAULT_STYLES | SS_CENTER,	Static::DEFAULT_EXSTYLES);
	
	Text00	.AlignTo(Web,		BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	0);
	Text01	.AlignTo(Text00,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	0);
	Text02	.AlignTo(Text01,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	0);
	Text03	.AlignTo(Text02,	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	0);
}

