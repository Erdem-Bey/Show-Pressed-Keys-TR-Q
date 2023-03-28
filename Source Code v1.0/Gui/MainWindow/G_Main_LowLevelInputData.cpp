#include "G_Main_LowLevelInputData.h"

#include <chrono>


std::vector<KeyboardKey>		Llid::KeysLarge;
std::vector<KeyboardKey>		Llid::KeysSmall;
std::vector<Gdiplus::PointF>	Llid::EnterVertices;
std::vector<Gdiplus::PointF>	Llid::EnterArrowVertices;
std::vector<Gdiplus::PointF>	Llid::ArrowKeyVertices_Up;
std::vector<Gdiplus::PointF>	Llid::ArrowKeyVertices_Left;
std::vector<Gdiplus::PointF>	Llid::ArrowKeyVertices_Down;
std::vector<Gdiplus::PointF>	Llid::ArrowKeyVertices_Right;
bool							Llid::EnterPressed				= false;

bool							Llid::LedNumber					= ((GetKeyState(VK_NUMLOCK)	& 0x0001) == 0x0001);
bool							Llid::LedCaps					= ((GetKeyState(VK_CAPITAL)	& 0x0001) == 0x0001);
bool							Llid::LedScroll					= ((GetKeyState(VK_SCROLL)	& 0x0001) == 0x0001);

HHOOK							Llid::hHookK;
HHOOK							Llid::hHookM;

std::list<std::future<void>>	Llid::HookFutures;

void *							Llid::pWindow					= nullptr;


bool							Llid::MouseL					= false;
bool							Llid::MouseM					= false;
bool							Llid::MouseR					= false;

Gdiplus::Bitmap *				Llid::pbmCatWheel				= nullptr;
Gdiplus::Bitmap *				Llid::pbmMouseWheel				= nullptr;
int								Llid::nWheelDelta				= 0;


RECT							Llid::rcLogo					{};
RECT							Llid::rcTrackbar				{};
RECT							Llid::rcClose					{};
RECT							Llid::rcBuddy000				{};
RECT							Llid::rcBuddy255				{};

//constexpr UINT				Llid::WM_USER_KEYBOARD			= WM_USER + 1;
//constexpr UINT				Llid::WM_USER_MOUSE				= WM_USER + 2;
//constexpr UINT				Llid::WM_USER_MOUSE_WHEEL		= WM_USER + 3;



std::future<void> & Llid::CleanUpCompletedThreadsAndGetMeAnIdleFutre()
{
	for (std::list<std::future<void>>::iterator it=HookFutures.begin(); it!=HookFutures.end(); /*++it*/)
	{
		if (it->valid() == false)
		{
			it = HookFutures.erase(it);
		}
		else
		{
			const std::future_status Status = it->wait_for(std::chrono::seconds(0));

			switch(Status)
			{
				case std::future_status::deferred:
					// Do nothing. The code mustn't reach here.
					break;
				case std::future_status::timeout:
					// The thread is still running. Don't delete it.
					break;
				case std::future_status::ready:
					it = HookFutures.erase(it);
					break;
			}
		}

		if (it != HookFutures.end())
		{
			++it;
		}
	}

	return HookFutures.emplace_back();
}

void Llid::WaitForAllThreadsToComplete()
{
	for (std::list<std::future<void>>::const_iterator cit=HookFutures.cbegin(); cit!=HookFutures.cend(); ++cit)
	{
		if (cit->valid() == false)
		{
			continue;
		}

		cit->wait();
	}
}
