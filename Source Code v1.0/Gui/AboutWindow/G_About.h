#pragma once

#include <Windows.h>
#include <gdiplus.h>

#include "..\..\Gui\((WindowClasses))\MainWindow.h"
#include "..\..\Gui\((WindowClasses))\Static.h"
#include "..\..\Gui\((WindowClasses))\Edit.h"
#include "..\..\Gui\((WindowClasses))\Button.h"
#include "..\..\Gui\((WindowClasses))\Hyperlink.h"


class WindowAbout
{
	public:
		WindowAbout();
		~WindowAbout();

		void Create();
		void Destroy();
		
		void ChangeGuiLanguage();

		friend class Gui;


	private:
		bool IsCreated;
		MainWindow Window;
		//HICON hLogo;

		void CreateChildren();
		static LRESULT CALLBACK MessageProcessor(	_In_	HWND	hwnd,
													_In_	UINT	uMsg,
													_In_	WPARAM	wParam,
													_In_	LPARAM	lParam);

		static constexpr int	TEXT_HEIGHT		= 20;
		static constexpr int	TEXT_WIDTH		= 200;

		Static		Image;	static const WORD	ID_IMAGE		= 3000;
		
		Hyperlink	Web;	static const WORD	ID_WEB			= 4000;

		Static		Text00;	static const WORD	ID_TEXT_00		= 5000;
		Static		Text01;	static const WORD	ID_TEXT_01		= 5001;
		Static		Text02;	static const WORD	ID_TEXT_02		= 5002;
		Static		Text03;	static const WORD	ID_TEXT_03		= 5003;

		Button		Close;	static const WORD	ID_BUTTON		= 6000;





};

