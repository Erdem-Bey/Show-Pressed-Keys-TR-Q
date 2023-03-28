#pragma once

#include <cstdint>
#include <string>
#include <Windows.h>
#include <gdiplus.h>

class TextBlock
{
	public:
		TextBlock();
		//TextBlock(const TextBlock &) = delete;
		~TextBlock();

		void Update();
		
		//HWND					hWnd;
		Gdiplus::Graphics	*	pGraphics;
		Gdiplus::REAL			X;
		Gdiplus::REAL			Y;
		Gdiplus::REAL			Width;
		Gdiplus::REAL			Height;
		Gdiplus::Color			BackgroundColor;
		Gdiplus::Color			TextColor;
		Gdiplus::REAL			FrameThickness;
		Gdiplus::Color			FrameColor;
		//Gdiplus::Font			Font;
		Gdiplus::REAL			FontHeight;
		std::wstring			FontFamily;
		std::wstring			Text;

};

