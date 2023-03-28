#include "MainWindow.h"
#include "MainWindow.h"


DWORD MainWindow::DEFAULT_STYLES	= WS_CAPTION
									| WS_MINIMIZEBOX
									| WS_SYSMENU
									| WS_TABSTOP
									| WS_GROUP
									| WS_VISIBLE;
DWORD MainWindow::DEFAULT_EXSTYLES	= WS_EX_ACCEPTFILES
									| WS_EX_CONTROLPARENT
									| WS_EX_LEFT
									| WS_EX_LTRREADING;

MainWindow::MainWindow()
{
}

MainWindow::MainWindow( const std::wstring &	WindowClassName,
						const std::wstring &	WindowTitle,
						HINSTANCE				hInstance,
						WNDPROC					MessageProcessor,
						int						x					/*= CW_USEDEFAULT*/,
						int						y					/*= CW_USEDEFAULT*/,
						int						Width				/*= 800*/,
						int						Height				/*= 600*/,
						DWORD					Styles				/*= DEFAULT_STYLES*/,
						DWORD					ExtendedStyles		/*= DEFAULT_EXSTYLES*/,
						DWORD					ClassStyles			/*= CS_HREDRAW | CS_VREDRAW*/,
						HICON					hIcon				/*= NULL*/,
						HICON					hSmallIcon			/*= NULL*/,
						HCURSOR					hCursor				/*= LoadCursor(NULL, IDC_ARROW)*/,
						HBRUSH					hBackground			/*= (COLOR_WINDOW + 0)*/,
						LPCWSTR					MenuName			/*= L""*/,
						HMENU					hMenu				/*= NULL*/)
	: BaseWindowClass()
{
	Create( WindowClassName,
			WindowTitle,
			hInstance,
			MessageProcessor,
			x,
			y,
			Width,
			Height,
			Styles,
			ExtendedStyles,
			ClassStyles,
			hIcon,
			hSmallIcon,
			hCursor,
			hBackground,
			MenuName,
			hMenu);
}

MainWindow::~MainWindow()
{
	Destroy();
}

void MainWindow::Create(const std::wstring &		WindowClassName,
						const std::wstring &		WindowTitle,
						HINSTANCE					hInstance,
						WNDPROC						MessageProcessor,
						int							x					/*= CW_USEDEFAULT*/,
						int							y					/*= CW_USEDEFAULT*/,
						int							Width				/*= 800*/,
						int							Height				/*= 600*/,
						DWORD						Styles				/*= DEFAULT_STYLES*/,
						DWORD						ExtendedStyles		/*= DEFAULT_EXSTYLES*/,
						DWORD						ClassStyles			/*= CS_HREDRAW | CS_VREDRAW*/,
						HICON						hIcon				/*= NULL*/,
						HICON						hSmallIcon			/*= NULL*/,
						HCURSOR						hCursor				/*= LoadCursor(NULL, IDC_ARROW)*/,
						HBRUSH						hBackground			/*= (HBRUSH) (COLOR_WINDOW + 0)*/,
						LPCWSTR						MenuName			/*= L""*/,
						HMENU						hMenu				/*= NULL*/)
{
	ClassName = WindowClassName;
	WindowClass.cbSize			= sizeof(WNDCLASSEXW);
	WindowClass.style			= ClassStyles;
	WindowClass.lpfnWndProc		= MessageProcessor;
	WindowClass.cbClsExtra		= 0;
	WindowClass.cbWndExtra		= 0;
	WindowClass.hInstance		= hInstance;
	WindowClass.hIcon			= (HICON) hIcon;
	WindowClass.hCursor			= hCursor;
	WindowClass.hbrBackground	= (HBRUSH) hBackground;
	WindowClass.lpszMenuName	= MenuName;
	WindowClass.lpszClassName	= ClassName.c_str();
	WindowClass.hIconSm			= (HICON) hSmallIcon;
	Atom = RegisterClassExW(&WindowClass);
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	ClassName.c_str(),
							/*_In_opt_	LPCTSTR*/	WindowTitle.c_str(),
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		x,
							/*_In_		int*/		y,
							/*_In_		int*/		Width,
							/*_In_		int*/		Height,
							/*_In_opt_	HWND*/		HWND_DESKTOP,
							/*_In_opt_	HMENU*/		hMenu,
							/*_In_opt_	HINSTANCE*/	WindowClass.hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	RECT Rect;
	GetWindowRect(hWnd, &Rect);
	StorePositionAndSize(Rect.left, Rect.top, Width, Height);
}

void MainWindow::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
	UnregisterClassW(ClassName.c_str(), WindowClass.hInstance);
}

RECT MainWindow::MakeRect(LONG Left, LONG Top, LONG Width, LONG Height)
{
	RECT Rect;
	//SetRect(&Rect, Left, Top, Width, Height);
	Rect.left		= Left;
	Rect.top		= Top;
	Rect.right		= Width;
	Rect.bottom		= Height;
	return Rect;
}
