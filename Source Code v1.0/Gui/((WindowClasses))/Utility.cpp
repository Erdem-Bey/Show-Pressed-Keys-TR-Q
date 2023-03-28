#include "Utility.h"

std::wstring Utility::MESSAGE_BOX_TITLE = std::wstring(L"Debug Message");
UINT         Utility::MESSAGE_BOX_ICON  = MB_ICONINFORMATION;

void Utility::DebugMessage(const std::wstring & Message)
{
	MessageBoxW(NULL, Message.c_str(), MESSAGE_BOX_TITLE.c_str(), MESSAGE_BOX_ICON);
}
