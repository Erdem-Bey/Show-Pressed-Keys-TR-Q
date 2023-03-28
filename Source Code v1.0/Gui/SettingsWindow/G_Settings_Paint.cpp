#include "G_Settings.h"

#include <Windows.h>
#include <gdiplus.h>

void WindowSettings::PaintColorBox(const Edit5 & ColorGroup)
{
	PAINTSTRUCT  PaintStruct;
	const HWND & hWnd = ColorGroup.back().hWnd;
	HDC hDC	= BeginPaint(hWnd, &PaintStruct);
	hDC		= GetDC(hWnd);
	{
				Gdiplus::Graphics	Graphics	(hDC);
		const	Gdiplus::SolidBrush	Brush		(GetGdiplusColor(ColorGroup));
		Graphics.FillRectangle(&Brush, 0, 0, EDIT_WIDTH, LINE_HEIGHT);
	}
	EndPaint(hWnd, &PaintStruct);
}

Gdiplus::Color WindowSettings::GetGdiplusColor(const Edit5 & ColorGroup)
{
	return Gdiplus::Color(	static_cast<BYTE>(ColorGroup[3].GetContent<unsigned int>()),	// A
							static_cast<BYTE>(ColorGroup[0].GetContent<unsigned int>()),	// R
							static_cast<BYTE>(ColorGroup[1].GetContent<unsigned int>()),	// G
							static_cast<BYTE>(ColorGroup[2].GetContent<unsigned int>()));	// B
}

