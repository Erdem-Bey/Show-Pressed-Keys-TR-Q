#pragma once

#include <string>
#include <stdint.h>
#include <thread>
#include "BaseWindowClass.h"

class MainWindow : public BaseWindowClass
{
	public:
		static DWORD DEFAULT_STYLES;
		static DWORD DEFAULT_EXSTYLES;

		WNDCLASSEXW WindowClass;
		
		MainWindow();
		MainWindow(	const std::wstring &	WindowClassName,
					const std::wstring &	WindowTitle,
					HINSTANCE				hInstance,
					WNDPROC					MessageProcessor,
					int						x					= CW_USEDEFAULT,
					int						y					= CW_USEDEFAULT,
					int						Width				= 800,
					int						Height				= 600,
					DWORD					Styles				= DEFAULT_STYLES,
					DWORD					ExtendedStyles		= DEFAULT_EXSTYLES,
					DWORD					ClassStyles			= CS_HREDRAW | CS_VREDRAW,
					HICON					hIcon				= NULL,
					HICON					hSmallIcon			= NULL,
					HCURSOR					hCursor				= LoadCursor(NULL, IDC_ARROW),
					HBRUSH					hBackground			= (HBRUSH) (COLOR_WINDOW + 0),
					LPCWSTR					MenuName			= L"",
					HMENU					hMenu				= NULL);
		~MainWindow();

		void Create(const std::wstring &	WindowClassName,
					const std::wstring &	WindowTitle,
					HINSTANCE				hInstance,
					WNDPROC					MessageProcessor,
					int						x					= CW_USEDEFAULT,
					int						y					= CW_USEDEFAULT,
					int						Width				= 800,
					int						Height				= 600,
					DWORD					Styles				= DEFAULT_STYLES,
					DWORD					ExtendedStyles		= DEFAULT_EXSTYLES,
					DWORD					ClassStyles			= CS_HREDRAW | CS_VREDRAW,
					HICON					hIcon				= NULL,
					HICON					hSmallIcon			= NULL,
					HCURSOR					hCursor				= LoadCursor(NULL, IDC_ARROW),
					HBRUSH					hBackground			= (HBRUSH) (COLOR_WINDOW + 0),
					LPCWSTR					MenuName			= L"",
					HMENU					hMenu				= NULL);

		void Destroy();

		inline static RECT MakeRect(LONG Left, LONG Top, LONG Width, LONG Height);

	protected:
		ATOM			Atom;
		std::wstring	ClassName;


};

