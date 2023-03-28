#include "StatusBar.h"

#include <CommCtrl.h>


DWORD StatusBar::DEFAULT_STYLES		= SBARS_SIZEGRIP | WS_VISIBLE | WS_CHILD;
DWORD StatusBar::DEFAULT_EXSTYLES	= 0;
bool  StatusBar::COMMON_CONTROL_INITIALIZED = false;

StatusBar::StatusBar()
{
}

StatusBar::StatusBar(	HINSTANCE					hInstance,
						HWND						hWndParent,
						WORD						Identifier		/*= 0*/,
						DWORD						Styles			/*= DEFAULT_STYLES*/,
						DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
	: BaseWindowClass()
{
	Create(											hInstance,
													hWndParent,
													Identifier		/*= 0*/,
													Styles			/*= DEFAULT_STYLES*/,
													ExtendedStyles	/*= DEFAULT_EXSTYLES*/);
}

void StatusBar::Create(	HINSTANCE					hInstance,
						HWND						hWndParent,
						WORD						Identifier		/*= 0*/,
						DWORD						Styles			/*= DEFAULT_STYLES*/,
						DWORD						ExtendedStyles	/*= DEFAULT_EXSTYLES*/)
{
	if (!COMMON_CONTROL_INITIALIZED)
	{
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC  = ICC_BAR_CLASSES;
		InitCommonControlsEx(&iccx);
		COMMON_CONTROL_INITIALIZED = true;
	}
	hWnd = CreateWindowExW(	/*_In_		DWORD*/		ExtendedStyles,
							/*_In_opt_	LPCTSTR*/	STATUSCLASSNAMEW,
							/*_In_opt_	LPCTSTR*/	L"",
							/*_In_		DWORD*/		Styles,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_		int*/		0,
							/*_In_opt_	HWND*/		hWndParent,
							/*_In_opt_	HMENU*/		NULL,
							/*_In_opt_	HINSTANCE*/	hInstance,
							/*_In_opt_	LPVOID*/	NULL);
	ChooseDefaultFont();
}

void StatusBar::Destroy()
{
	SendMessageW(hWnd, WM_DESTROY, NULL, NULL);
}

StatusBar::~StatusBar()
{
	Destroy();
}

/*void StatusBar::UpdatePartLocations()
{
	if (PartLocations.size())
	{
		SendMessageW(hWnd, SB_SETPARTS, (WPARAM) PartLocations.size(), (LPARAM) &(PartLocations[0]));
	}
}

std::vector<INT> StatusBar::GetPartLocations() const
{
	constexpr INT MAX_NUM_PARTS = 256;
	INT * pParts;
	SendMessageW(hWnd, SB_GETPARTS, (WPARAM) MAX_NUM_PARTS, (LPARAM) pParts);
}*/

/*void StatusBar::SetPartText(BYTE PartId, const std::wstring & Text)
{
	//if (static_cast<std::vector<INT>::size_type>(PartId) < PartLocations.size())
	//{
		SendMessageW(hWnd, SB_SETTEXT, (WPARAM) MAKEWORD(PartId, 0), (LPARAM) Text.c_str());
	//}
}

void StatusBar::SetPartText(BYTE PartId, long int Text)
{
	std::wstringstream ss;
	ss << Text;
	//if (static_cast<std::vector<INT>::size_type>(PartId) < PartLocations.size())
	//{
		SendMessageW(hWnd, SB_SETTEXT, (WPARAM) MAKEWORD(PartId, 0), (LPARAM) ss.str().c_str());
	//}
}

void StatusBar::SetPartText(BYTE PartId, double Text)
{
	std::wstringstream ss;
	ss << Text;
	//if (static_cast<std::vector<INT>::size_type>(PartId) < PartLocations.size())
	//{
		SendMessageW(hWnd, SB_SETTEXT, (WPARAM) MAKEWORD(PartId, 0), (LPARAM) ss.str().c_str());
	//}
}*/
