#pragma once
#ifndef WINDOWS_CLASSES__BASEWINDOWCLASS_H
#define WINDOWS_CLASSES__BASEWINDOWCLASS_H

#include <stdint.h>
#include <string>
#include <sstream>
#include <Windows.h>

class BaseWindowClass
{
	public:
		enum ALIGN_SIDE { AS_RIGHT, AS_LEFT, AS_TOP, AS_BOTTOM };
		enum ALIGN_TYPE { AT_RIGHT, AT_TOP, AT_LEFT, AT_BOTTOM, AT_CENTER };

		BaseWindowClass();
		~BaseWindowClass();

		void ProcessMessages();

		HWND hWnd;
		
		void UpdateFontProperty_Weight(const int Weight);
		void UpdateFontProperty_Width(const int Width);
		void UpdateFontProperty_Height(const int Height);
		void ChooseDefaultFont();

		void Enable();
		void Disable();

		bool IsEnabled()	const;
		bool IsDisabled()	const;

		void Show() const;
		void Hide() const;

		bool CheckStyle		(DWORD Style);		// Returns true if the given style
		bool CheckExStyle	(DWORD ExStyle);	// exist in the control.
		void AddStyle		(DWORD NewStyle);
		void AddExStyle		(DWORD NewExStyle);
		void RemoveStyle	(DWORD StyleToBeRemoved);
		void RemoveExStyle	(DWORD ExStyleToBeRemoved);
		void UpdateWindowStyles();

		void SetWindowPosition(int x, int y, int w, int h);
		void SetWindowPosition(const RECT & Rect);
		void Move(int x, int y);
		void Resize(int w, int h);
		void AlignTo(	const BaseWindowClass & ReferenceWindow,
						/*HWND ParentWindow,*/
						ALIGN_SIDE WhichSideToAlign,
						ALIGN_TYPE HowToAlign,
						int SpaceToLeaveBetween);

		RECT			GetLocalCoordinates		()	const;
		POINT			GetTopLeftCoordinates	()	const;
		RECT			GetCornerPoints			()	const;
		int				GetX					()	const;
		int				GetY					()	const;
		int				GetLeft					()	const;
		int				GetRight				()	const;
		int				GetTop					()	const;
		int				GetBottom				()	const;
		int				GetWidth				()	const;
		int				GetHeight				()	const;
		const HWND &	GetHandle				()	const;

		std::wstring	GetText					()	const;
		void			SetText(const std::wstring & Text);

		template <class T>
		T				GetContent				()	const;
		template <class T>
		void			SetContent				(const T & Content);

		//int64_t		GetInteger				()	const;
		//uint64_t		GetUInteger				()	const;
		//double		GetDouble				()	const;

	protected:
		void StorePositionAndSize(int x, int y, int w, int h);
		int x;
		int y;
		int w;
		int h;

};

template <class T>
T BaseWindowClass::GetContent() const
{
	std::wistringstream Wiss(GetText());
	T Content;
	Wiss >> Content;
	return Content;
}

template <class T>
void BaseWindowClass::SetContent(const T & Content)
{
	std::wostringstream Woss;
	Woss << Content;
	SetText(Woss.str());
}

#endif	// WINDOWS_CLASSES__BASEWINDOWCLASS_H
