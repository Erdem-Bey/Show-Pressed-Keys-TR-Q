#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <Windows.h>
#include <gdiplus.h>

class LinePath
{
	public:
		LinePath();
		~LinePath();

		void Update();
		
		//HWND							hWnd;
		Gdiplus::Graphics			*	pGraphics;
		Gdiplus::REAL					Thickness;
		Gdiplus::Color					Color;
		std::vector<Gdiplus::PointF>	Vertexes;

};

