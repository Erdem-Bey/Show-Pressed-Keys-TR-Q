#include "TextBlock.h"



TextBlock::TextBlock()
	:	pGraphics		(nullptr)
	//:	hWnd			(NULL)
	,	X				(0)
	,	Y				(0)
	,	Width			(10)
	,	Height			(10)
	,	BackgroundColor	(static_cast<Gdiplus::ARGB>(0xFF0000FF))
	,	TextColor		(static_cast<Gdiplus::ARGB>(0xFF000000))
	,	FrameColor		(static_cast<Gdiplus::ARGB>(0xFF000000))
	,	FrameThickness	(1)
	//,	Font			(&Gdiplus::FontFamily(L"Arial"), 12)
	,	FontHeight		(12)
	,	FontFamily		(L"Arial")
	,	Text			(L"Text")
{
}


TextBlock::~TextBlock()
{
}


void TextBlock::Update()
{
	//if (hWnd == NULL)
	if (pGraphics == nullptr)
	{
		return;
	}

	//PAINTSTRUCT	PaintStruct;
	//HDC			hDC	= BeginPaint(hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
	//			hDC	= GetDC(hWnd);						// So, I get the correct "hDC" like this.

	//		Gdiplus::Graphics	Graphics	(hDC);
	const	Gdiplus::Pen		Pen			(FrameColor);
	const	Gdiplus::SolidBrush	brBack		(BackgroundColor);
	const	Gdiplus::SolidBrush	brText		(TextColor);
    
	pGraphics->FillRectangle(&brBack,	X,	Y,	Width,	Height);
	pGraphics->DrawRectangle(&Pen,	X,	Y,	Width,	Height);
	
	Gdiplus::Font Font(&Gdiplus::FontFamily(FontFamily.c_str()), FontHeight);
	
	Gdiplus::RectF Rect;
	pGraphics->MeasureString(Text.c_str(), Text.length(), &Font, {0, 0}, &Rect);

	//const Gdiplus::REAL &	Xs	= X;
	//const Gdiplus::REAL	Ys	= Y + (Height - FontHeight) / 2;
	
	const Gdiplus::REAL Xs = X + (Width  - Rect.Width)  / 2;
	const Gdiplus::REAL Ys = Y + (Height - Rect.Height) / 2;

	Gdiplus::Status Status = pGraphics->DrawString(Text.c_str(), -1, &Font, Gdiplus::PointF(Xs, Ys), &brText);
	if (Status != Gdiplus::Ok)
	{
		// ...
	}

	//EndPaint(hWnd, &PaintStruct);
}
