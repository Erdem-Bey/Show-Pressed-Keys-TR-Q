#define NTDDI_VERSION	NTDDI_WINBLUE
#define WINVER			_WIN32_WINNT_WINBLUE
#define _WIN32_WINNT	_WIN32_WINNT_WINBLUE
#define _WIN32_WINDOWS	_WIN32_WINNT_WINBLUE
#define _WIN32_IE		_WIN32_IE_IE100

#include <iostream>
#include <Windows.h>

#include "Resource.h"
#include "Settings\Settings.h"
#include "Gui\Gui.h"


int APIENTRY wWinMain(	_In_		HINSTANCE	hInstance,
						_In_opt_	HINSTANCE	hPrevInstance,
						_In_		LPWSTR		lpCmdLine,
						_In_		int			nCmdShow)
{
	Settings::LoadDefaults();
	Settings::LoadFromFile();
	
	Gui::hInstance = hInstance;
	UNREFERENCED_PARAMETER(hPrevInstance);
	
	Gui::MainWnd.Create();
	
	MSG Msg;
	while (GetMessageW(&Msg, NULL, 0, 0))
	{
		if (!IsDialogMessageW(Gui::MainWnd.Window.hWnd, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);
		}
	}

	Settings::SaveToFile();
	Gui::MainWnd.Destroy();

	return 0;
}

