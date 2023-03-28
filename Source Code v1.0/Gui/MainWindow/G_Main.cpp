#include "G_Main.h"

#include <Windows.h>

#include "..\..\Gui\Gui.h"
#include "..\..\Resource.h"
#include "..\..\Settings\Settings.h"
#include "..\..\Gui\((WindowClasses))\Utility.h"



WindowMain::WindowMain()
	:	gdiplusStartupInput		()
	,	gdiplusToken			()
	,	bProcessIsTerminating	(false)
	,	pLogo					(nullptr)
	,	FontFamily				(L"Arial")
	,	FontHeight_Large		(16)
	,	FontHeight_Small		(10)
	,	FrameThickness			(1)
	,	BackgroundColor			(0xFF'FF'FF'FF)		// AA RR GG BB
	,	BackgroundColor_Pressed	(0xFF'80'80'FF)		// AA RR GG BB
	,	TextColor				(0xFF'00'00'00)		// AA RR GG BB
	,	FrameColor				(0xFF'A0'C0'FF)		// AA RR GG BB
	,	p_pnMouse				(nullptr)
	,	p_brButtonDown			(nullptr)
	,	p_brButtonUp			(nullptr)
	,	PaintStruct				()
	,	hDC						()
{
}

WindowMain::~WindowMain()
{
	Destroy();
}

void WindowMain::Create()
{
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	p_pnMouse		= new Gdiplus::Pen			(FrameColor,	2 * FrameThickness);
	p_brButtonDown	= new Gdiplus::SolidBrush	(BackgroundColor_Pressed);
	p_brButtonUp	= new Gdiplus::SolidBrush	(BackgroundColor);

	//this->CreateMenu();

	Window.Create(	/*const std::wstring &	WindowClassName*/	Settings::MainWindow::MAINWND_CLASS,
					/*const std::wstring &	WindowTitle*/		Settings_MainWindow::MAINWND_TITLE,
					/*HINSTANCE				hInstance*/			Gui::hInstance,
																WindowMain::MessageProcessor,
					/*int					x*/					Settings::MainWindow::MainWnd_X,
					/*int					y*/					Settings::MainWindow::MainWnd_Y,
					/*int					Width*/				Settings::MainWindow::MainWnd_W,
					/*int					Height*/			Settings::MainWindow::MainWnd_H,
					/*DWORD					Styles*/			Settings::MainWindow::MAINWND_STYLES,
					/*DWORD					ExtendedStyles*/	Settings::MainWindow::MAINWND_EXSTYLES,
					/*DWORD					ClassStyles*/		Settings::MainWindow::MAINWND_CLASS_STYLES,
					/*HICON					hIcon*/				LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_MAIN_BIG)),
					/*HICON					hSmallIcon*/		LoadIconW(Gui::hInstance, MAKEINTRESOURCEW(ICON_WINDOW_MAIN_SMALL)),
					/*HCURSOR				hCursor*/			LoadCursor(NULL, IDC_ARROW),
					/*HBRUSH				hBackground*/		Settings::MainWindow::MAINWND_BACKGROUND,	//(HBRUSH) COLOR_WINDOW,
					/*LPCWSTR				MenuName*/			NULL,
					/*HMENU					hMenu*/				(HMENU) NULL); // this->hMenuBar);

	//hDC	= BeginPaint(Window.hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
	//hDC	= GetDC(Window.hWnd);						// So, I get the correct "hDC" like this.
	//pGraphics = Gdiplus::Graphics::FromHDC(hDC);

	Llid::pbmCatWheel = LoadImageFromResource(Gui::hInstance, MAKEINTRESOURCE(PICTURE_CAT_WHEEL), L"PNG");
	Llid::pbmMouseWheel = LoadImageFromResource(Gui::hInstance, MAKEINTRESOURCE(PICTURE_MOUSE_WHEEL), L"PNG");
	pLogo = Gdiplus::Bitmap::FromFile(L"Graphics\\Logo.png", false);

	CreateChildren();

	SetLayeredWindowAttributes(		/*[in] HWND     hwnd	*/	Window.hWnd,
									/*[in] COLORREF crKey	*/	RGB(0,0,0),
									/*[in] BYTE     bAlpha	*/	200,
									/*[in] DWORD    dwFlags	*/	LWA_ALPHA);

	SetWindowLong(Window.hWnd, GWL_STYLE, Settings::MainWindow::MAINWND_STYLES);
	SetWindowPos(Window.hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(Window.hWnd, SW_SHOW);
    UpdateWindow(Window.hWnd);

	//if (false)
	{
		RECT rect;
		GetWindowRect(Window.hWnd, &rect);
		rect.left	= Settings::MainWindow::MainWnd_X;
		rect.top	= Settings::MainWindow::MainWnd_Y;
		rect.right	= Settings::MainWindow::MainWnd_X + Settings::MainWindow::MainWnd_W;
		rect.bottom	= Settings::MainWindow::MainWnd_Y + Settings::MainWindow::MainWnd_H;
		MoveWindow(Window.hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, false);
		ShowWindow(Window.hWnd, 1);
		UpdateWindow(Window.hWnd);
	}

	hDC	= BeginPaint(Window.hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
	hDC	= GetDC(Window.hWnd);						// So, I get the correct "hDC" like this.

	if (false)
	{
		LOGBRUSH lbr = { 0 };
		const HBRUSH hb = GetSysColorBrush(reinterpret_cast<int>(Settings::MainWindow::MAINWND_BACKGROUND));
		volatile int ret = GetObjectW(hb, sizeof(lbr), &lbr);
		const COLORREF lbColor = lbr.lbColor;
		//WindowColor.SetFromCOLORREF(lbColor);
		/*RGBQUAD rgbq = {0};
		rgbq.rgbBlue = GetBValue(lbColor);
		rgbq.rgbGreen = GetGValue(lbColor);
		rgbq.rgbRed = GetRValue(lbColor);
		rgbq.rgbReserved = 0;*/
	}
	
	Llid::pWindow = this;
	/*HHOOK*/ Llid::hHookK = SetWindowsHookExW(	/*[in] int       idHook		*/	WH_KEYBOARD_LL,
												/*[in] HOOKPROC  lpfn		*/	LowLevelKeyboardProc,
												/*[in] HINSTANCE hmod		*/	NULL,
												/*[in] DWORD     dwThreadId	*/	0);
	/*HHOOK*/ Llid::hHookM = SetWindowsHookExW(	/*[in] int       idHook		*/	WH_MOUSE_LL,
												/*[in] HOOKPROC  lpfn		*/	LowLevelMouseProc,
												/*[in] HINSTANCE hmod		*/	NULL,
												/*[in] DWORD     dwThreadId	*/	0);
}

void WindowMain::Destroy()
{
	EndPaint(Window.hWnd, &PaintStruct);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	//delete Llid::pbmMouseWheel;
	//TrayIcon.Delete();
}

const HWND & WindowMain::GetHandle() const
{
	return Window.hWnd;
}

// https://stackoverflow.com/a/66238748/245376
Gdiplus::Bitmap * WindowMain::LoadImageFromResource(HMODULE hMod, const wchar_t* resid, const wchar_t* restype)
{
    IStream* pStream = nullptr;
    Gdiplus::Bitmap* pBmp = nullptr;
    HGLOBAL hGlobal = nullptr;

    HRSRC hrsrc = FindResourceW(hMod, resid, restype);     // get the handle to the resource
    if (hrsrc)
    {
        DWORD dwResourceSize = SizeofResource(hMod, hrsrc);
        if (dwResourceSize > 0)
        {
            HGLOBAL hGlobalResource = LoadResource(hMod, hrsrc); // load it
            if (hGlobalResource)
            {
                void* imagebytes = LockResource(hGlobalResource); // get a pointer to the file bytes

                // copy image bytes into a real hglobal memory handle
                hGlobal = ::GlobalAlloc(GHND, dwResourceSize);
                if (hGlobal)
                {
                    void* pBuffer = ::GlobalLock(hGlobal);
                    if (pBuffer)
                    {
                        memcpy(pBuffer, imagebytes, dwResourceSize);
                        HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
                        if (SUCCEEDED(hr))
                        {
                            // pStream now owns the global handle and will invoke GlobalFree on release
                            hGlobal = nullptr;
                            pBmp = new Gdiplus::Bitmap(pStream);
                        }
                    }
                }
            }
        }
    }

    if (pStream)
    {
        pStream->Release();
        pStream = nullptr;
    }

    if (hGlobal)
    {
        GlobalFree(hGlobal);
        hGlobal = nullptr;
    }

    return pBmp;
}
