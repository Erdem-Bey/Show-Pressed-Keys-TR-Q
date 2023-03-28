#ifndef INI_FILE_H
#define INI_FILE_H

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "IniHeader.h"
#include "IniEntry.h"
#include "IniGarbage.h"
#include "IniException.h"

class IniFile
{
	public:
		IniFile()						= delete;
		IniFile(IniFile &)				= delete;
		IniFile(IniFile &&)				= delete;
		IniFile & operator=(IniFile &)	= delete;
		IniFile & operator=(IniFile &&)	= delete;

		IniFile(const	std::wstring &	FileLocation) throw(IniException);
		IniFile(		std::wstring &&	FileLocation) throw(IniException);

		~IniFile();

		static const std::wstring	WHITE_SPACE_CHARACTERS;
		static const wchar_t		HEADER_OPEN;
		static const wchar_t		HEADER_CLOSE;
		static const wchar_t		EQUALS;
		static const wchar_t		QUOTE;

		friend std::wostream & operator<<(std::wostream & os, const IniFile & file);

		void SaveToFile() const;

		int64_t			GetValueInteger	(const std::wstring & Header, const std::wstring & Key) const throw(IniException);
		long double		GetValueFloat	(const std::wstring & Header, const std::wstring & Key) const throw(IniException);
		std::wstring	GetValueString	(const std::wstring & Header, const std::wstring & Key) const throw(IniException);

		void			AddBlankLine	(const std::wstring & Header)	throw(IniException);
		void			AddBlankLine	();

		template <class T>
		void			SetValue		(const std::wstring & Header, const std::wstring & Key, const T &				Value) throw(IniException);
		//void			SetValue		(const std::wstring & Header, const std::wstring & Key, const std::wstring &	Value) throw(IniException);
		//void			SetValue		(const std::wstring & Header, const std::wstring & Key, int64_t					Value) throw(IniException);
		//void			SetValue		(const std::wstring & Header, const std::wstring & Key, long double				Value) throw(IniException);

	private:
		const std::wstring FileLocation;

		std::vector<std::unique_ptr<IniHeader>> Headers;

				IniHeader & FindHeader(const std::wstring & Header)			throw(IniException);
		const	IniHeader & FindHeader(const std::wstring & Header) const	throw(IniException);

		void ImportFromFile		(const std::wstring & IniFileLocation)		throw(IniException);
		void ParseAndAddLine	(const std::wstring & Line);

		static std::wstring	StripQuotes		(const std::wstring & Text);
		static std::wstring	GetInitialSpace	(const std::wstring & Text);
		static std::wstring	GetEndingSpace	(const std::wstring & Text);
		static std::wstring	TrimSpaces		(const std::wstring & Text);
		static void			TestTrimming	();

		static int64_t		StringToInteger	(const std::wstring & String);
		static long double	StringToFloat	(const std::wstring & String);
		template <class T>
		static std::wstring	NumericToString	(const T & NumericValue);

		
};

template <class T>
std::wstring IniFile::NumericToString(const T & NumericValue)
{
	std::wostringstream oss;
	oss << NumericValue;
	return oss.str();
}

template <class T>
//void IniFile::SetValue(const std::wstring & HeaderName, const std::wstring & Key, const std::wstring & Value) throw(IniException)
void IniFile::SetValue(const std::wstring & HeaderName, const std::wstring & Key, const T & Value) throw(IniException)
{
	const std::wstring StringValue = NumericToString(Value);
	try
	{
		IniHeader & Header = FindHeader(HeaderName);
		try
		{
			std::wstring & IniValue = Header.GetValue(Key);
			IniValue = StringValue;
			return;				// The header and key existed. The value changed.
		}
		catch (IniException & e)
		{
			switch (e.ErrorCode)
			{
				case 1:
					Header.AddLine(std::unique_ptr<IniLine>(new IniEntry(L"", Key, L" ", L" ", StringValue, L"")));
					return;		// The header existed, but the key didn't. The key is created, the value is assigned to it.
					break;
				default:
					throw(IniException(	static_cast<unsigned char>(100),
										L"Unknown error!",
										L"IniFile",
										L"SetValue",
										std::wstring(__WFILE__),
										static_cast<unsigned int>(__LINE__)));
					break;
			}
		}
	}
	catch (IniException & e)
	{
		switch (e.ErrorCode)
		{
			case 1:
				Headers.emplace_back(new IniHeader(L"", L"", HeaderName, L"", L""));
				Headers.back()->AddLine(std::unique_ptr<IniLine>(new IniEntry(L"", Key, L" ", L" ", StringValue, L"")));
				return;			// The header didn't exist. The header is created, and the key-value pair is added in it.
				break;
			default:
				throw(IniException(	static_cast<unsigned char>(200),
									L"Unknown error!",
									L"IniFile",
									L"SetValue",
									std::wstring(__WFILE__),
									static_cast<unsigned int>(__LINE__)));
				break;
		}
	}
}

#endif // INI_FILE_H
