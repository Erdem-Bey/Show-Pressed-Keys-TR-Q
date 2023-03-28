#pragma once
#ifndef WINDOWS_CLASSES__TIMER_H
#define WINDOWS_CLASSES__TIMER_H

#include <stdint.h>
#include <functional>
#include <list>
#include <Windows.h>

class Timer
{
	public:
		uint64_t TimerId;

		Timer();
		Timer(UINT Period, std::function<void(uint64_t)> SubscribedMember);
		~Timer();
		
		void Set(UINT Period, std::function<void(uint64_t)> SubscribedMember);
		void Kill();

	protected:
		class TimerInfo
		{
			public:
				TimerInfo(std::function<void(uint64_t)> Cbf, uint64_t Tid)
							: FunctionToBeCalled(Cbf), TimerId(Tid) {}
				std::function<void(uint64_t)> FunctionToBeCalled;
				uint64_t TimerId;
		};
		
		static VOID CALLBACK TimerProc(	_In_  HWND hwnd,
										_In_  UINT uMsg,
										_In_  UINT_PTR idEvent,
										_In_  DWORD dwTime);
		
		static std::list<TimerInfo> Subscribers;

};

#endif	// WINDOWS_CLASSES__TIMER_H
