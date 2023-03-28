#include "UpDown.h"

#include <CommCtrl.h>


DWORD UpDown::DEFAULT_STYLES	= UDS_SETBUDDYINT | UDS_ARROWKEYS | UDS_ALIGNRIGHT | WS_VISIBLE | WS_CHILD;
DWORD UpDown::DEFAULT_EXSTYLES	= WS_EX_CLIENTEDGE;
bool  UpDown::COMMON_CONTROL_INITIALIZED = false;

UpDown::UpDown()
{
}

UpDown::UpDown(		int							x,
					int							y,
					int							Width,
					int							Height,
					HINSTANCE					hInstance,
					HWND						hWndParent,
					WORD						Identifier		/*= 0*/,
					DWORD						Styles			/*= DEFAULT_STYLES*/,
					DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass(), BuddyWindow()
{
	Create(										x,
												y,
												Width,
												Height,
												hInstance,
												hWndParent,
												Identifier		/*= 0*/,
												Styles			/*= DEFAULT_STYLES*/,
												ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void UpDown::Create(int							x,
					int							y,
					int							Width,
					int							Height,
					HINSTANCE					hInstance,
					HWND						hWndParent,
					WORD						Identifier		/*= 0*/,
					DWORD						Styles			/*= DEFAULT_STYLES*/,
					DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	BuddyWindow.Create(	x,
						y,
						Width,
						Height,
						hInstance,
						hWndParent,
						L"",
						Identifier);
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_UPDOWN_CLASS;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	UPDOWN_CLASSW,
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		(HMENU) Identifier,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	StorePositionAndSize(x, y, Width, Height);
	ChooseDefaultFont();
	SendMessageW(hWnd, UDM_SETBUDDY, (WPARAM) BuddyWindow.hWnd, (LPARAM) NULL);
}

void UpDown::Destroy()
{
	//SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
	DestroyWindow(hWnd);
	DestroyWindow(BuddyWindow.hWnd);
}

UpDown::~UpDown()
{
	Destroy();
}

void UpDown::SetRange(INT Low, INT High)
{
	SendMessageW(hWnd, UDM_SETRANGE32, (WPARAM) Low, (LPARAM) High);
}

void UpDown::SetPosition(INT NewPosition)
{
	SendMessageW(hWnd, UDM_SETPOS32, (WPARAM) NULL, (LPARAM) NewPosition);
}

INT UpDown::GetPosition() const
{
	return (INT) SendMessageW(hWnd, UDM_GETPOS32, (WPARAM) NULL, (LPARAM) NULL);
}

void UpDown::UpdateSpeedIncrements()
{
	std::vector<UINT>::size_type Size = SpeedIncrements.size();
	if ((Size != IncrementTimes.size()) || (Size == 0))
	{
		return;
	}
	std::vector<UDACCEL> Accels;
	Accels.reserve(Size);
	UDACCEL Accel;
	for (std::vector<UINT>::size_type i=0; i<Size; i++)
	{
		Accel.nInc = SpeedIncrements[i];
		Accel.nSec = IncrementTimes[i];
		Accels.push_back(Accel);
	}
	SendMessageW(hWnd, UDM_SETACCEL, (WPARAM) Size, (LPARAM) &Accels[0]);
}

void UpDown::SetText(const std::wstring & Text)
{
	BuddyWindow.SetText(Text);
}

std::wstring UpDown::GetText() const
{
	WPARAM Size = SendMessageW(BuddyWindow.hWnd, WM_GETTEXTLENGTH, (WPARAM) NULL, (LPARAM) NULL);
	wchar_t * Buffer = new wchar_t[Size + 1];
	SendMessageW(BuddyWindow.hWnd, WM_GETTEXT, Size + 1, (LPARAM) Buffer);
	std::wstring Text(Buffer, Size);
	delete Buffer;
	return Text;
}

int64_t UpDown::GetInteger() const
{
	std::wstringstream ss;
	ss << GetText();
	int64_t Ret;
	ss >> Ret;
	return Ret;
}

uint64_t UpDown::GetUInteger() const
{
	std::wstringstream ss;
	ss << GetText();
	uint64_t Ret;
	ss >> Ret;
	return Ret;
}

double UpDown::GetDouble() const
{
	std::wstringstream ss;
	ss << GetText();
	double Ret;
	ss >> Ret;
	return Ret;
}

/*void UpDown::AlignTo	(const BaseWindowClass & ReferenceWindow,
						BaseWindowClass::ALIGN_SIDE WhichSideToAlign,
						BaseWindowClass::ALIGN_TYPE HowToAlign,
						int SpaceToLeaveBetween)
{
	//BaseWindowClass::AlignTo(ReferenceWindow, WhichSideToAlign, HowToAlign, SpaceToLeaveBetween);
	switch (WhichSideToAlign)
	{
		case ALIGN_SIDE::AS_RIGHT:
			BuddyWindow.AlignTo	(ReferenceWindow,	ALIGN_SIDE::AS_RIGHT,	HowToAlign,				SpaceToLeaveBetween);
			this->AlignTo		(BuddyWindow,		ALIGN_SIDE::AS_RIGHT,	ALIGN_TYPE::AT_CENTER,	0);
		case ALIGN_SIDE::AS_LEFT:
			//this->AlignTo		(ReferenceWindow,	ALIGN_SIDE::AS_LEFT,	HowToAlign,				SpaceToLeaveBetween);
			//BuddyWindow.AlignTo	(std::ref(*this),	ALIGN_SIDE::AS_LEFT,	ALIGN_TYPE::AT_CENTER,	0);
			BuddyWindow.AlignTo	(ReferenceWindow,	ALIGN_SIDE::AS_LEFT,	HowToAlign,				SpaceToLeaveBetween + w);
			this->AlignTo		(BuddyWindow,		ALIGN_SIDE::AS_RIGHT,	ALIGN_TYPE::AT_CENTER,	0);
		case ALIGN_SIDE::AS_TOP:
			BuddyWindow.AlignTo	(ReferenceWindow,	ALIGN_SIDE::AS_TOP,		HowToAlign,				SpaceToLeaveBetween);
			this->AlignTo		(BuddyWindow,		ALIGN_SIDE::AS_RIGHT,	ALIGN_TYPE::AT_CENTER,	0);
		case ALIGN_SIDE::AS_BOTTOM:
			BuddyWindow.AlignTo	(ReferenceWindow,	ALIGN_SIDE::AS_BOTTOM,	HowToAlign,				SpaceToLeaveBetween);
			this->AlignTo		(BuddyWindow,		ALIGN_SIDE::AS_RIGHT,	ALIGN_TYPE::AT_CENTER,	0);
	}
}*/



