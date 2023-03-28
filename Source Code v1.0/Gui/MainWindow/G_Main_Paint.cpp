#include "G_Main.h"

#include "..\..\Settings\Settings.h"
#include "..\..\Gui\Gui.h"
#include "..\Graphics\TextBlock.h"
#include "G_Main_LowLevelInputData.h"

#include <mutex>
#include <cmath>
#include <algorithm>

/*
// Color order: 0xAARRGGBB									AA RR GG BB
const Gdiplus::Color WindowMain::Color_Text				= 0xFF'00'00'00;
const Gdiplus::Color WindowMain::Color_Frame			= 0xFF'00'00'00;
const Gdiplus::Color WindowMain::Color_Line_LogicHigh	= 0xFF'00'BB'00;
const Gdiplus::Color WindowMain::Color_Line_LogicLow	= 0xFF'FF'00'00;
const Gdiplus::Color WindowMain::Color_Line_Healthy		= 0xFF'00'BB'00;
const Gdiplus::Color WindowMain::Color_Line_Failed		= 0xFF'FF'00'00;
const Gdiplus::Color WindowMain::Color_Line_Unknown		= 0xFF'00'00'00;
const Gdiplus::Color WindowMain::Color_Gpio_LogicHigh	= 0xFF'00'FF'00;
const Gdiplus::Color WindowMain::Color_Gpio_LogicLow	= 0xFF'FF'00'00;
const Gdiplus::Color WindowMain::Color_Gpio_Unknown		= 0xFF'FF'A0'00;
const Gdiplus::Color WindowMain::Color_Block_Healthy	= 0xFF'00'40'FF;
const Gdiplus::Color WindowMain::Color_Block_Failed		= 0xFF'FF'40'00;
const Gdiplus::Color WindowMain::Color_Block_Unknown	= 0xFF'FF'A0'00;
const std::wstring WindowMain::FontFamily				= L"Arial";
*/

void WindowMain::Repaint_MouseWheel()
{
	if (bProcessIsTerminating)
	{
		return;
	}

	/// 
	/// MOUSE WHEEL
	/// 

	RECT rect;
	float windowWidth = static_cast<float>(Settings::MainWindow::MainWnd_W);
	float windowHeight = static_cast<float>(Settings::MainWindow::MainWnd_H);
	if(GetWindowRect(Window.hWnd, &rect))
	{
		windowWidth = rect.right - rect.left - 16;
		windowHeight = rect.bottom - rect.top - 9;
	}
	const float xScale = windowWidth / static_cast<float>(Settings::MainWindow::MAINWND_NOMINAL_W);
	const float yScale = windowHeight / static_cast<float>(Settings::MainWindow::MAINWND_NOMINAL_H);

	Gdiplus::Graphics Graphics(hDC);
	
	const Gdiplus::REAL X = 220;
	//const Gdiplus::REAL Y = 300;

	{
		Gdiplus::RectF rectImage{xScale * X, yScale * 300, xScale * 225, yScale * 225};
		Graphics.DrawImage(Llid::pbmMouseWheel, rectImage);

		if (Llid::nWheelDelta != 0)
		{
			Gdiplus::GraphicsPath ArrowWheel;

			if (Llid::nWheelDelta > 0)
			{
				ArrowWheel.AddBezier(	xScale * (X + 20),	yScale * 500,
										xScale * (X + 20),	yScale * 440,
										xScale * (X + 60),	yScale * 340,
										xScale * (X + 140),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 140),	yScale * 320,
										xScale * (X + 120),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 120),	yScale * 320,
										xScale * (X + 140),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 140),	yScale * 320,
										xScale * (X + 125),	yScale * 335);
			}
			else if (Llid::nWheelDelta < 0)
			{
				ArrowWheel.AddBezier(	xScale * (X + 140),	yScale * 320,
										xScale * (X + 60),	yScale * 340,
										xScale * (X + 20),	yScale * 440,
										xScale * (X + 20),	yScale * 500);
				ArrowWheel.AddLine(		xScale * (X + 20),	yScale * 500,
										xScale * (X + 15),	yScale * 480);
				ArrowWheel.AddLine(		xScale * (X + 15),	yScale * 480,
										xScale * (X + 20),	yScale * 500);
				ArrowWheel.AddLine(		xScale * (X + 20),	yScale * 500,
										xScale * (X + 30),	yScale * 480);
			}

			/*if (Llid::nWheelDelta > 0)
			{
				//Buffer.DrawPath(&pnErase, &ArrowWheelDw);
				Buffer.DrawPath(&pnMouse, &ArrowWheelUp);
			}
			else if (Llid::nWheelDelta < 0)
			{
				//Buffer.DrawPath(&pnErase, &ArrowWheelUp);
				Buffer.DrawPath(&pnMouse, &ArrowWheelDw);
			}*/

			Graphics.DrawPath(p_pnMouse, &ArrowWheel);

			Llid::nWheelDelta = 0;
		}
	}
}

void WindowMain::UpdateGraphics()
{
	
	if (bProcessIsTerminating)
	{
		return;
	}
	
	std::mutex Mutex;
	std::lock_guard<std::mutex> LockGuard(Mutex);
	
	if (Window.hWnd == NULL)
	{
		return;
	}
	
	RECT rect;
	float windowWidth = static_cast<float>(Settings::MainWindow::MainWnd_W);
	float windowHeight = static_cast<float>(Settings::MainWindow::MainWnd_H);
	if(GetWindowRect(Window.hWnd, &rect))
	{
		windowWidth = rect.right - rect.left - 16;
		windowHeight = rect.bottom - rect.top - 9;
	}
	const float xScale = windowWidth / static_cast<float>(Settings::MainWindow::MAINWND_NOMINAL_W);
	const float yScale = windowHeight / static_cast<float>(Settings::MainWindow::MAINWND_NOMINAL_H);
	

	//PAINTSTRUCT PaintStruct;
	//HDC hDC	= BeginPaint(Window.hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
	//hDC	= GetDC(Window.hWnd);							// So, I get the correct "hDC" like this.

  	Gdiplus::Bitmap Bmp(windowWidth, windowHeight);
	Gdiplus::Graphics Graphics(hDC);
	Gdiplus::Graphics Buffer(&Bmp);
	
	//const COLORREF color = GetPixel(hDC, xScale * 15, yScale * 150);
	//WindowColor.SetFromCOLORREF(color);

	//Graphics	.Clear(Gdiplus::Color::White);
	//Graphics	.Clear(WindowColor);
	Buffer	.Clear(Gdiplus::Color::White);
	//Buffer	.Clear(WindowColor);

	/*const		std::wstring	FontFamily(L"Arial");
	constexpr	Gdiplus::REAL	FontHeight_Large		= 16;
	constexpr	Gdiplus::REAL	FontHeight_Small		= 10;
	constexpr	Gdiplus::REAL	FrameThickness			= 1;
	const		Gdiplus::Color	BackgroundColor			= 0xFF'FF'FF'FF;	// AA RR GG BB
	const		Gdiplus::Color	BackgroundColor_Pressed	= 0xFF'80'80'FF;	// AA RR GG BB
	const		Gdiplus::Color	TextColor				= 0xFF'00'00'00;	// AA RR GG BB
	const		Gdiplus::Color	FrameColor				= 0xFF'A0'C0'FF;	// AA RR GG BB*/
	
	for (size_t i=0; i<Llid::KeysLarge.size(); i++)
	{
		Llid::KeysLarge[i].Graphics.pGraphics		= &Buffer;
		Llid::KeysLarge[i].Graphics.X				= xScale * Llid::KeysLarge[i].Location.x;
		Llid::KeysLarge[i].Graphics.Y				= yScale * Llid::KeysLarge[i].Location.y;
		Llid::KeysLarge[i].Graphics.Width			= xScale * Llid::KeysLarge[i].Size.w;
		Llid::KeysLarge[i].Graphics.Height			= yScale * Llid::KeysLarge[i].Size.h;
		if (Llid::KeysLarge[i].Pressed)
		{
		Llid::KeysLarge[i].Graphics.BackgroundColor	= BackgroundColor_Pressed;
		}
		else
		{
		Llid::KeysLarge[i].Graphics.BackgroundColor	= BackgroundColor;
		}
		Llid::KeysLarge[i].Graphics.TextColor		= TextColor;
		Llid::KeysLarge[i].Graphics.FrameThickness	= FrameThickness;
		Llid::KeysLarge[i].Graphics.FrameColor		= FrameColor;
		Llid::KeysLarge[i].Graphics.FontHeight		= min(xScale, yScale) * FontHeight_Large;
		Llid::KeysLarge[i].Graphics.FontFamily		= FontFamily;
		Llid::KeysLarge[i].Graphics.Text			= Llid::KeysLarge[i].Name;
		Llid::KeysLarge[i].Graphics.Update();
	}
	
	for (size_t i=0; i<Llid::KeysSmall.size(); i++)
	{
		Llid::KeysSmall[i].Graphics.pGraphics		= &Buffer;
		Llid::KeysSmall[i].Graphics.X				= xScale * Llid::KeysSmall[i].Location.x;
		Llid::KeysSmall[i].Graphics.Y				= yScale * Llid::KeysSmall[i].Location.y;
		Llid::KeysSmall[i].Graphics.Width			= xScale * Llid::KeysSmall[i].Size.w;
		Llid::KeysSmall[i].Graphics.Height			= yScale * Llid::KeysSmall[i].Size.h;
		if (Llid::KeysSmall[i].Pressed)
		{
		Llid::KeysSmall[i].Graphics.BackgroundColor	= BackgroundColor_Pressed;
		}
		else
		{
		Llid::KeysSmall[i].Graphics.BackgroundColor	= BackgroundColor;
		}
		Llid::KeysSmall[i].Graphics.TextColor		= TextColor;
		Llid::KeysSmall[i].Graphics.FrameThickness	= FrameThickness;
		Llid::KeysSmall[i].Graphics.FrameColor		= FrameColor;
		Llid::KeysSmall[i].Graphics.FontHeight		= min(xScale, yScale) * FontHeight_Small;
		Llid::KeysSmall[i].Graphics.FontFamily		= FontFamily;
		Llid::KeysSmall[i].Graphics.Text			= Llid::KeysSmall[i].Name;
		Llid::KeysSmall[i].Graphics.Update();
	}
	
	
	/*const	Gdiplus::Pen pnMouse(FrameColor,	2 * FrameThickness);
	//const	Gdiplus::Pen pnErase(WindowColor,	2 * FrameThickness);
	const	Gdiplus::SolidBrush	brButtonDown	(BackgroundColor_Pressed);
	const	Gdiplus::SolidBrush	brButtonUp		(BackgroundColor);*/
	
	const	Gdiplus::Pen		&	pnMouse			= *p_pnMouse;
	const	Gdiplus::SolidBrush	&	brButtonDown	= *p_brButtonDown;
	const	Gdiplus::SolidBrush	&	brButtonUp		= *p_brButtonUp;


	/// 
	/// ENTER KEY
	/// 
	
	{
		Gdiplus::Pen EnterPen(FrameColor, FrameThickness);
		std::vector<Gdiplus::PointF> ScaledVertices_Enter;
		for (size_t i=0; i<Llid::EnterVertices.size(); i++)
		{
			ScaledVertices_Enter.push_back({xScale * Llid::EnterVertices[i].X, yScale * Llid::EnterVertices[i].Y});
		}
		if (Llid::EnterPressed == true)
		{
			Buffer.FillPolygon(&brButtonDown, ScaledVertices_Enter.data(), ScaledVertices_Enter.size(), Gdiplus::FillMode::FillModeAlternate);
		}
		else
		{
			Buffer.FillPolygon(&brButtonUp, ScaledVertices_Enter.data(), ScaledVertices_Enter.size(), Gdiplus::FillMode::FillModeAlternate);
		}
		Buffer.DrawPolygon(&EnterPen, ScaledVertices_Enter.data(), ScaledVertices_Enter.size());
	}
	
	
	/// 
	/// ENTER KEY ARROWS
	/// 
	
	{
		Gdiplus::Pen EnterArrowPen(Gdiplus::Color::Black, FrameThickness);
		std::vector<Gdiplus::PointF> ScaledVertices_EnterArrow;
		for (size_t i=0; i<Llid::EnterArrowVertices.size(); i++)
		{
			ScaledVertices_EnterArrow.push_back({xScale * Llid::EnterArrowVertices[i].X, yScale * Llid::EnterArrowVertices[i].Y});
		}
		Buffer.DrawLines(&EnterArrowPen, ScaledVertices_EnterArrow.data(), ScaledVertices_EnterArrow.size());
	}

	
	/// 
	/// NUMBER LOCK, SCROLL LOCK, PAUSE
	/// 
	
	{
		TextBlock NumBlock, CapsBlock, PauseBlock;
		const Gdiplus::Color Color_Frame	= 0xFF'00'00'00;
		const Gdiplus::Color Background_On	= 0xFF'EB'98'34;
		const Gdiplus::Color Background_Off	= 0xFF'D0'F7'F3;
		const Gdiplus::Color TextColor_On	= 0xFF'EB'98'34;
		const Gdiplus::Color TextColor_Off	= 0xFF'00'00'00;
		const Gdiplus::REAL TextHeight		= 12;
		const Gdiplus::REAL LEFT_X			= 865;
		const Gdiplus::REAL TOP_Y			= 25;
		const Gdiplus::REAL WIDTH			= 20;
		const Gdiplus::REAL HEIGHT			= 20;
		const Gdiplus::REAL SPACE			= 30;

		NumBlock.pGraphics			= &Buffer;
		NumBlock.X					= xScale * LEFT_X;
		NumBlock.Y					= yScale * TOP_Y;
		NumBlock.Width				= xScale * WIDTH;
		NumBlock.Height				= yScale * HEIGHT;
		if (Llid::LedNumber)
		{
		NumBlock.BackgroundColor	= Background_On;
		NumBlock.TextColor			= TextColor_On;
		}
		else
		{
		NumBlock.BackgroundColor	= Background_Off;
		NumBlock.TextColor			= TextColor_Off;
		}
		NumBlock.FrameThickness		= FrameThickness;
		NumBlock.FrameColor			= Color_Frame;
		NumBlock.FontHeight			= min(xScale, yScale) * TextHeight;
		NumBlock.FontFamily			= FontFamily;
		NumBlock.Text				= L"1";
		NumBlock.Update();

		CapsBlock.pGraphics			= &Buffer;
		CapsBlock.X					= xScale * (LEFT_X + SPACE);
		CapsBlock.Y					= yScale * TOP_Y;
		CapsBlock.Width				= xScale * WIDTH;
		CapsBlock.Height			= yScale * HEIGHT;
		if (Llid::LedCaps)
		{
		CapsBlock.BackgroundColor	= Background_On;
		CapsBlock.TextColor			= TextColor_On;
		}
		else
		{
		CapsBlock.BackgroundColor	= Background_Off;
		CapsBlock.TextColor			= TextColor_Off;
		}
		CapsBlock.FrameThickness	= FrameThickness;
		CapsBlock.FrameColor		= Color_Frame;
		CapsBlock.FontHeight		= min(xScale, yScale) * TextHeight;
		CapsBlock.FontFamily		= FontFamily;
		CapsBlock.Text				= L"A";
		CapsBlock.Update();

		PauseBlock.pGraphics		= &Buffer;
		PauseBlock.X				= xScale * (LEFT_X + 2 * SPACE);
		PauseBlock.Y				= yScale * TOP_Y;
		PauseBlock.Width			= xScale * WIDTH;
		PauseBlock.Height			= yScale * HEIGHT;
		if (Llid::LedScroll)
		{
		PauseBlock.BackgroundColor	= Background_On;
		PauseBlock.TextColor		= TextColor_On;
		}
		else
		{
		PauseBlock.BackgroundColor	= Background_Off;
		PauseBlock.TextColor		= TextColor_Off;
		}
		PauseBlock.FrameThickness	= FrameThickness;
		PauseBlock.FrameColor		= Color_Frame;
		PauseBlock.FontHeight		= min(xScale, yScale) * TextHeight;
		PauseBlock.FontFamily		= FontFamily;
		PauseBlock.Text				= L"⤓";
		PauseBlock.Update();
	}


	/// 
	/// MOUSE BODY DRAWING
	/// 
	
	{
		const Gdiplus::SolidBrush brMouseBody(Gdiplus::Color::Gray);
		Gdiplus::GraphicsPath MouseBody;
		MouseBody.AddArc(xScale * 50, yScale * 300,	// Ellipse rectangle top-left corner
						xScale * 150, yScale * 100,	// Ellipse radii
						0, -180);
		MouseBody.AddArc(xScale * 50, yScale * 200,	// Ellipse rectangle top-left corner
						xScale * 150, yScale * 300,	// Ellipse radii
						180, -180);
		Buffer.DrawPath(&pnMouse, &MouseBody);
		Buffer.FillPath(&brMouseBody, &MouseBody);
	}
	
	
	/// 
	/// MOUSE BUTTON DRAWINGS
	/// 
	
	{
		Gdiplus::REAL x1, y1, x2, y2;
		constexpr Gdiplus::REAL PI = 3.1415926536f;
		constexpr Gdiplus::REAL BUTTON_ARC = 56;
		constexpr Gdiplus::REAL BUTTON_ARC_RAD = PI * 56.0f / 180.0f;
		constexpr Gdiplus::REAL RX = 110.0f / 2.0f;
		constexpr Gdiplus::REAL RY = 60.0f / 2.0f;
		constexpr Gdiplus::REAL EX = 70;
		constexpr Gdiplus::REAL EY = 320;
		constexpr Gdiplus::REAL BUTTON_BOTTOM_Y = EY + 2 * RY + 0;
		Gdiplus::GraphicsPath ButtonL, ButtonM, ButtonR;

		ButtonR.AddArc(	xScale * EX, yScale * EY,			// Ellipse rectangle top-left corner
						xScale * 2 * RX, yScale * 2 * RY,	// Ellipse radii
						0, -BUTTON_ARC);
		x1 = xScale * (EX + 72);
		y1 = yScale * (EY + 2);
		x2 = x1;
		y2 = yScale * (BUTTON_BOTTOM_Y);
		ButtonR.AddLine(x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
		x2 = xScale * (EX + 2 * RX);
		y2 = y1;
		ButtonR.AddLine(x1, y1, x2, y2);
		//x = (EX + 2 * RX) - (RX - RX * std::cos(BUTTON_ARC_RAD));
		//y = (EY) + (RX - RX * std::sin(BUTTON_ARC_RAD));
		//ButtonR.AddLine(xScale * x,		yScale * y,						xScale * x,					yScale * BUTTON_BOTTOM_Y);
		//ButtonR.AddLine(xScale * x,		yScale * BUTTON_BOTTOM_Y,		xScale * (EX + 2 * RX),		yScale * BUTTON_BOTTOM_Y);

		ButtonM.AddArc(	xScale * EX, yScale * EY,			// Ellipse rectangle top-left corner
						xScale * 2 * RX, yScale * 2 * RY,	// Ellipse radii
						-BUTTON_ARC - 6, -BUTTON_ARC);
		x1 = xScale * (EX + 41.5f);
		y1 = yScale * (EY + 1.5f);
		x2 = x1;
		y2 = yScale * (BUTTON_BOTTOM_Y);
		ButtonM.AddLine(x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
		x2 = xScale * (EX + 69.37);							// xScale * (x1 + 2 * (EX + RX - x1));
		y2 = y1;
		ButtonM.AddLine(x1, y1, x2, y2);

		ButtonL.AddArc(	xScale * EX, yScale * EY,			// Ellipse rectangle top-left corner
						xScale * 2 * RX, yScale * 2 * RY,	// Ellipse radii
						180, BUTTON_ARC);
		x1 = xScale * (EX + (2 * RX - 72));
		y1 = yScale * (EY + 2);
		x2 = x1;
		y2 = yScale * (BUTTON_BOTTOM_Y);
		ButtonL.AddLine(x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
		x2 = xScale * (EX);
		y2 = y1;
		ButtonL.AddLine(x1, y1, x2, y2);

		Buffer.DrawPath(&pnMouse, &ButtonR);
		Buffer.DrawPath(&pnMouse, &ButtonM);
		Buffer.DrawPath(&pnMouse, &ButtonL);
		
		if (Llid::MouseR == true)
		{
			Buffer.FillPath(&brButtonDown, &ButtonR);
		}
		else
		{
			Buffer.FillPath(&brButtonUp, &ButtonR);
		}
		if (Llid::MouseM == true)
		{
			Buffer.FillPath(&brButtonDown, &ButtonM);
		}
		else
		{
			Buffer.FillPath(&brButtonUp, &ButtonM);
		}
		if (Llid::MouseL == true)
		{
			Buffer.FillPath(&brButtonDown, &ButtonL);
		}
		else
		{
			Buffer.FillPath(&brButtonUp, &ButtonL);
		}
	}
	
	
	/// 
	/// MOUSE WHEEL
	/// 
	
	{
		Gdiplus::RectF rectImage{xScale * 220, yScale * 300, xScale * 225, yScale * 225};
		Buffer.DrawImage(Llid::pbmMouseWheel, rectImage);
		
		const Gdiplus::REAL X = 220;
		//const Gdiplus::REAL Y = 300;

		if (true)	//(Llid::nWheelDelta != 0)
		{
			Gdiplus::GraphicsPath ArrowWheel;

			if (Llid::nWheelDelta > 0)
			{
				ArrowWheel.AddBezier(	xScale * (X + 20),	yScale * 500,
										xScale * (X + 20),	yScale * 440,
										xScale * (X + 60),	yScale * 340,
										xScale * (X + 140),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 140),	yScale * 320,
										xScale * (X + 120),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 120),	yScale * 320,
										xScale * (X + 140),	yScale * 320);
				ArrowWheel.AddLine(		xScale * (X + 140),	yScale * 320,
										xScale * (X + 125),	yScale * 335);
			}
			else if (Llid::nWheelDelta < 0)
			{
				ArrowWheel.AddBezier(	xScale * (X + 140),	yScale * 320,
										xScale * (X + 60),	yScale * 340,
										xScale * (X + 20),	yScale * 440,
										xScale * (X + 20),	yScale * 500);
				ArrowWheel.AddLine(		xScale * (X + 20),	yScale * 500,
										xScale * (X + 15),	yScale * 480);
				ArrowWheel.AddLine(		xScale * (X + 15),	yScale * 480,
										xScale * (X + 20),	yScale * 500);
				ArrowWheel.AddLine(		xScale * (X + 20),	yScale * 500,
										xScale * (X + 30),	yScale * 480);
			}

			/*if (Llid::nWheelDelta > 0)
			{
				//Buffer.DrawPath(&pnErase, &ArrowWheelDw);
				Buffer.DrawPath(&pnMouse, &ArrowWheelUp);
			}
			else if (Llid::nWheelDelta < 0)
			{
				//Buffer.DrawPath(&pnErase, &ArrowWheelUp);
				Buffer.DrawPath(&pnMouse, &ArrowWheelDw);
			}*/

			Buffer.DrawPath(&pnMouse, &ArrowWheel);

			Llid::nWheelDelta = 0;
		}
	}
	
	
	/// 
	/// LOGO
	/// 
	
	if (false)
	{
		PAINTSTRUCT PaintStruct;
		HDC hDC	= BeginPaint(stLogo.hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
		hDC	= GetDC(stLogo.hWnd);							// So, I get the correct "hDC" like this.
		Gdiplus::Graphics Graphics(hDC);

		Gdiplus::RectF Rect(0, 0, 0, 0);

		Gdiplus::Status Status = Graphics.DrawImage(pLogo, Rect);
		//Gdiplus::Status Status = Graphics.DrawImage(pLogo, 0, 0);
		EndPaint(stLogo.hWnd, &PaintStruct);
	}
	

	/// 
	/// WINDOW TRANSPARENCY
	/// 
	
	{
		SetLayeredWindowAttributes(	/*[in] HWND     hwnd					*/	Window.hWnd,
									/*[in] COLORREF crKey					*/	RGB(80, 80, 80),
									/*[in] BYTE     bAlpha					*/	Settings::MainWindow::Opacity,
									/*[in] DWORD    dwFlags					*/	LWA_ALPHA);
		
		///*typedef struct _BLENDFUNCTION {	*/	BLENDFUNCTION Bf;
		//	/*BYTE BlendOp;					*/	Bf.BlendOp				= AC_SRC_OVER;
		//	/*BYTE BlendFlags;				*/	Bf.BlendFlags			= 0;
		//	/*BYTE SourceConstantAlpha;		*/	Bf.SourceConstantAlpha	= 50;
		//	/*BYTE AlphaFormat;				*/	Bf.AlphaFormat			= AC_SRC_ALPHA;
		///*} BLENDFUNCTION, *PBLENDFUNCTION;	*/
		//
		//RECT rc;  
		//GetWindowRect(Window.hWnd, &rc);
		//POINT ptDest = { rc.left, rc.top };
		//SIZE size = { rc.right - rc.left, rc.bottom - rc.top };
		//POINT imagePosition = { 0, 0 };
		//
		//UpdateLayeredWindow(		/*[in]           HWND          hWnd		*/	Window.hWnd,
		//							/*[in, optional] HDC           hdcDst	*/	GetDC(NULL),
		//							/*[in, optional] POINT         *pptDst	*/	&ptDest,
		//							/*[in, optional] SIZE          *psize	*/	&size,
		//							/*[in, optional] HDC           hdcSrc	*/	CreateCompatibleDC(hDC),
		//							/*[in, optional] POINT         *pptSrc	*/	&imagePosition,
		//							/*[in]           COLORREF      crKey	*/	RGB(0, 0, 0),
		//							/*[in, optional] BLENDFUNCTION *pblend	*/	&Bf,
		//							/*[in]           DWORD         dwFlags	*/	ULW_ALPHA);
	}

	/// 
	/// CHILD WINDOW LOCATIONS
	/// 
	
	if (bProcessIsTerminating == false)	// If we don't do this check, all of the non-GDI+ Win32 functions (i.e.; MoveWindow and UpdateFontProperty) fail after clicking the close button.
	{
		int x	= xScale * Llid::rcLogo.left;
		int y	= yScale * Llid::rcLogo.right;
		int w	= xScale * Llid::rcLogo.top;
		int h	= yScale * Llid::rcLogo.bottom;
		Buffer.DrawImage(pLogo, x, y, w, h);
		
		x		= xScale * Llid::rcTrackbar.left;
		y		= yScale * Llid::rcTrackbar.right;
		w		= xScale * Llid::rcTrackbar.top;
		h		= yScale * Llid::rcTrackbar.bottom;
		MoveWindow(tbOpacity.hWnd, x, y, w, h, FALSE);
		
		/*Gdiplus::FontFamily	fontFamily(L"Times New Roman");
		Gdiplus::Font		font(&fontFamily, min(xScale, yScale) * 12, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
		x		= xScale * (Llid::rcTrackbar.left - Llid::rcBuddy.top);
		y		= yScale * (Llid::rcTrackbar.right);
		w		= xScale * (0);
		h		= yScale * (0);
		Gdiplus::PointF		point000(x, y);
		
		x		= xScale * (Llid::rcTrackbar.left + Llid::rcTrackbar.top + Llid::rcBuddy.top);
		y		= yScale * (Llid::rcTrackbar.right);
		w		= xScale * (0);
		h		= yScale * (0);
		Gdiplus::PointF		point255(x, y);
		
		Gdiplus::SolidBrush	solidBrush(Gdiplus::Color(255, 0, 0, 255));
		Buffer.DrawString(L"0",		-1, &font, point000, &solidBrush);
		Buffer.DrawString(L"255",	-1, &font, point255, &solidBrush);*/
		
		x		= xScale * Llid::rcBuddy000.left;
		y		= yScale * Llid::rcBuddy000.right;
		w		= xScale * Llid::rcBuddy000.top;
		h		= yScale * Llid::rcBuddy000.bottom;
		MoveWindow(st000.hWnd, x, y, w, h, FALSE);
		
		x		= xScale * Llid::rcBuddy255.left;
		y		= yScale * Llid::rcBuddy255.right;
		w		= xScale * Llid::rcBuddy255.top;
		h		= yScale * Llid::rcBuddy255.bottom;
		MoveWindow(st255.hWnd, x, y, w, h, FALSE);
		
		st000.UpdateFontProperty_Width	(xScale * 5);
		st000.UpdateFontProperty_Height	(yScale * 20);
		
		st255.UpdateFontProperty_Width	(xScale * 5);
		st255.UpdateFontProperty_Height	(yScale * 20);
		
		x		= xScale * Llid::rcClose.left;
		y		= yScale * Llid::rcClose.right;
		w		= xScale * Llid::rcClose.top;
		h		= yScale * Llid::rcClose.bottom;
		MoveWindow(btClose.hWnd, x, y, w, h, FALSE);
	}


	//EndPaint(Window.hWnd, &PaintStruct);
	Graphics.DrawImage(&Bmp, 0, 0);
}




void WindowMain::DrawAndFillRoundedRectangle(			Gdiplus::Graphics	&	Graphics,
												const	Gdiplus::Pen		&	Pen,
												const	Gdiplus::SolidBrush	&	Brush,
														INT						X_LEFT,
														INT						Y_TOP,
														INT						WIDTH,
														INT						HEIGHT,
														INT						X_RADIUS,
														INT						Y_RADIUS)
{
	const		INT		ArcWidth	= 2 * X_RADIUS;
	const		INT		ArcHeigth	= 2 * Y_RADIUS;
	constexpr	float	SweepAngle	= -90.0f;		// Stupid GDI+ sweeps in the negative direction.
													// The minus sign is to compensate it.
	Gdiplus::GraphicsPath Path;
	
	// Top-Left Arc
	Path.AddArc(	X_LEFT,
					Y_TOP,
					ArcWidth, ArcHeigth,
					-90.0f, SweepAngle);

	// Left Edge
	Path.AddLine(	X_LEFT,
					Y_TOP				+ Y_RADIUS,
					X_LEFT,
					Y_TOP	+ HEIGHT	- Y_RADIUS);

	// Bottom-Left Arc
	Path.AddArc(	X_LEFT,
					Y_TOP	+ HEIGHT	- ArcHeigth,
					ArcWidth, ArcHeigth,
					-180.0f, SweepAngle);

	// Bottom Edge
	Path.AddLine(	X_LEFT				+ X_RADIUS,
					Y_TOP	+ HEIGHT,
					X_LEFT	+ WIDTH		- X_RADIUS,
					Y_TOP	+ HEIGHT);

	// Bottom-Right Arc
	Path.AddArc(	X_LEFT	+ WIDTH		- ArcWidth,
					Y_TOP	+ HEIGHT	- ArcHeigth,
					ArcWidth, ArcHeigth,
					-270.0f, SweepAngle);

	// Right Edge
	Path.AddLine(	X_LEFT	+ WIDTH,
					Y_TOP	+ HEIGHT	- Y_RADIUS,
					X_LEFT	+ WIDTH,
					Y_TOP				+ Y_RADIUS);

	// Top-Right Arc
	Path.AddArc(	X_LEFT	+ WIDTH		- ArcWidth,
					Y_TOP,
					ArcWidth, ArcHeigth,
					0.0f, SweepAngle);

	// Top Edge
	Path.AddLine(	X_LEFT	+ WIDTH		- X_RADIUS,
					Y_TOP,
					X_LEFT				+ X_RADIUS,
					Y_TOP);
	
	Graphics.FillPath(&Brush,	&Path);
	Graphics.DrawPath(&Pen,		&Path);
}
