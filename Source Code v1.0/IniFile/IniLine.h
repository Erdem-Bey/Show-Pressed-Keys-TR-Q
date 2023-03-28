#ifndef INI_LINE_H
#define INI_LINE_H

#include <string>
#include <iostream>

class IniLine
{
	public:
		enum TYPE
		{
			GARBAGE	= 0,
			HEADER	= 1,
			ENTRY	= 2
		};
		const TYPE Type;

		IniLine(IniLine::TYPE Type);
		IniLine()						= delete;
		IniLine(IniLine &)				= delete;
		IniLine(IniLine &&)				= delete;
		IniLine & operator=(IniLine &)	= delete;
		IniLine & operator=(IniLine &&)	= delete;
		~IniLine();

		virtual void Print(std::wostream & os) const = 0;
		friend std::wostream & operator<<(std::wostream & os, const IniLine & line);

};

#endif // INI_LINE_H
