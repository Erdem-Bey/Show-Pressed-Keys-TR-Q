#pragma once

#include <tuple>
#include <Windows.h>
#include <gdiplus.h>

#include "..\..\Gui\((WindowClasses))\MainWindow.h"
#include "..\..\Gui\((WindowClasses))\Static.h"
#include "..\..\Gui\((WindowClasses))\Edit.h"
#include "..\..\Gui\((WindowClasses))\Button.h"
#include "..\..\Gui\((WindowClasses))\CheckBox.h"
#include "..\..\Gui\((WindowClasses))\Radio.h"
#include "..\..\Gui\((WindowClasses))\ComboBox.h"
#include "..\..\Gui\((WindowClasses))\ListBox.h"
#include "..\..\Gui\((WindowClasses))\ProgressBar.h"
#include "..\..\Gui\((WindowClasses))\TrackBar.h"
#include "..\..\Gui\((WindowClasses))\StatusBar.h"
#include "..\..\Gui\((WindowClasses))\UpDown.h"
#include "..\..\Gui\((WindowClasses))\ListView.h"
#include "..\..\Gui\((WindowClasses))\Timer.h"
#include "..\..\Gui\((WindowClasses))\Utility.h"
#include "..\..\Gui\((WindowClasses))\Tab.h"
#include "..\..\Gui\((WindowClasses))\Hyperlink.h"


class WindowUsage
{
	public:
		WindowUsage();
		~WindowUsage();

		void Create();
		void Destroy();

		void ChangeGuiLanguage();

		friend class Gui;


	private:
		bool		IsCreated;
		MainWindow	Window;
		//HICON		hLogo;

		void CreateChildren();
		static LRESULT CALLBACK MessageProcessor(	_In_	HWND	hwnd,
													_In_	UINT	uMsg,
													_In_	WPARAM	wParam,
													_In_	LPARAM	lParam);
		
		static constexpr int	TEXT_WIDTH		= 760;
		static constexpr int	TEXT_HEIGHT		= 16;
		static constexpr int	TEXT_HEIGHT2	= 2 * TEXT_HEIGHT;
		static constexpr int	ROW_HEIGTH		= 4;
		static constexpr WORD	LINE_ID_START	= 1000;

		std::vector<std::tuple<int, Static, std::wstring>>	Lines;





};

