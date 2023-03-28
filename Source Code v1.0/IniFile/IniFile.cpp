#include "IniFile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <locale>
#include <codecvt>

#include "IniHeader.h"
#include "IniEntry.h"
#include "IniGarbage.h"

const std::wstring	IniFile::WHITE_SPACE_CHARACTERS	(L" \t");
const wchar_t		IniFile::HEADER_OPEN			(L'[');
const wchar_t		IniFile::HEADER_CLOSE			(L']');
const wchar_t		IniFile::EQUALS					(L'=');
const wchar_t		IniFile::QUOTE					(L'\"');

IniFile::IniFile(const std::wstring & FileLocation) throw(IniException)
	: FileLocation(FileLocation)
{
	// Insert an initial dummy header for any possible entries that will show up before an actual header.
	Headers.emplace_back(new IniHeader(L"", L"", L"", L"", L"", true));
	try
	{
		ImportFromFile(FileLocation);
	}
	catch (IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				throw(IniException(	static_cast<unsigned char>(1),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			case 2:
				throw(IniException(	static_cast<unsigned char>(2),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(100),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

IniFile::IniFile(std::wstring && FileLocation) throw(IniException)
	: FileLocation(std::move(FileLocation))
{
	Headers.emplace_back(new IniHeader(L"", L"", L"", L"", L"", true));
	try
	{
		ImportFromFile(this->FileLocation);
	}
	catch (IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				throw(IniException(	static_cast<unsigned char>(1),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			case 2:
				throw(IniException(	static_cast<unsigned char>(2),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(100),
									e.ErrorMessage,
									L"IniFile",
									L"IniFile",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

IniFile::~IniFile()
{
}

IniHeader & IniFile::FindHeader(const std::wstring & Header) throw(IniException)
{
	for (std::vector<std::unique_ptr<IniHeader>>::iterator it=Headers.begin(); it!=Headers.end(); ++it)
	{
		if ((**it).GetName() == Header)
		{
			return **it;
		}
	}
	throw(IniException(	static_cast<unsigned char>(1),
						L"Header is not found.",
						L"IniFile",
						L"FindHeader",
						std::wstring(__WFILE__),
						static_cast<unsigned int>(__LINE__)));
}

const IniHeader & IniFile::FindHeader(const std::wstring & Header) const throw(IniException)
{
	for (std::vector<std::unique_ptr<IniHeader>>::const_iterator cit=Headers.cbegin(); cit!=Headers.cend(); ++cit)
	{
		if ((**cit).GetName() == Header)
		{
			return **cit;
		}
	}
	throw(IniException(	static_cast<unsigned char>(1),
						L"Header is not found.",
						L"IniFile",
						L"FindHeader",
						std::wstring(__WFILE__),
						static_cast<unsigned int>(__LINE__)));
}

void IniFile::ImportFromFile(const std::wstring & IniFileLocation) throw(IniException)
{
	// Adam gibi çalışan hâli.
	//std::wifstream FileStream(IniFileLocation, std::wifstream::in);

	// Yeni eklediğim kod.
	std::wifstream FileStream(IniFileLocation);
	FileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	/*std::wostringstream wss;
	wss << FileStream.rdbuf();
	std::wstring Wstr(wss.str());
	std::wcout.fill(L'0');
	std::wcout << std::uppercase;
	for (size_t i=0; i<Wstr.length(); i++)
	{
		std::wcout << "[" << std::setw(2) << std::dec << i << "]\t0x" << std::setw(4) << std::hex << static_cast<unsigned int>(Wstr[i]) << std::endl;
	}*/

	if (!FileStream.good())
	{
		if (FileStream.bad())
		{
			throw(IniException(	static_cast<unsigned char>(1),
								L"Read/writing error on i/o operation.",
								L"IniFile",
								L"ImportFromFile",
								std::wstring(__WFILE__),
								static_cast<unsigned int>(__LINE__)));
		}
		else if (FileStream.fail())
		{
			throw(IniException(	static_cast<unsigned char>(2),
								L"Logical error on i/o operation.",
								L"IniFile",
								L"ImportFromFile",
								std::wstring(__WFILE__),
								static_cast<unsigned int>(__LINE__)));
		}
		else
		{
			throw(IniException(	static_cast<unsigned char>(100),
								L"Unknown error while opening the file.",
								L"IniFile",
								L"ImportFromFile",
								std::wstring(__WFILE__),
								static_cast<unsigned int>(__LINE__)));
		}
	}

	std::wstring Line;
	while (std::getline(FileStream, Line))
	{
		ParseAndAddLine(Line);
	}

	FileStream.close();
}

void IniFile::ParseAndAddLine(const std::wstring & Line)
{
	size_t FoundLeft, FoundRight;

	/*        FoundLeft                                       FoundRight
	              ?                                               ?
	              [                   HeaderText                  ]         // Header comment.
	|____________| |_________________||________||________________| |_________________________|
	 InitialSpace   SpaceBeforeHeader   Header   SpaceAfterHeader           FinalSpace		*/ 
	FoundLeft = Line.find(HEADER_OPEN);
	if (FoundLeft != std::wstring::npos)
	{
		FoundRight = Line.find(HEADER_CLOSE, FoundLeft);
		if (FoundRight != std::wstring::npos)
		{
			std::wstring SpaceInitial;
			std::wstring SpaceBeforeHeader;
			std::wstring Header;
			std::wstring SpaceAfterHeader;
			std::wstring SpaceFinal;

			SpaceInitial			= Line.substr(0, FoundLeft);

			std::wstring RawHeader;
			try
			{
				RawHeader			= Line.substr(FoundLeft + 1, FoundRight - FoundLeft - 1);
				SpaceBeforeHeader	= GetInitialSpace	(RawHeader);
				Header				= TrimSpaces		(RawHeader);
				SpaceAfterHeader	= GetEndingSpace	(RawHeader);
			}
			catch (std::out_of_range & e)
			{
				SpaceBeforeHeader	= std::wstring();
				Header				= std::wstring();
				SpaceAfterHeader	= std::wstring();
			}

			try
			{
				SpaceFinal			= Line.substr(FoundRight + 1, std::wstring::npos);
			}
			catch (std::out_of_range & e)
			{
				SpaceFinal			= std::wstring();
			}

			Headers.emplace_back(new IniHeader(SpaceInitial, SpaceBeforeHeader, Header, SpaceAfterHeader, SpaceFinal));

			return;
		}
	}

	/*      FoundKey1   FoundKey2    FoundEquals     FoundValue1     FoundValue2
	              ?       ?               ?                  ?         ?
	              KeyString               =                  ValueString         // Entry comment.
	|____________||_______||_____________| |________________||_________||________________________|
	 SpaceInitial    Key      SpaceLeft        SpaceRight       Value           SpaceFinal      */
	size_t FoundKey1, FoundKey2, FoundEquals, FoundValue1, FoundValue2;
	FoundEquals = Line.find(IniFile::EQUALS);
	if ((FoundEquals != std::wstring::npos) && (FoundEquals != 0))
	{
		FoundKey1	= Line.find_first_not_of(WHITE_SPACE_CHARACTERS);
		if (FoundKey1 != FoundEquals)
		{
			FoundKey2	= Line.find_last_not_of	(WHITE_SPACE_CHARACTERS, FoundEquals - 1);
			FoundValue1	= Line.find_first_not_of(WHITE_SPACE_CHARACTERS, FoundEquals + 1);
			if (FoundValue1 != std::wstring::npos)
			{
				if (Line[FoundValue1] == QUOTE)
				{
					FoundValue2 = Line.find_first_of(QUOTE, FoundValue1 + 1);
					if (FoundValue2 == std::wstring::npos)
					{
						FoundValue2 = Line.find_first_of(WHITE_SPACE_CHARACTERS, FoundValue1);
						if (FoundValue2 == std::wstring::npos)
						{
							FoundValue2 = Line.length();
						}
						else
						{
							FoundValue2--;
						}
					}
				}
				else
				{
					FoundValue2 = Line.find_first_of(WHITE_SPACE_CHARACTERS, FoundValue1);
					if (FoundValue2 == std::wstring::npos)
					{
						FoundValue2 = Line.length();
					}
					else
					{
						FoundValue2--;
					}
				}

				std::wstring SpaceInitial	= Line.substr(0, FoundKey1);
				std::wstring Key			= Line.substr(FoundKey1, FoundKey2 - FoundKey1 + 1);
				std::wstring SpaceLeft		= Line.substr(FoundKey2 + 1, FoundEquals - FoundKey2 - 1);
				std::wstring SpaceRight		= Line.substr(FoundEquals + 1, FoundValue1 - FoundEquals - 1);
				std::wstring Value			= Line.substr(FoundValue1, FoundValue2 - FoundValue1 + 1);
				std::wstring SpaceFinal;
				try
				{
					SpaceFinal = Line.substr(FoundValue2 + 1, std::wstring::npos);
				}
				catch (std::out_of_range & e)
				{
					SpaceFinal = L"";
				}

				Headers.back()->AddLine(std::unique_ptr<IniLine>(new IniEntry(SpaceInitial, Key, SpaceLeft, SpaceRight, Value, SpaceFinal)));

				return;
			}
		}
	}
	
	Headers.back()->AddLine(std::unique_ptr<IniLine>(new IniGarbage(Line)));
}

std::wostream & operator<<(std::wostream & os, const IniFile & file)
{
	for (std::vector<std::unique_ptr<IniHeader>>::const_iterator cit=file.Headers.cbegin(); cit!=file.Headers.cend(); ++cit)
	{
		os << **cit;
	}/**/
	return os;
}

void IniFile::SaveToFile() const
{
	// Yeni eklediğim kod.
	std::wofstream FileStream;
	FileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	FileStream.open(FileLocation);
	FileStream << *this;
	FileStream.close();


	return;

	// Doğru düzgün çalışan hâli.
	//std::wofstream FileStream(FileLocation, std::ios_base::out | std::ios_base::trunc);
	//FileStream << *this;
	//FileStream.close();
}

int64_t IniFile::GetValueInteger(const std::wstring & Header, const std::wstring & Key) const throw(IniException)
{
	try
	{
		return StringToInteger(StripQuotes(GetValueString(Header, Key)));
	}
	catch (const IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				throw(IniException(	static_cast<unsigned char>(1),
									L"The given key is not found.",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			case 2:
				throw(IniException(	static_cast<unsigned char>(2),
									L"The given header is not found.",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(100),
									L"Unknown error occurred!",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

long double IniFile::GetValueFloat(const std::wstring & Header, const std::wstring & Key) const throw(IniException)
{
	try
	{
		return StringToFloat(StripQuotes(GetValueString(Header, Key)));
	}
	catch (const IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				throw(IniException(	static_cast<unsigned char>(1),
									L"The given key is not found.",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			case 2:
				throw(IniException(	static_cast<unsigned char>(2),
									L"The given header is not found.",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(100),
									L"Unknown error occurred!",
									L"IniFile",
									L"GetValueString",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

std::wstring IniFile::GetValueString(const std::wstring & Header, const std::wstring & Key) const throw(IniException)
{
	for (std::vector<std::unique_ptr<IniHeader>>::const_iterator cit=Headers.cbegin(); cit!=Headers.cend(); ++cit)
	{
		if ((*cit)->GetName() == Header)
		{
			try
			{
				return (*cit)->GetValue(Key);
			}
			catch (const IniException & e)
			{
				switch (e.ErrorCode)
				{
					case 1:
						throw(IniException(	static_cast<unsigned char>(1),
											L"The given key is not found.",
											L"IniFile",
											L"GetValueString",
											std::wstring(__WFILE__),
											static_cast<unsigned int>(__LINE__)));
						break;
					default:
						throw(IniException(	static_cast<unsigned char>(100),
											L"Unknown error occurred!",
											L"IniFile",
											L"GetValueString",
											std::wstring(__WFILE__),
											static_cast<unsigned int>(__LINE__)));
						break;
				}
			}
		}
	}
	throw(IniException(	static_cast<unsigned char>(2),
						L"The given header is not found.",
						L"IniFile",
						L"GetValueString",
						std::wstring(__WFILE__),
						static_cast<unsigned int>(__LINE__)));
}

void IniFile::AddBlankLine(const std::wstring & HeaderName) throw(IniException)
{
	try
	{
		IniHeader & Header = FindHeader(HeaderName);
		Header.AddLine(std::unique_ptr<IniLine>(new IniGarbage(L"")));
	}
	catch (IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				throw(IniException(	static_cast<unsigned char>(1),
									L"The header is not found.",
									L"IniFile",
									L"AddBlankLine",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(100),
									L"Unknown error occurred!",
									L"IniFile",
									L"AddBlankLine",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

void IniFile::AddBlankLine()
{
	Headers.back()->AddLine(std::unique_ptr<IniLine>(new IniGarbage(L"")));
}

/*void IniFile::SetValue(const std::wstring & Header, const std::wstring & Key, int64_t Value) throw(IniException)
{
	try
	{
		SetValue(Header, Key, NumericToString(Value));
	}
	catch (IniException & e)
	{
		throw(e);
	}
}

void IniFile::SetValue(const std::wstring & Header, const std::wstring & Key, long double Value) throw(IniException)
{
	try
	{
		SetValue(Header, Key, NumericToString(Value));
	}
	catch (IniException & e)
	{
		throw(e);
	}
}*/

std::wstring IniFile::StripQuotes(const std::wstring & Text)
{
	const size_t LENGTH = Text.length();
	if (LENGTH >= 2)
	{
		if ((Text.front() == QUOTE) && (Text.back() == QUOTE))
		{
			return Text.substr(1, LENGTH - 2);
		}
	}
	return Text;
}

std::wstring IniFile::GetInitialSpace(const std::wstring & Text)
{
	return Text.substr(0, Text.find_first_not_of(IniFile::WHITE_SPACE_CHARACTERS));
}

std::wstring IniFile::GetEndingSpace(const std::wstring & Text)
{
	size_t Pos = Text.find_last_not_of(IniFile::WHITE_SPACE_CHARACTERS) + 1;
	if ((Pos == std::wstring::npos) || (Pos == 0))
	{
		Pos = Text.length();	// Make it return empty string.
	}
	return Text.substr(Pos, std::wstring::npos);
	/*try
	{
		return Text.substr(Pos, std::wstring::npos);
	}
	catch (std::out_of_range & e)
	{
		return std::wstring();
	}*/
}

std::wstring IniFile::TrimSpaces(const std::wstring & Text)
{
	size_t First	= Text.find_first_not_of(	IniFile::WHITE_SPACE_CHARACTERS);
	size_t Last		= Text.find_last_not_of(	IniFile::WHITE_SPACE_CHARACTERS);
	if ((First == std::wstring::npos) || (Last == std::wstring::npos))
	{
		return std::wstring();
	}
	else
	{
		return Text.substr(First, (Last - First + 1));
	}
}

void IniFile::TestTrimming()
{
	std::wstring Str1(L"");
	std::wstring Str2(L" ");
	std::wstring Str3(L"		xyz		 ");
	std::wstring Str4(L"		123");
	std::wstring Str5(L"!#$			");

	std::wcout << L"-" << Str1 << L"-" << std::endl;
	std::wcout << L"-" << Str2 << L"-" << std::endl;
	std::wcout << L"-" << Str3 << L"-" << std::endl;
	std::wcout << L"-" << Str4 << L"-" << std::endl;
	std::wcout << L"-" << Str5 << L"-" << std::endl << std::endl;

	std::wcout << L"-" << IniFile::TrimSpaces(Str1) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::TrimSpaces(Str2) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::TrimSpaces(Str3) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::TrimSpaces(Str4) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::TrimSpaces(Str5) << L"-" << std::endl << std::endl;

	std::wcout << L"-" << IniFile::GetInitialSpace(Str1) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str2) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str3) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str4) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str5) << L"-" << std::endl << std::endl;

	std::wcout << L"-" << IniFile::GetEndingSpace(Str1) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetEndingSpace(Str2) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetEndingSpace(Str3) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetEndingSpace(Str4) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetEndingSpace(Str5) << L"-" << std::endl << std::endl;

	std::wcout << L"-" << IniFile::GetInitialSpace(Str1) << IniFile::TrimSpaces(Str1) << IniFile::GetEndingSpace(Str1) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str2) << IniFile::TrimSpaces(Str2) << IniFile::GetEndingSpace(Str2) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str3) << IniFile::TrimSpaces(Str3) << IniFile::GetEndingSpace(Str3) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str4) << IniFile::TrimSpaces(Str4) << IniFile::GetEndingSpace(Str4) << L"-" << std::endl;
	std::wcout << L"-" << IniFile::GetInitialSpace(Str5) << IniFile::TrimSpaces(Str5) << IniFile::GetEndingSpace(Str5) << L"-" << std::endl << std::endl;

	std::wcout << L"-" << ((IniFile::GetInitialSpace(Str1) + IniFile::TrimSpaces(Str1) + IniFile::GetEndingSpace(Str1) == Str1) ? L"Same" : L"Different") << L"-" << std::endl;
	std::wcout << L"-" << ((IniFile::GetInitialSpace(Str2) + IniFile::TrimSpaces(Str2) + IniFile::GetEndingSpace(Str2) == Str2) ? L"Same" : L"Different") << L"-" << std::endl;
	std::wcout << L"-" << ((IniFile::GetInitialSpace(Str3) + IniFile::TrimSpaces(Str3) + IniFile::GetEndingSpace(Str3) == Str3) ? L"Same" : L"Different") << L"-" << std::endl;
	std::wcout << L"-" << ((IniFile::GetInitialSpace(Str4) + IniFile::TrimSpaces(Str4) + IniFile::GetEndingSpace(Str4) == Str4) ? L"Same" : L"Different") << L"-" << std::endl;
	std::wcout << L"-" << ((IniFile::GetInitialSpace(Str5) + IniFile::TrimSpaces(Str5) + IniFile::GetEndingSpace(Str5) == Str5) ? L"Same" : L"Different") << L"-" << std::endl << std::endl;
}

int64_t IniFile::StringToInteger(const std::wstring & String)
{
	int64_t Return;
	std::wistringstream iss(String);
	iss >> Return;
	return Return;
}

long double IniFile::StringToFloat(const std::wstring & String)
{
	long double Return;
	std::wistringstream iss(String);
	iss >> Return;
	return Return;
}
