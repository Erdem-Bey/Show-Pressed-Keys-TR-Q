#include "IniGarbage.h"

#include <utility>

IniGarbage::IniGarbage(const std::wstring & Line)
	:	Line	(Line),
		IniLine	(IniLine::TYPE::GARBAGE)
{
}

IniGarbage::IniGarbage(std::wstring && LineString)
	:	Line	(std::move(LineString)),
		IniLine	(IniLine::TYPE::GARBAGE)
{
}

IniGarbage::~IniGarbage()
{
}

void IniGarbage::Print(std::wostream & os) const
{
	os << Line;
}
