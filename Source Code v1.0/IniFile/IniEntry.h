#ifndef INI_ENTRY_H
#define INI_ENTRY_H

#include "IniLine.h"

#include <string>

class IniEntry : public IniLine
{
	public:
		IniEntry()							= delete;
		IniEntry(IniEntry &)				= delete;
		IniEntry(IniEntry &&)				= delete;
		IniEntry & operator=(IniEntry &)	= delete;
		IniEntry & operator=(IniEntry &&)	= delete;

		IniEntry(	const std::wstring & SpaceBeforeKey,
					const std::wstring & Key,
					const std::wstring & SpaceAfterKey,
					const std::wstring & SpaceBeforeValue,
					const std::wstring & Value,
					const std::wstring & SpaceAfterValue);

		~IniEntry();

		void Print(std::wostream & os)		const;
		const	std::wstring & GetKey()		const;
				std::wstring & GetValue();
		const	std::wstring & GetValue()	const;

	//private:
		const	std::wstring SpaceBeforeKey;
		const	std::wstring Key;
		const	std::wstring SpaceAfterKey;
		const	std::wstring SpaceBeforeValue;
				std::wstring Value;
		const	std::wstring SpaceAfterValue;

};

#endif // INI_ENTRY_H
