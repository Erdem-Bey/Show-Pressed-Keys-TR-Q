#include "BaseWindowClass.h"

#include <utility>
#include <sstream>
#include <Windows.h>
#include <WinUser.h>


BaseWindowClass::BaseWindowClass()
{
}

BaseWindowClass::~BaseWindowClass()
{
}

void BaseWindowClass::ProcessMessages()
{
	MSG Msg;
	while (PeekMessageW(&Msg, hWnd, 0, 0, PM_REMOVE))
	{
		if (!IsDialogMessageW(hWnd, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);
		}
	}
}

void BaseWindowClass::UpdateFontProperty_Weight(const int Weight)
{
	const HFONT hFontOld = reinterpret_cast<HFONT>(::SendMessageW(hWnd, WM_GETFONT, NULL, NULL));
	LOGFONTW LogFont;
	::GetObjectW(hFontOld, sizeof(LOGFONTW), &LogFont);
	LogFont.lfWeight = Weight;
	const HFONT hFontNew = ::CreateFontIndirectW(&LogFont);
	::SendMessageW(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hFontNew), TRUE);
	::DeleteObject(hFontOld);
}

void BaseWindowClass::UpdateFontProperty_Width(const int Width)
{
	const HFONT hFontOld = reinterpret_cast<HFONT>(::SendMessageW(hWnd, WM_GETFONT, NULL, NULL));
	LOGFONTW LogFont;
	::GetObjectW(hFontOld, sizeof(LOGFONTW), &LogFont);
	LogFont.lfWidth = Width;
	const HFONT hFontNew = ::CreateFontIndirectW(&LogFont);
	::SendMessageW(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hFontNew), TRUE);
	::DeleteObject(hFontOld);
}

void BaseWindowClass::UpdateFontProperty_Height(const int Height)
{
	const HFONT hFontOld = reinterpret_cast<HFONT>(::SendMessageW(hWnd, WM_GETFONT, NULL, NULL));
	LOGFONTW LogFont;
	::GetObjectW(hFontOld, sizeof(LOGFONTW), &LogFont);
	LogFont.lfHeight = Height;
	const HFONT hFontNew = ::CreateFontIndirectW(&LogFont);
	::SendMessageW(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hFontNew), TRUE);
	::DeleteObject(hFontOld);
}

void BaseWindowClass::ChooseDefaultFont()
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

void BaseWindowClass::Enable()
{
	EnableWindow(hWnd, TRUE);
}

void BaseWindowClass::Disable()
{
	EnableWindow(hWnd, FALSE);
}

bool BaseWindowClass::IsEnabled() const
{
	return IsWindowEnabled(hWnd);
}

bool BaseWindowClass::IsDisabled() const
{
	return !IsWindowEnabled(hWnd);
}

void BaseWindowClass::Show() const
{
	//LONG_PTR WindowStyle = GetWindowLongPtrW(hWnd, GWL_STYLE);
	//WindowStyle |= WS_VISIBLE;
	//SetWindowLongPtrW(hWnd, GWL_STYLE, WindowStyle);
	//SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	ShowWindow(hWnd, SW_SHOW);
}

void BaseWindowClass::Hide() const
{
	//LONG_PTR WindowStyle = GetWindowLongPtrW(hWnd, GWL_STYLE);
	//WindowStyle &= ~WS_VISIBLE;
	//SetWindowLongPtrW(hWnd, GWL_STYLE, WindowStyle);
	//SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	ShowWindow(hWnd, SW_HIDE);
}

bool BaseWindowClass::CheckStyle(DWORD Style)
{
	return (bool) (GetWindowLongW(hWnd, GWL_STYLE) & Style);
}

bool BaseWindowClass::CheckExStyle(DWORD ExStyle)
{
	return (bool) (GetWindowLongW(hWnd, GWL_EXSTYLE) & ExStyle);
}

void BaseWindowClass::AddStyle(DWORD NewStyle)
{
	SetWindowLongW(hWnd, GWL_STYLE, /*newstyle=*/GetWindowLongW(hWnd, GWL_STYLE) | NewStyle);
	UpdateWindowStyles();
}

void BaseWindowClass::AddExStyle(DWORD ExNewStyle)
{
	SetWindowLongW(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) | ExNewStyle);
	UpdateWindowStyles();
}

void BaseWindowClass::RemoveStyle(DWORD StyleToBeRemoved)
{
	SetWindowLongW(hWnd, GWL_STYLE, GetWindowLongW(hWnd, GWL_STYLE) & (~StyleToBeRemoved));
	UpdateWindowStyles();
}

void BaseWindowClass::RemoveExStyle(DWORD ExStyleToBeRemoved)
{
	SetWindowLongW(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) & (~ExStyleToBeRemoved));
	UpdateWindowStyles();
}

void BaseWindowClass::UpdateWindowStyles()
{
	SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void BaseWindowClass::SetWindowPosition(int x, int y, int w, int h)
{
	SetWindowPos(hWnd, NULL, x, y, w, h, SWP_NOZORDER | SWP_NOOWNERZORDER);
}

void BaseWindowClass::SetWindowPosition(const RECT & Rect)
{
	SetWindowPosition(Rect.left, Rect.top, Rect.right-Rect.left, Rect.bottom-Rect.top);
}

void BaseWindowClass::Move(int x, int y)
{
	//SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | (SWP_NOOWNERZORDER*0) | SWP_NOSIZE);
	SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE);
	this->x = x;
	this->y = y;
}

void BaseWindowClass::Resize(int w, int h)
{
	SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE);
	this->w = w;
	this->h = h;
}

void BaseWindowClass::AlignTo(	const BaseWindowClass & ReferenceWindow,
								/*HWND ParentWindow,*/
								ALIGN_SIDE WhichSideToAlign,
								ALIGN_TYPE HowToAlign,
								int SpaceToLeaveBetween)
{
	int t_x, t_y, t_w, t_h;
	int r_x, r_y, r_w, r_h;
	t_x = x;
	t_y = y;
	t_w = w;
	t_h = h;
	r_x = ReferenceWindow.GetX();
	r_y = ReferenceWindow.GetY();
	r_w = ReferenceWindow.GetWidth();
	r_h = ReferenceWindow.GetHeight();
	switch (WhichSideToAlign)
	{
		case ALIGN_SIDE::AS_RIGHT:
					t_x	= r_x + r_w + SpaceToLeaveBetween;
			switch (HowToAlign)
			{
				case ALIGN_TYPE::AT_RIGHT:
				case ALIGN_TYPE::AT_TOP:
					t_y	= r_y;
					break;
				case ALIGN_TYPE::AT_LEFT:
				case ALIGN_TYPE::AT_BOTTOM:
					t_y	= r_y + r_h - t_h;
					break;
				case ALIGN_TYPE::AT_CENTER:
					t_y	= r_y + (r_h - t_h) / 2;
					break;
			}
			break;
		case ALIGN_SIDE::AS_LEFT:
					t_x	= r_x - t_w - SpaceToLeaveBetween;
			switch (HowToAlign)
			{
				case ALIGN_TYPE::AT_RIGHT:
				case ALIGN_TYPE::AT_TOP:
					t_y	= r_y;
					break;
				case ALIGN_TYPE::AT_LEFT:
				case ALIGN_TYPE::AT_BOTTOM:
					t_y	= r_y + r_h - t_h;
					break;
				case ALIGN_TYPE::AT_CENTER:
					t_y	= r_y + (r_h - t_h) / 2;
					break;
			}
			break;
		case ALIGN_SIDE::AS_TOP:
					t_y	= r_y - t_h - SpaceToLeaveBetween;
			switch (HowToAlign)
			{
				case ALIGN_TYPE::AT_RIGHT:
				case ALIGN_TYPE::AT_TOP:
					t_x	= r_x + r_w - t_w;
					break;
				case ALIGN_TYPE::AT_LEFT:
				case ALIGN_TYPE::AT_BOTTOM:
					t_x	= r_x;
					break;
				case ALIGN_TYPE::AT_CENTER:
					t_x	= r_x + (r_w - t_w) / 2;
					break;
			}
			break;
		case ALIGN_SIDE::AS_BOTTOM:
					t_y	= r_y + r_h + SpaceToLeaveBetween;
			switch (HowToAlign)
			{
				case ALIGN_TYPE::AT_RIGHT:
				case ALIGN_TYPE::AT_TOP:
					t_x	= r_x + r_w - t_w;
					break;
				case ALIGN_TYPE::AT_LEFT:
				case ALIGN_TYPE::AT_BOTTOM:
					t_x	= r_x;
					break;
				case ALIGN_TYPE::AT_CENTER:
					t_x	= r_x + (r_w - t_w) / 2;
					break;
			}
			break;
	}
	//SetWindowPos(hWnd, NULL, t_x, t_y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	Move(t_x, t_y);
	x = t_x;
	y = t_y;
	//this->w = t_w;
	//this->h = t_h;
}

// POINT BaseWindowClass::GetLocalCoordinates() const
// {
// 	RECT RectThis, RectParent;
// 	POINT Point;
// 	//HWND hp=GetParent(hWnd);
// 	GetWindowRect(hWnd,				&RectThis);
// 	GetWindowRect(GetParent(hWnd),	&RectParent);
// 	Point.x = RectThis.left - RectParent.left;
// 	Point.y = RectThis.top  - RectParent.top;
// 	//MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT) &Rect, 2);
// 	return Point;
// }

RECT BaseWindowClass::GetLocalCoordinates() const
{
    RECT Rect;
    GetWindowRect(hWnd, &Rect);
    MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT) &Rect, 2);
    return Rect;
}

POINT BaseWindowClass::GetTopLeftCoordinates() const
{
	POINT Point;
	Point.x = x;
	Point.y = y;
	return Point;
}

RECT BaseWindowClass::GetCornerPoints() const
{
	RECT Rect;
	Rect.left	= x;
	Rect.right	= x + w;
	Rect.top	= y;
	Rect.bottom = y + h;
	return Rect;
}

int BaseWindowClass::GetX() const
{
	return x;
}

int BaseWindowClass::GetY() const
{
	return y;
}

int BaseWindowClass::GetLeft() const
{
	return x;
}

int BaseWindowClass::GetRight() const
{
	return x + w;
}

int BaseWindowClass::GetTop() const
{
	return y;
}

int BaseWindowClass::GetBottom() const
{
	return y + h;
}

int BaseWindowClass::GetWidth() const
{
	return w;
}

int BaseWindowClass::GetHeight() const
{
	return h;
}

const HWND & BaseWindowClass::GetHandle() const
{
	return hWnd;
}

void BaseWindowClass::StorePositionAndSize(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

std::wstring BaseWindowClass::GetText() const
{
	const WPARAM SIZE = SendMessageW(hWnd, WM_GETTEXTLENGTH, (WPARAM) NULL, (LPARAM) NULL) + 1;
	wchar_t * const Buffer = new wchar_t[SIZE];
	SendMessageW(hWnd, WM_GETTEXT, SIZE, (LPARAM) Buffer);
	std::wstring Text(Buffer, SIZE);
	delete Buffer;
	return Text;
}

void BaseWindowClass::SetText(const std::wstring & Text)
{
	SendMessageW(hWnd, WM_SETTEXT, (WPARAM) NULL, (LPARAM) Text.c_str());
}

/*int64_t BaseWindowClass::GetInteger() const
{
	std::wstringstream ss;
	ss << GetText();
	int64_t Ret;
	ss >> Ret;
	return Ret;
}

uint64_t BaseWindowClass::GetUInteger() const
{
	std::wstringstream ss;
	ss << GetText();
	uint64_t Ret;
	ss >> Ret;
	return Ret;
}

double BaseWindowClass::GetDouble() const
{
	std::wstringstream ss;
	ss << GetText();
	double Ret;
	ss >> Ret;
	return Ret;
}*/
