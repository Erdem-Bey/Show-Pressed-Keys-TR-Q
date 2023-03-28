#pragma once

#include <array>

#include <Windows.h>
#include <CommCtrl.h>
#include <gdiplus.h>

#include "..\..\Gui\((WindowClasses))\MainWindow.h"
#include "..\..\Gui\((WindowClasses))\Static.h"
//#include "..\..\Gui\((WindowClasses))\Edit.h"
#include "..\..\Gui\((WindowClasses))\Button.h"
//#include "..\..\Gui\((WindowClasses))\CheckBox.h"
//#include "..\..\Gui\((WindowClasses))\Radio.h"
//#include "..\..\Gui\((WindowClasses))\ComboBox.h"
//#include "..\..\Gui\((WindowClasses))\ListBox.h"
//#include "..\..\Gui\((WindowClasses))\ProgressBar.h"
#include "..\..\Gui\((WindowClasses))\TrackBar.h"
//#include "..\..\Gui\((WindowClasses))\StatusBar.h"
//#include "..\..\Gui\((WindowClasses))\UpDown.h"
//#include "..\..\Gui\((WindowClasses))\ListView.h"
//#include "..\..\Gui\((WindowClasses))\Timer.h"
//#include "..\..\Gui\((WindowClasses))\Utility.h"
//#include "..\..\Gui\((WindowClasses))\SystemTrayIcon.h"
//#include "..\..\Gui\((WindowClasses))\Calendar.h"

#include "..\Graphics\TextBlock.h"
#include "..\Graphics\LinePath.h"

#include "..\..\KeyboardKey.h"
#include "G_Main_LowLevelInputData.h"


class WindowMain// : public SerialPortListener
{
	public:
		WindowMain();
		~WindowMain();

		void Create();
		void Destroy();
		const HWND & GetHandle() const;
		
		friend class Gui;

		MainWindow Window;


	private:
		static LRESULT CALLBACK WindowMain::LowLevelKeyboardProc(	_In_ int    nCode,
																	_In_ WPARAM wParam,
																	_In_ LPARAM lParam);

		static LRESULT CALLBACK WindowMain::LowLevelMouseProc(		_In_ int    nCode,
																	_In_ WPARAM wParam,
																	_In_ LPARAM lParam);

		const	std::wstring			FontFamily;					//(L"Arial");
		const	Gdiplus::REAL			FontHeight_Large;			//= 16;
		const	Gdiplus::REAL			FontHeight_Small;			//= 10;
		const	Gdiplus::REAL			FrameThickness;				//= 1;
		const	Gdiplus::Color			BackgroundColor;			//= 0xFF'FF'FF'FF;	// AA RR GG BB
		const	Gdiplus::Color			BackgroundColor_Pressed;	//= 0xFF'80'80'FF;	// AA RR GG BB
		const	Gdiplus::Color			TextColor;					//= 0xFF'00'00'00;	// AA RR GG BB
		const	Gdiplus::Color			FrameColor;					//= 0xFF'A0'C0'FF;	// AA RR GG BB

		const	Gdiplus::Pen		*	p_pnMouse;					//(FrameColor,	2 * FrameThickness);
		const	Gdiplus::SolidBrush	*	p_brButtonDown;				//(BackgroundColor_Pressed);
		const	Gdiplus::SolidBrush	*	p_brButtonUp;				//(BackgroundColor);

		PAINTSTRUCT						PaintStruct;
		HDC								hDC;

		// https://stackoverflow.com/a/66238748/245376
		static Gdiplus::Bitmap* LoadImageFromResource(HMODULE hMod, const wchar_t* resid, const wchar_t* restype);

		void LoadLayout_Turkish();
		void UpdateGraphics();
		void Repaint_MouseWheel();

		Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
		ULONG_PTR						gdiplusToken;
		bool							bProcessIsTerminating;
		//Gdiplus::Color				WindowColor;

										static constexpr WORD ID_FIRST		= 10000;
		TrackBar	tbOpacity;			static constexpr WORD ID_TB_Opacity	= ID_FIRST + 1000;
		Button		btClose;			static constexpr WORD ID_BT_Close	= ID_FIRST + 2000;
		Static		stLogo;				static constexpr WORD ID_ST_Logo	= ID_FIRST + 3000;
		Static		st000;				static constexpr WORD ID_ST_000		= ID_FIRST + 4000;
		Static		st255;				static constexpr WORD ID_ST_255		= ID_FIRST + 5000;
		
  		Gdiplus::Image * pLogo;


		
		void CreateChildren();
		void CreateMenu();

		static LRESULT CALLBACK MessageProcessor(	_In_	HWND					hwnd,
													_In_	UINT					uMsg,
													_In_	WPARAM					wParam,
													_In_	LPARAM					lParam);
		
		/*static LRESULT CALLBACK ChildWindowProc(			HWND					hWnd,
															UINT					uMsg,
															WPARAM					wParam,
															LPARAM					lParam,
															UINT_PTR				uIdSubclass,
															DWORD_PTR				dwRefData);*/

		static void DrawAndFillRoundedRectangle(			Gdiplus::Graphics	&	Graphics,
													const	Gdiplus::Pen		&	Pen,
													const	Gdiplus::SolidBrush	&	Brush,
															INT						X_LEFT,
															INT						Y_TOP,
															INT						WIDTH,
															INT						HEIGHT,
															INT						X_RADIUS,
															INT						Y_RADIUS);

		
};

