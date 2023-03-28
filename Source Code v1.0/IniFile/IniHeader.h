#ifndef INI_HEADER_H
#define INI_HEADER_H

#include "IniLine.h"

#include <memory>
#include <vector>
#include <iostream>

#include "IniException.h"

class IniHeader : public IniLine
{
	public:
		IniHeader()							= delete;
		IniHeader(IniHeader &)				= delete;
		IniHeader(IniHeader &&)				= delete;
		IniHeader & operator=(IniHeader &)	= delete;
		IniHeader & operator=(IniHeader &&)	= delete;

		IniHeader(	const std::wstring & InitialSpace,
					const std::wstring & SpaceBeforeHeader,
					const std::wstring & Header,
					const std::wstring & SpaceAfterHeader,
					const std::wstring & FinalSpace,
					bool bIsInitial = false);

		~IniHeader();

		const bool bIsInitial;

		void Print(std::wostream & os) const;
		void AddLine(std::unique_ptr<IniLine> && upLine);
		const	std::wstring & GetName() const;
				std::wstring & GetValue(const std::wstring & Key)		throw(IniException);
		const	std::wstring & GetValue(const std::wstring & Key) const	throw(IniException);

	//private:
		const std::wstring InitialSpace;
		const std::wstring SpaceBeforeHeader;
		const std::wstring Header;
		const std::wstring SpaceAfterHeader;
		const std::wstring FinalSpace;
		
		std::vector<std::unique_ptr<IniLine>> Lines;
		
};

#endif // INI_HEADER_H
