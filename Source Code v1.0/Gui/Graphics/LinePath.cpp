#include "LinePath.h"



LinePath::LinePath()
	:	pGraphics	(nullptr)
	//:	hWnd		(NULL)
	,	Thickness	(1)
	,	Color		(static_cast<Gdiplus::ARGB>(0xFF000000))
	,	Vertexes	()
{
}


LinePath::~LinePath()
{
}


void LinePath::Update()
{
	//if (hWnd == NULL)
	if (pGraphics == nullptr)
	{
		return;
	}
	
	const size_t NumPoints = Vertexes.size();

	if (NumPoints < 2)
	{
		return;
	}

	//PAINTSTRUCT	PaintStruct;
	//HDC			hDC	= BeginPaint(hWnd, &PaintStruct);	// This doesn't return "hDC" correctly.
	//			hDC	= GetDC(hWnd);						// So, I get the correct "hDC" like this.

	//		Gdiplus::Graphics		Graphics	(hDC);
			Gdiplus::GraphicsPath	Path;
	const	Gdiplus::Pen			Pen			(Color, Thickness);
	
	Path.AddLines(&Vertexes[0], NumPoints);
	/*for (size_t i=0; i<NumPoints-1; i++)
	{
		Path.AddLine(Vertexes[i], Vertexes[i+1]);
	}*/

	Gdiplus::Status Status = pGraphics->DrawPath(&Pen, &Path);
	
	if (Status != Gdiplus::Ok)
	{
		// ...
	}

	//EndPaint(hWnd, &PaintStruct);
}
