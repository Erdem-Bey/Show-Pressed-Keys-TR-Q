#pragma once

#include <array>
#include <Windows.h>
#include <Gdiplus.h>

#include "..\..\Types.h"
#include "..\..\Gui\((WindowClasses))\MainWindow.h"
#include "..\..\Gui\((WindowClasses))\Static.h"
#include "..\..\Gui\((WindowClasses))\Edit.h"
#include "..\..\Gui\((WindowClasses))\Button.h"
#include "..\..\Gui\((WindowClasses))\Radio.h"
#include "..\..\Gui\((WindowClasses))\ListBox.h"

class WindowSettings
{
	public:
		WindowSettings();
		~WindowSettings();

		void Create();
		void Destroy();
		
		void ChangeGuiLanguage();

		friend class Gui;
		friend class Controller_SettingsWindow;

		void ShowPanel_00();
		void ShowPanel_01();
		void HidePanel_00();
		void HidePanel_01();

		void UpdatePanel00_Colors(	const	Gdiplus::Color	&	Button_Start_Outline_Inactive,
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
									const	Gdiplus::Color	&	ProgressBar_Fill_Active_Remaining);

		void Panel00Updated_Colors(			Gdiplus::Color	&	Button_Start_Outline_Inactive,
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
											Gdiplus::Color	&	ProgressBar_Fill_Active_Remaining);

		void UpdatePanel01_Language(const	Languages		&	SelectedLanguage);

		



		MainWindow Window;

	private:
		bool IsCreated;

		void CreateChildren();
		static LRESULT CALLBACK MessageProcessor(	_In_	HWND		hwnd,
													_In_	UINT		uMsg,
													_In_	WPARAM		wParam,
													_In_	LPARAM		lParam);
		static LRESULT CALLBACK ChildWindowProc(			HWND		hWnd,
															UINT		uMsg,
															WPARAM		wParam,
															LPARAM		lParam,
															UINT_PTR	uIdSubclass,
															DWORD_PTR	dwRefData);

		void OptionBox_SelectionChanged();
		void SaveButton_Clicked();

		
		ListBox		ListBx;								static constexpr WORD ID_LISTBOX								= 101;
		Button		bt00Save;							static constexpr WORD ID_BT00_SAVE								= 102;

		// Panel 00
		static constexpr size_t NUM_COLS = 5;
		typedef std::array<Static, NUM_COLS> Static5;
		Static5		st00RGBA;							static constexpr WORD ID_ST00_RGBA								= 1001;
		Static		st00StartOutlineInactive;			static constexpr WORD ID_ST00_START_OUTLINE_INACTIVE			= 1002;
		Static		st00StartOutlineActive;				static constexpr WORD ID_ST00_START_OUTLINE_ACTIVE				= 1003;
		Static		st00StartFillInactive;				static constexpr WORD ID_ST00_START_FILL_INACTIVE				= 1004;
		Static		st00StartFillActive;				static constexpr WORD ID_ST00_START_FILL_ACTIVE					= 1005;
		Static		st00StopOutlineInactive;			static constexpr WORD ID_ST00_STOP_OUTLINE_INACTIVE				= 1006;
		Static		st00StopOutlineActive;				static constexpr WORD ID_ST00_STOP_OUTLINE_ACTIVE				= 1007;
		Static		st00StopFillInactive;				static constexpr WORD ID_ST00_STOP_FILL_INACTIVE				= 1008;
		Static		st00StopFillActive;					static constexpr WORD ID_ST00_STOP_FILL_ACTIVE					= 1009;
		Static		st00ProgressBarOutlineInactive;		static constexpr WORD ID_ST00_PROGRESSBAR_OUTLINE_INACTIVE		= 1010;
		Static		st00ProgressBarOutlineActive;		static constexpr WORD ID_ST00_PROGRESSBAR_OUTLINE_ACTIVE		= 1011;
		Static		st00ProgressBarFillInactive;		static constexpr WORD ID_ST00_PROGRESSBAR_FILL_INACTIVE			= 1012;
		Static		st00ProgressBarFillActivePassed;	static constexpr WORD ID_ST00_PROGRESSBAR_FILL_ACTIVE_PASSED	= 1013;
		Static		st00ProgressBarFillActiveRemaining;	static constexpr WORD ID_ST00_PROGRESSBAR_FILL_ACTIVE_REMAINING	= 1014;
		typedef std::array<Edit, NUM_COLS> Edit5;
		Edit5		ed00StartOutlineInactive;			static constexpr WORD ID_ED00_START_OUTLINE_INACTIVE			= 2010;
		Edit5		ed00StartOutlineActive;				static constexpr WORD ID_ED00_START_OUTLINE_ACTIVE				= 2020;
		Edit5		ed00StartFillInactive;				static constexpr WORD ID_ED00_START_FILL_INACTIVE				= 2030;
		Edit5		ed00StartFillActive;				static constexpr WORD ID_ED00_START_FILL_ACTIVE					= 2040;
		Edit5		ed00StopOutlineInactive;			static constexpr WORD ID_ED00_STOP_OUTLINE_INACTIVE				= 2050;
		Edit5		ed00StopOutlineActive;				static constexpr WORD ID_ED00_STOP_OUTLINE_ACTIVE				= 2060;
		Edit5		ed00StopFillInactive;				static constexpr WORD ID_ED00_STOP_FILL_INACTIVE				= 2070;
		Edit5		ed00StopFillActive;					static constexpr WORD ID_ED00_STOP_FILL_ACTIVE					= 2080;
		Edit5		ed00ProgressBarOutlineInactive;		static constexpr WORD ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE		= 2090;
		Edit5		ed00ProgressBarOutlineActive;		static constexpr WORD ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE		= 2100;
		Edit5		ed00ProgressBarFillInactive;		static constexpr WORD ID_ED00_PROGRESSBAR_FILL_INACTIVE			= 2110;
		Edit5		ed00ProgressBarFillActivePassed;	static constexpr WORD ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED	= 2120;
		Edit5		ed00ProgressBarFillActiveRemaining;	static constexpr WORD ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING	= 2130;
		static void				PaintColorBox	(const Edit5 & ColorGroup);
		static Gdiplus::Color	GetGdiplusColor	(const Edit5 & ColorGroup);

		// Panel 01
		Static		st01Message;						static constexpr WORD ID_ST01_MESSAGE							= 11001;
		Radio		rd01English;						static constexpr WORD ID_RD01_ENGLISH							= 12001;
		Radio		rd01Turkish;						static constexpr WORD ID_RD01_TURKISH							= 12002;
		Radio		rd01Arabic;							static constexpr WORD ID_RD01_ARABIC							= 12003;
		Radio		rd01Japanese;						static constexpr WORD ID_RD01_JAPANESE							= 12004;


		static constexpr int	LISTBOX_WIDTH	= 200;
		static constexpr int	COLUMN_WIDTH	= 10;
		static constexpr int	LINE_HEIGHT		= 16;
		static constexpr int	LABEL_WIDTH		= 180;
		static constexpr int	EDIT_WIDTH		= 40;
		static constexpr size_t	NUM_COLORS		= 4;

		static BYTE GetColor(const Gdiplus::Color & Color, size_t Which);



		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// EVENTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void OnClick_Panel01_Radio_Language(const Languages & SelectedLanguage);


};

