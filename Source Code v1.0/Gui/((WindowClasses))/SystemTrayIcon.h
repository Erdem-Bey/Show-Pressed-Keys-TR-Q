#pragma once
#ifndef WINDOWS_CLASSES__SYSTEMTRAYICON_H
#define WINDOWS_CLASSES__SYSTEMTRAYICON_H

#include <string>
#include <windows.h>
#include <shellapi.h>

#ifndef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WIN10
#endif

//if (NNOTIFYICON_VERSION or 0) uCallbackMessage = 32-bit number in wParam
//if (NNOTIFYICON_VERSION_4   ) uCallbackMessage = 16-bit number in HIWORD(lParam)

class SystemTrayIcon
{
	public:
		enum BALLOON_ICON_TYPE
		{
			BIT_NONE			= 100,
			BIT_INFO			= 101,
			BIT_WARNING			= 102,
			BIT_ERROR			= 103,
			BIT_USER_DEFINED	= 104
		};

		SystemTrayIcon();
		~SystemTrayIcon();

		bool Create(const std::wstring &	Tip,
					HWND					hWndParent,
					const GUID &			Guid,
					UINT					IdCallback,
					HICON					hIcon,
					bool					bSharedIcon,
					bool					bHidden);

		operator bool();

		void Show();
		void Hide();
		void Focus();
		void Delete();
		void Update(	HICON					hIcon,
						const std::wstring &	Tip);
		void Balloon(	const std::wstring &	Title,
						const std::wstring &	Message,
						HICON					hBalloonIcon,
						BALLOON_ICON_TYPE		IconType,
						UINT					Timeout,	// In milliseconds.
						bool					bSound,
						bool					bLargeIcon,
						bool					bRespectQuiteTime);

		bool bLastResult;

	private:
		bool bInitialized;
		NOTIFYICONDATAW NotifyIconData;

		static const size_t MAX_TITLE	= 63;
		static const size_t MAX_MESSAGE	= 255;
		static const size_t MAX_TIP		= 127;

		void Update();
};

#endif	// WINDOWS_CLASSES__SYSTEMTRAYICON_H

// {7F0F02E3-479B-4A09-BF99-D339E93A8B22}
//static const GUID <<name>> = 
//{ 0x7f0f02e3, 0x479b, 0x4a09, { 0xbf, 0x99, 0xd3, 0x39, 0xe9, 0x3a, 0x8b, 0x22 } };
