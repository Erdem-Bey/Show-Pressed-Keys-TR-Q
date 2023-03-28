#include "G_Settings.h"

#include <Windows.h>
#include <sstream>

#include "..\..\Gui\Gui.h"
#include "..\..\Controller\Controller.h"


void WindowSettings::ShowPanel_00()
{
	st00RGBA[0]									.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"R",										ID_ST00_RGBA + 0,									WS_VISIBLE | WS_CHILD | SS_CENTER,		Static::DEFAULT_EXSTYLES);
	st00RGBA[1]									.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"G",										ID_ST00_RGBA + 1,									WS_VISIBLE | WS_CHILD | SS_CENTER,		Static::DEFAULT_EXSTYLES);
	st00RGBA[2]									.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"B",										ID_ST00_RGBA + 2,									WS_VISIBLE | WS_CHILD | SS_CENTER,		Static::DEFAULT_EXSTYLES);
	st00RGBA[3]									.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"A",										ID_ST00_RGBA + 3,									WS_VISIBLE | WS_CHILD | SS_CENTER,		Static::DEFAULT_EXSTYLES);
	st00RGBA[4]									.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Color",									ID_ST00_RGBA + 4,									WS_VISIBLE | WS_CHILD | SS_CENTER,		Static::DEFAULT_EXSTYLES);

	st00StartOutlineInactive					.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Start Button Outline, Inactive",			ID_ST00_START_OUTLINE_INACTIVE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StartOutlineActive						.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Start Button Outline, Active",			ID_ST00_START_OUTLINE_ACTIVE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StartFillInactive						.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Start Button Fill,    Inactive",			ID_ST00_START_FILL_INACTIVE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StartFillActive							.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Start Button Fill,    Active",			ID_ST00_START_FILL_ACTIVE,							Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StopOutlineInactive						.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Stop  Button Outline, Inactive",			ID_ST00_STOP_OUTLINE_INACTIVE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StopOutlineActive						.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Stop  Button Outline, Active",			ID_ST00_STOP_OUTLINE_ACTIVE,						Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StopFillInactive						.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Stop  Button Fill,    Inactive",			ID_ST00_STOP_FILL_INACTIVE,							Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00StopFillActive							.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Stop  Button Fill,    Active",			ID_ST00_STOP_FILL_ACTIVE,							Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00ProgressBarOutlineInactive				.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Progress Bar Outline, Inactive",			ID_ST00_PROGRESSBAR_OUTLINE_INACTIVE,				Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00ProgressBarOutlineActive				.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Progress Bar Outline, Active",			ID_ST00_PROGRESSBAR_OUTLINE_ACTIVE,					Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00ProgressBarFillInactive					.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Progress Bar Fill,    Inactive",			ID_ST00_PROGRESSBAR_FILL_INACTIVE,					Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00ProgressBarFillActivePassed				.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Progress Bar Fill,    Active, Passed",	ID_ST00_PROGRESSBAR_FILL_ACTIVE_PASSED,				Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);
	st00ProgressBarFillActiveRemaining			.Create(  0,   0,  LABEL_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"Progress Bar Fill,    Active, Remaining",ID_ST00_PROGRESSBAR_FILL_ACTIVE_REMAINING,			Static::DEFAULT_STYLES,					Static::DEFAULT_EXSTYLES);

	constexpr DWORD MY_EDIT_STYLES = WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER;
	for (size_t i=0; i<NUM_COLS-1; i++)	// 0:R, 1:G, 2:B, 3:A
	{
		ed00StartOutlineInactive			[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_OUTLINE_INACTIVE				+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StartOutlineActive				[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_OUTLINE_ACTIVE				+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StartFillInactive				[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_FILL_INACTIVE					+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StartFillActive					[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_FILL_ACTIVE					+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StopOutlineInactive				[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_OUTLINE_INACTIVE				+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StopOutlineActive				[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_OUTLINE_ACTIVE					+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StopFillInactive				[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_FILL_INACTIVE					+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00StopFillActive					[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_FILL_ACTIVE					+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00ProgressBarOutlineInactive		[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE		+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00ProgressBarOutlineActive		[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE			+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00ProgressBarFillInactive			[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_INACTIVE			+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00ProgressBarFillActivePassed		[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED		+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
		ed00ProgressBarFillActiveRemaining	[i]		.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING	+ i,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	}
	constexpr DWORD MY_COLOR_STYLES = WS_VISIBLE | WS_CHILD | ES_READONLY;
	const size_t LAST_COL = NUM_COLS - 1;
	ed00StartOutlineInactive			[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_OUTLINE_INACTIVE				+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StartOutlineActive				[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_OUTLINE_ACTIVE				+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StartFillInactive				[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_FILL_INACTIVE					+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StartFillActive					[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_START_FILL_ACTIVE					+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StopOutlineInactive				[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_OUTLINE_INACTIVE				+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StopOutlineActive				[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_OUTLINE_ACTIVE					+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StopFillInactive				[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_FILL_INACTIVE					+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StopFillActive					[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_STOP_FILL_ACTIVE					+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00ProgressBarOutlineInactive		[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE		+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00ProgressBarOutlineActive		[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE			+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00ProgressBarFillInactive			[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_INACTIVE			+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00ProgressBarFillActivePassed		[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED		+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00ProgressBarFillActiveRemaining	[LAST_COL]	.Create(  0,   0,  EDIT_WIDTH,	LINE_HEIGHT,	Gui::hInstance, Window.hWnd, L"",										ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING	+ LAST_COL,	MY_EDIT_STYLES,							Edit::DEFAULT_EXSTYLES);
	ed00StartOutlineInactive			[LAST_COL]	.Disable();
	ed00StartOutlineActive				[LAST_COL]	.Disable();
	ed00StartFillInactive				[LAST_COL]	.Disable();
	ed00StartFillActive					[LAST_COL]	.Disable();
	ed00StopOutlineInactive				[LAST_COL]	.Disable();
	ed00StopOutlineActive				[LAST_COL]	.Disable();
	ed00StopFillInactive				[LAST_COL]	.Disable();
	ed00StopFillActive					[LAST_COL]	.Disable();
	ed00ProgressBarOutlineInactive		[LAST_COL]	.Disable();
	ed00ProgressBarOutlineActive		[LAST_COL]	.Disable();
	ed00ProgressBarFillInactive			[LAST_COL]	.Disable();
	ed00ProgressBarFillActivePassed		[LAST_COL]	.Disable();
	ed00ProgressBarFillActiveRemaining	[LAST_COL]	.Disable();
	SetWindowSubclass(ed00StartOutlineInactive			[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_START_OUTLINE_INACTIVE,				(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StartOutlineActive			[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_START_OUTLINE_ACTIVE,				(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StartFillInactive				[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_START_FILL_INACTIVE,				(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StartFillActive				[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_START_FILL_ACTIVE,					(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StopOutlineInactive			[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_STOP_OUTLINE_INACTIVE,				(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StopOutlineActive				[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_STOP_OUTLINE_ACTIVE,				(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StopFillInactive				[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_STOP_FILL_INACTIVE,					(DWORD_PTR) NULL);
	SetWindowSubclass(ed00StopFillActive				[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_STOP_FILL_ACTIVE,					(DWORD_PTR) NULL);
	SetWindowSubclass(ed00ProgressBarOutlineInactive	[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE,		(DWORD_PTR) NULL);
	SetWindowSubclass(ed00ProgressBarOutlineActive		[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE,			(DWORD_PTR) NULL);
	SetWindowSubclass(ed00ProgressBarFillInactive		[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_PROGRESSBAR_FILL_INACTIVE,			(DWORD_PTR) NULL);
	SetWindowSubclass(ed00ProgressBarFillActivePassed	[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED,		(DWORD_PTR) NULL);
	SetWindowSubclass(ed00ProgressBarFillActiveRemaining[LAST_COL].hWnd,	ChildWindowProc,	ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING,	(DWORD_PTR) NULL);

	st00RGBA[0]									.Move(LISTBOX_WIDTH + LABEL_WIDTH + 3 * COLUMN_WIDTH, LINE_HEIGHT);
	st00RGBA[1]									.AlignTo(st00RGBA[0],								BaseWindowClass::AS_RIGHT,	BaseWindowClass::AT_BOTTOM,	COLUMN_WIDTH);
	st00RGBA[2]									.AlignTo(st00RGBA[1],								BaseWindowClass::AS_RIGHT,	BaseWindowClass::AT_BOTTOM,	COLUMN_WIDTH);
	st00RGBA[3]									.AlignTo(st00RGBA[2],								BaseWindowClass::AS_RIGHT,	BaseWindowClass::AT_BOTTOM,	COLUMN_WIDTH);
	st00RGBA[4]									.AlignTo(st00RGBA[3],								BaseWindowClass::AS_RIGHT,	BaseWindowClass::AT_BOTTOM,	COLUMN_WIDTH);

	st00StartOutlineInactive					.Move(LISTBOX_WIDTH + 2 * COLUMN_WIDTH, 3 *  LINE_HEIGHT);
	st00StartOutlineActive						.AlignTo(st00StartOutlineInactive,					BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StartFillInactive						.AlignTo(st00StartOutlineActive,					BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StartFillActive							.AlignTo(st00StartFillInactive,						BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StopOutlineInactive						.AlignTo(st00StartFillActive,						BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StopOutlineActive						.AlignTo(st00StopOutlineInactive,					BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StopFillInactive						.AlignTo(st00StopOutlineActive,						BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00StopFillActive							.AlignTo(st00StopFillInactive,						BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00ProgressBarOutlineActive				.AlignTo(st00StopFillActive,						BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00ProgressBarOutlineInactive				.AlignTo(st00ProgressBarOutlineActive,				BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00ProgressBarFillInactive					.AlignTo(st00ProgressBarOutlineInactive,			BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00ProgressBarFillActivePassed				.AlignTo(st00ProgressBarFillInactive,				BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	st00ProgressBarFillActiveRemaining			.AlignTo(st00ProgressBarFillActivePassed,			BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);

	for (size_t i=0; i<NUM_COLS; i++)	// 0:R, 1:G, 2:B, 3:A)
	{
		ed00StartOutlineInactive			[i]	.AlignTo(st00RGBA							[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StartOutlineActive				[i]	.AlignTo(ed00StartOutlineInactive			[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StartFillInactive				[i]	.AlignTo(ed00StartOutlineActive				[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StartFillActive					[i]	.AlignTo(ed00StartFillInactive				[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StopOutlineInactive				[i]	.AlignTo(ed00StartFillActive				[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StopOutlineActive				[i]	.AlignTo(ed00StopOutlineInactive			[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StopFillInactive				[i]	.AlignTo(ed00StopOutlineActive				[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00StopFillActive					[i]	.AlignTo(ed00StopFillInactive				[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00ProgressBarOutlineInactive		[i]	.AlignTo(ed00StopFillActive					[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00ProgressBarOutlineActive		[i]	.AlignTo(ed00ProgressBarOutlineInactive		[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00ProgressBarFillInactive			[i]	.AlignTo(ed00ProgressBarOutlineActive		[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00ProgressBarFillActivePassed		[i]	.AlignTo(ed00ProgressBarFillInactive		[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
		ed00ProgressBarFillActiveRemaining	[i]	.AlignTo(ed00ProgressBarFillActivePassed	[i],	BaseWindowClass::AS_BOTTOM,	BaseWindowClass::AT_LEFT,	LINE_HEIGHT);
	}

	for (size_t i=0; i<NUM_COLS; i++)	// 0:R, 1:G, 2:B, 3:A)
	{
		st00RGBA[i].UpdateFontProperty_Height(16);
		st00RGBA[i].UpdateFontProperty_Weight(600);
	}

	Controller::SettingsWindow::UpdatePanel00_Colors();
}

void WindowSettings::HidePanel_00()
{
	st00StartOutlineActive						.Destroy();
	st00StartFillActive							.Destroy();
	st00StartOutlineInactive					.Destroy();
	st00StartFillInactive						.Destroy();
	st00StopOutlineActive						.Destroy();
	st00StopFillActive							.Destroy();
	st00StopOutlineInactive						.Destroy();
	st00StopFillInactive						.Destroy();
	st00ProgressBarOutlineInactive				.Destroy();
	st00ProgressBarFillInactive					.Destroy();
	st00ProgressBarOutlineActive				.Destroy();
	st00ProgressBarFillActivePassed				.Destroy();
	st00ProgressBarFillActiveRemaining			.Destroy();

	for (size_t i=0; i<NUM_COLS; i++)	// 0:R, 1:G, 2:B, 3:A)
	{
		st00RGBA							[i]	.Destroy();
		ed00StartOutlineInactive			[i]	.Destroy();
		ed00StartOutlineActive				[i]	.Destroy();
		ed00StartFillInactive				[i]	.Destroy();
		ed00StartFillActive					[i]	.Destroy();
		ed00StopOutlineInactive				[i]	.Destroy();
		ed00StopOutlineActive				[i]	.Destroy();
		ed00StopFillInactive				[i]	.Destroy();
		ed00StopFillActive					[i]	.Destroy();
		ed00ProgressBarOutlineInactive		[i]	.Destroy();
		ed00ProgressBarOutlineActive		[i]	.Destroy();
		ed00ProgressBarFillInactive			[i]	.Destroy();
		ed00ProgressBarFillActivePassed		[i]	.Destroy();
		ed00ProgressBarFillActiveRemaining	[i]	.Destroy();
	}
}

void WindowSettings::UpdatePanel00_Colors(	const	Gdiplus::Color	&	Button_Start_Outline_Inactive,
											const	Gdiplus::Color	&	Button_Start_Outline_Active,
											const	Gdiplus::Color	&	Button_Start_Fill_Inactive,
											const	Gdiplus::Color	&	Button_Start_Fill_Active,
											const	Gdiplus::Color	&	Button_Stop_Outline_Inactive,
											const	Gdiplus::Color	&	Button_Stop_Outline_Active,
											const	Gdiplus::Color	&	Button_Stop_Fill_Inactive,
											const	Gdiplus::Color	&	Button_Stop_Fill_Active,
											const	Gdiplus::Color	&	ProgressBar_Outline_Inactive,
											const	Gdiplus::Color	&	ProgressBar_Outline_Active,
											const	Gdiplus::Color	&	ProgressBar_Fill_Inactive,
											const	Gdiplus::Color	&	ProgressBar_Fill_Active_Passed,
											const	Gdiplus::Color	&	ProgressBar_Fill_Active_Remaining)
{
	for (size_t i=0; i<NUM_COLORS; i++)
	{
		ed00StartOutlineInactive			[i].SetContent(GetColor(Button_Start_Outline_Inactive,		i));
		ed00StartOutlineActive				[i].SetContent(GetColor(Button_Start_Outline_Active,		i));
		ed00StartFillInactive				[i].SetContent(GetColor(Button_Start_Fill_Inactive,			i));
		ed00StartFillActive					[i].SetContent(GetColor(Button_Start_Fill_Active,			i));
		ed00StopOutlineInactive				[i].SetContent(GetColor(Button_Stop_Outline_Inactive,		i));
		ed00StopOutlineActive				[i].SetContent(GetColor(Button_Stop_Outline_Active,			i));
		ed00StopFillInactive				[i].SetContent(GetColor(Button_Stop_Fill_Inactive,			i));
		ed00StopFillActive					[i].SetContent(GetColor(Button_Stop_Fill_Active,			i));
		ed00ProgressBarOutlineInactive		[i].SetContent(GetColor(ProgressBar_Outline_Inactive,		i));
		ed00ProgressBarOutlineActive		[i].SetContent(GetColor(ProgressBar_Outline_Active,			i));
		ed00ProgressBarFillInactive			[i].SetContent(GetColor(ProgressBar_Fill_Inactive,			i));
		ed00ProgressBarFillActivePassed		[i].SetContent(GetColor(ProgressBar_Fill_Active_Passed,		i));
		ed00ProgressBarFillActiveRemaining	[i].SetContent(GetColor(ProgressBar_Fill_Active_Remaining,	i));
	}
}

void WindowSettings::Panel00Updated_Colors(	Gdiplus::Color	&	Button_Start_Outline_Inactive,
											Gdiplus::Color	&	Button_Start_Outline_Active,
											Gdiplus::Color	&	Button_Start_Fill_Inactive,
											Gdiplus::Color	&	Button_Start_Fill_Active,
											Gdiplus::Color	&	Button_Stop_Outline_Inactive,
											Gdiplus::Color	&	Button_Stop_Outline_Active,
											Gdiplus::Color	&	Button_Stop_Fill_Inactive,
											Gdiplus::Color	&	Button_Stop_Fill_Active,
											Gdiplus::Color	&	ProgressBar_Outline_Inactive,
											Gdiplus::Color	&	ProgressBar_Outline_Active,
											Gdiplus::Color	&	ProgressBar_Fill_Inactive,
											Gdiplus::Color	&	ProgressBar_Fill_Active_Passed,
											Gdiplus::Color	&	ProgressBar_Fill_Active_Remaining)
{
	std::array<BYTE, NUM_COLORS> Colors_Button_Start_Outline_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_Button_Start_Outline_Active;
	std::array<BYTE, NUM_COLORS> Colors_Button_Start_Fill_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_Button_Start_Fill_Active;
	std::array<BYTE, NUM_COLORS> Colors_Button_Stop_Outline_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_Button_Stop_Outline_Active;
	std::array<BYTE, NUM_COLORS> Colors_Button_Stop_Fill_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_Button_Stop_Fill_Active;
	std::array<BYTE, NUM_COLORS> Colors_ProgressBar_Outline_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_ProgressBar_Outline_Active;
	std::array<BYTE, NUM_COLORS> Colors_ProgressBar_Fill_Inactive;
	std::array<BYTE, NUM_COLORS> Colors_ProgressBar_Fill_Active_Passed;
	std::array<BYTE, NUM_COLORS> Colors_ProgressBar_Fill_Active_Remaining;

	for (size_t i=0; i<NUM_COLORS; i++)
	{
		Colors_Button_Start_Outline_Inactive		[i] = static_cast<BYTE>(ed00StartOutlineInactive			[i].GetContent<unsigned int>());
		Colors_Button_Start_Outline_Active			[i] = static_cast<BYTE>(ed00StartOutlineActive				[i].GetContent<unsigned int>());
		Colors_Button_Start_Fill_Inactive			[i] = static_cast<BYTE>(ed00StartFillInactive				[i].GetContent<unsigned int>());
		Colors_Button_Start_Fill_Active				[i] = static_cast<BYTE>(ed00StartFillActive					[i].GetContent<unsigned int>());
		Colors_Button_Stop_Outline_Inactive			[i] = static_cast<BYTE>(ed00StopOutlineInactive				[i].GetContent<unsigned int>());
		Colors_Button_Stop_Outline_Active			[i] = static_cast<BYTE>(ed00StopOutlineActive				[i].GetContent<unsigned int>());
		Colors_Button_Stop_Fill_Inactive			[i] = static_cast<BYTE>(ed00StopFillInactive				[i].GetContent<unsigned int>());
		Colors_Button_Stop_Fill_Active				[i] = static_cast<BYTE>(ed00StopFillActive					[i].GetContent<unsigned int>());
		Colors_ProgressBar_Outline_Inactive			[i] = static_cast<BYTE>(ed00ProgressBarOutlineInactive		[i].GetContent<unsigned int>());
		Colors_ProgressBar_Outline_Active			[i] = static_cast<BYTE>(ed00ProgressBarOutlineActive		[i].GetContent<unsigned int>());
		Colors_ProgressBar_Fill_Inactive			[i] = static_cast<BYTE>(ed00ProgressBarFillInactive			[i].GetContent<unsigned int>());
		Colors_ProgressBar_Fill_Active_Passed		[i] = static_cast<BYTE>(ed00ProgressBarFillActivePassed		[i].GetContent<unsigned int>());
		Colors_ProgressBar_Fill_Active_Remaining	[i] = static_cast<BYTE>(ed00ProgressBarFillActiveRemaining	[i].GetContent<unsigned int>());/**/
	}

	Button_Start_Outline_Inactive		.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Start_Outline_Inactive	[3],
																			Colors_Button_Start_Outline_Inactive	[0],
																			Colors_Button_Start_Outline_Inactive	[1],
																			Colors_Button_Start_Outline_Inactive	[2]));
	Button_Start_Outline_Active			.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Start_Outline_Active		[3],
																			Colors_Button_Start_Outline_Active		[0],
																			Colors_Button_Start_Outline_Active		[1],
																			Colors_Button_Start_Outline_Active		[2]));
	Button_Start_Fill_Inactive			.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Start_Fill_Inactive		[3],
																			Colors_Button_Start_Fill_Inactive		[0],
																			Colors_Button_Start_Fill_Inactive		[1],
																			Colors_Button_Start_Fill_Inactive		[2]));
	Button_Start_Fill_Active			.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Start_Fill_Active			[3],
																			Colors_Button_Start_Fill_Active			[0],
																			Colors_Button_Start_Fill_Active			[1],
																			Colors_Button_Start_Fill_Active			[2]));
	Button_Stop_Outline_Inactive		.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Stop_Outline_Inactive		[3],
																			Colors_Button_Stop_Outline_Inactive		[0],
																			Colors_Button_Stop_Outline_Inactive		[1],
																			Colors_Button_Stop_Outline_Inactive		[2]));
	Button_Stop_Outline_Active			.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Stop_Outline_Active		[3],
																			Colors_Button_Stop_Outline_Active		[0],
																			Colors_Button_Stop_Outline_Active		[1],
																			Colors_Button_Stop_Outline_Active		[2]));
	Button_Stop_Fill_Inactive			.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Stop_Fill_Inactive		[3],
																			Colors_Button_Stop_Fill_Inactive		[0],
																			Colors_Button_Stop_Fill_Inactive		[1],
																			Colors_Button_Stop_Fill_Inactive		[2]));
	Button_Stop_Fill_Active				.SetValue(Gdiplus::Color::MakeARGB(	Colors_Button_Stop_Fill_Active			[3],
																			Colors_Button_Stop_Fill_Active			[0],
																			Colors_Button_Stop_Fill_Active			[1],
																			Colors_Button_Stop_Fill_Active			[2]));
	ProgressBar_Outline_Inactive		.SetValue(Gdiplus::Color::MakeARGB(	Colors_ProgressBar_Outline_Inactive		[3],
																			Colors_ProgressBar_Outline_Inactive		[0],
																			Colors_ProgressBar_Outline_Inactive		[1],
																			Colors_ProgressBar_Outline_Inactive		[2]));
	ProgressBar_Outline_Active			.SetValue(Gdiplus::Color::MakeARGB(	Colors_ProgressBar_Outline_Active		[3],
																			Colors_ProgressBar_Outline_Active		[0],
																			Colors_ProgressBar_Outline_Active		[1],
																			Colors_ProgressBar_Outline_Active		[2]));
	ProgressBar_Fill_Inactive			.SetValue(Gdiplus::Color::MakeARGB(	Colors_ProgressBar_Fill_Inactive		[3],
																			Colors_ProgressBar_Fill_Inactive		[0],
																			Colors_ProgressBar_Fill_Inactive		[1],
																			Colors_ProgressBar_Fill_Inactive		[2]));
	ProgressBar_Fill_Active_Passed		.SetValue(Gdiplus::Color::MakeARGB(	Colors_ProgressBar_Fill_Active_Passed	[3],
																			Colors_ProgressBar_Fill_Active_Passed	[0],
																			Colors_ProgressBar_Fill_Active_Passed	[1],
																			Colors_ProgressBar_Fill_Active_Passed	[2]));
	ProgressBar_Fill_Active_Remaining	.SetValue(Gdiplus::Color::MakeARGB(	Colors_ProgressBar_Fill_Active_Remaining[3],
																			Colors_ProgressBar_Fill_Active_Remaining[0],
																			Colors_ProgressBar_Fill_Active_Remaining[1],
																			Colors_ProgressBar_Fill_Active_Remaining[2]));
}

BYTE WindowSettings::GetColor(const Gdiplus::Color & Color, size_t Which)
{
	switch (Which)
	{
		case 0:
			return Color.GetR();
			break;
		case 1:
			return Color.GetG();
			break;
		case 2:
			return Color.GetB();
			break;
		case 3:
			return Color.GetA();
			break;
		default:
			return 0;
	}
}
