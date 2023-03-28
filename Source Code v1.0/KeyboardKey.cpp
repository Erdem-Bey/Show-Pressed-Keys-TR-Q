#include "KeyboardKey.h"



KeyboardKey::KeyboardKey(	const std::wstring	& Name,
							const KeySize		& Size,
							const KeyLocation	& Location,
							const DWORD			& VirtualKeyCode)
							//const DWORD		& HardwareScanCode)
	:	Name				(Name)
	,	Size				(Size)
	,	Location			(Location)
	,	VirtualKeyCode		(VirtualKeyCode)
	//,	HardwareScanCode	(HardwareScanCode)
	,	Pressed				(false)
	,	Graphics			()
{
}
