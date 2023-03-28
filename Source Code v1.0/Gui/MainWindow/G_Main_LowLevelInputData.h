#pragma once

#include <future>
#include <list>
#include <vector>
#include <Windows.h>
#include <gdiplus.h>

#include "..\..\KeySize.h"
#include "..\..\KeyboardKey.h"


class Llid
{
	public:
		Llid() = delete;
		Llid(Llid &) = delete;

		static std::vector<KeyboardKey> KeysLarge;
		static std::vector<KeyboardKey> KeysSmall;
		
		static std::vector<Gdiplus::PointF> EnterVertices;
		static std::vector<Gdiplus::PointF> EnterArrowVertices;
		static std::vector<Gdiplus::PointF> ArrowKeyVertices_Up;
		static std::vector<Gdiplus::PointF> ArrowKeyVertices_Left;
		static std::vector<Gdiplus::PointF> ArrowKeyVertices_Down;
		static std::vector<Gdiplus::PointF> ArrowKeyVertices_Right;
		static bool EnterPressed;

		static bool LedNumber;
		static bool LedCaps;
		static bool LedScroll;
		
		static bool MouseL;
		static bool MouseM;
		static bool MouseR;
		
		static Gdiplus::Bitmap * pbmCatWheel;
		static Gdiplus::Bitmap * pbmMouseWheel;
		static int nWheelDelta;

		static HHOOK hHookK, hHookM;
		static std::list<std::future<void>> HookFutures;
		static std::future<void> & CleanUpCompletedThreadsAndGetMeAnIdleFutre();
		static void WaitForAllThreadsToComplete();

		static void * pWindow;
		
		static RECT rcLogo;
		static RECT rcTrackbar;
		static RECT rcClose;
		static RECT rcBuddy000;
		static RECT rcBuddy255;
		
		static constexpr UINT WM_USER_KEYBOARD		= WM_USER + 1;
		static constexpr UINT WM_USER_MOUSE			= WM_USER + 2;
		static constexpr UINT WM_USER_MOUSE_WHEEL	= WM_USER + 3;
		
};

