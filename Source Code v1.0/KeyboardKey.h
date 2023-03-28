#pragma once

#include <Windows.h>
#include <string>

#include "KeySize.h"
#include "KeyLocation.h"

#include "Gui\Graphics\TextBlock.h"


class KeyboardKey
{
	public:
		KeyboardKey(	const	std::wstring	& Name,
						const	KeySize			& Size,
						const	KeyLocation		& Location,
						const	DWORD			& VirtualKeyCode
						//const	DWORD			& HardwareScanCode
																	);


		const	std::wstring	Name;
		const	KeySize			Size;
		const	KeyLocation		Location;
		const	DWORD			VirtualKeyCode;
		//const	DWORD			HardwareScanCode;

		bool					Pressed;

		TextBlock				Graphics;

};

