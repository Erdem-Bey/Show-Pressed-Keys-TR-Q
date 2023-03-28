#pragma once
#ifndef HANCOPY__GUI_H
#define HANCOPY__GUI_H

#include <string>
#include <Windows.h>

#include "..\Gui\MainWindow\G_Main.h"


class Gui
{
	public:
		Gui()				= delete;
		Gui(const Gui &)	= delete;
		
		~Gui();

		
		static HINSTANCE		hInstance;
		
		static WindowMain		MainWnd;
		//static WindowSettings	SettWnd;
		//static WindowUsage	UsgeWnd;
		//static WindowAbout	AbutWnd;


	private:

};

#endif // HANCOPY__GUI_H

