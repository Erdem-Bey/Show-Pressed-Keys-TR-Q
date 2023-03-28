#include "Timer.h"
#include <Windows.h>

std::list<Timer::TimerInfo> Timer::Subscribers;

Timer::Timer()
{
	TimerId = 0;
}

Timer::Timer(UINT Period, std::function<void(uint64_t)> SubscribedMember)
{
	Set(Period, SubscribedMember);
}

Timer::~Timer()
{
	Kill();
}

void Timer::Set(UINT Period, std::function<void(uint64_t)> SubscribedMember)
{
	if (TimerId)
	{
		return;
	}
	TimerId = SetTimer(NULL, TimerId, Period, Timer::TimerProc);
	if (TimerId)
	{
		Subscribers.push_back(TimerInfo(SubscribedMember, TimerId));
	}
}

void Timer::Kill()
{
	if (!TimerId)
	{
		return;
	}
	for (std::list<TimerInfo>::iterator it=Subscribers.begin(); it!=Subscribers.end(); ++it)
	{
		if (it->TimerId == TimerId)
		{
			KillTimer(NULL, TimerId);
			Subscribers.erase(it);
			break;
		}
	}
	TimerId = 0;
}

VOID CALLBACK Timer::TimerProc(	_In_ HWND hwnd,
								_In_ UINT uMsg,
								_In_ UINT_PTR idEvent,
								_In_ DWORD dwTime)
{
	for (std::list<TimerInfo>::iterator it=Subscribers.begin(); it!=Subscribers.end(); ++it)
	{
		if (it->TimerId == idEvent)
		{
			it->FunctionToBeCalled(it->TimerId);
			break;
		}
	}
}
