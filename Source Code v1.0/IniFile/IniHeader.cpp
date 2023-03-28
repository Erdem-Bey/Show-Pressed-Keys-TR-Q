#include "IniHeader.h"

#include <memory>

#include "IniFile.h"
#include "IniEntry.h"

IniHeader::IniHeader(	const std::wstring & InitialSpace,
						const std::wstring & SpaceBeforeHeader,
						const std::wstring & Header,
						const std::wstring & SpaceAfterHeader,
						const std::wstring & FinalSpace,
						bool bIsInitial /*= false*/)
	:	InitialSpace		(InitialSpace),
		SpaceBeforeHeader	(SpaceBeforeHeader),
		Header				(Header),
		SpaceAfterHeader	(SpaceAfterHeader),
		FinalSpace			(FinalSpace),
		bIsInitial			(bIsInitial),
		IniLine				(IniLine::TYPE::HEADER)
{
}

IniHeader::~IniHeader()
{
}

void IniHeader::Print(std::wostream & os) const
{
	// Print the header.
	if (!bIsInitial)
	{
		os << InitialSpace << IniFile::HEADER_OPEN << SpaceBeforeHeader << Header << SpaceAfterHeader << IniFile::HEADER_CLOSE << FinalSpace << std::endl;
	}

	// Print the entries.
	for (std::vector<std::unique_ptr<IniLine>>::const_iterator cit=Lines.cbegin(); cit!=Lines.cend(); ++cit)
	{
		os << **cit << std::endl;
	}/**/
}

void IniHeader::AddLine(std::unique_ptr<IniLine> && upLine)
{
	Lines.push_back(std::move(upLine));
}

const std::wstring & IniHeader::GetName() const
{
	return this->Header;
}

std::wstring & IniHeader::GetValue(const std::wstring & Key) throw(IniException)
{
	for (std::vector<std::unique_ptr<IniLine>>::iterator it=Lines.begin(); it!=Lines.end(); ++it)
	{
		if ((*it)->Type != IniLine::TYPE::ENTRY)	// Skip garbage lines.
		{
			continue;
		}
		IniEntry & Entry = *(dynamic_cast<IniEntry*>(it->get()));
		//if ((dynamic_cast<IniEntry*>(cit->get()))->GetKey() == Key)
		if (Entry.GetKey() == Key)
		{
			return Entry.GetValue();
		}
	}
	throw(IniException(	static_cast<unsigned char>(1),
						L"The key is not found.",
						L"IniHeader",
						L"GetValue",
						std::wstring(__WFILE__),
						static_cast<unsigned int>(__LINE__)));
}

const std::wstring & IniHeader::GetValue(const std::wstring & Key) const throw(IniException)
{
	for (std::vector<std::unique_ptr<IniLine>>::const_iterator cit=Lines.cbegin(); cit!=Lines.cend(); ++cit)
	{
		if ((*cit)->Type != IniLine::TYPE::ENTRY)	// Skip garbage lines.
		{
			continue;
		}
		const IniEntry & Entry = *(dynamic_cast<IniEntry*>(cit->get()));
		//if ((dynamic_cast<IniEntry*>(cit->get()))->GetKey() == Key)
		if (Entry.GetKey() == Key)
		{
			return Entry.GetValue();
		}
	}
	throw(IniException(	static_cast<unsigned char>(1),
						L"The given key is not found.",
						L"IniHeader",
						L"GetValue",
						std::wstring(__WFILE__),
						static_cast<unsigned int>(__LINE__)));
}
