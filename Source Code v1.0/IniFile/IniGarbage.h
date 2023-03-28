#pragma once

#include "IniLine.h"

#include <string>


class IniGarbage : public IniLine
{
	public:
		IniGarbage()							= delete;
		IniGarbage(IniGarbage &)				= delete;
		IniGarbage(IniGarbage &&)				= delete;
		IniGarbage & operator=(IniGarbage &)	= delete;
		IniGarbage & operator=(IniGarbage &&)	= delete;

		IniGarbage(const	std::wstring &		Line);
		IniGarbage(			std::wstring &&		Line);

		~IniGarbage();

		void Print(std::wostream & os) const;

	private:
		std::wstring Line;
};

