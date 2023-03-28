#include "IniEntry.h"

#include "IniFile.h"

IniEntry::IniEntry(	const std::wstring & SpaceBeforeKey,
					const std::wstring & Key,
					const std::wstring & SpaceAfterKey,
					const std::wstring & SpaceBeforeValue,
					const std::wstring & Value,
					const std::wstring & SpaceAfterValue)
	:	SpaceBeforeKey		(SpaceBeforeKey),
		Key					(Key),
		SpaceAfterKey		(SpaceAfterKey),
		SpaceBeforeValue	(SpaceBeforeValue),
		Value				(Value),
		SpaceAfterValue		(SpaceAfterValue),
		IniLine				(IniLine::TYPE::ENTRY)
{

}

IniEntry::~IniEntry()
{
}

void IniEntry::Print(std::wostream & os) const
{
	os << SpaceBeforeKey << Key << SpaceAfterKey << IniFile::EQUALS << SpaceBeforeValue << Value << SpaceAfterValue;
}

const std::wstring & IniEntry::GetKey() const
{
	return this->Key;
}

std::wstring & IniEntry::GetValue()
{
	return this->Value;
}

const std::wstring & IniEntry::GetValue() const
{
	return this->Value;
}
