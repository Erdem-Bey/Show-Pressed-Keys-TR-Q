#include "IniLine.h"


IniLine::IniLine(IniLine::TYPE Type)
	:	Type(Type)
{
}

IniLine::~IniLine()
{
}

std::wostream & operator<<(std::wostream & os, const IniLine & line)
{
	line.Print(os);
	return os;
}
