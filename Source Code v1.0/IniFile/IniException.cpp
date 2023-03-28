#include "IniException.h"


IniException::IniException(	unsigned char ErrorCode,
							const std::wstring & ErrorMessage,
							const std::wstring & ClassName,
							const std::wstring & MethodName,
							const std::wstring & FileName,
							unsigned int FileLine)
	:	ErrorCode		(ErrorCode),
		ErrorMessage	(ErrorMessage),
		ClassName		(ClassName),
		MethodName		(MethodName),
		FileName		(FileName),
		FileLine		(FileLine)
{
}

IniException::IniException(IniException & Another)
	:	ErrorCode		(std::move(Another.ErrorCode)),
		ErrorMessage	(std::move(Another.ErrorMessage)),
		ClassName		(std::move(Another.ClassName)),
		MethodName		(std::move(Another.MethodName)),
		FileName		(std::move(Another.FileName)),
		FileLine		(std::move(Another.FileLine))
{
}

IniException::IniException(IniException && Another)
	:	ErrorCode		(std::move(Another.ErrorCode)),
		ErrorMessage	(std::move(Another.ErrorMessage)),
		ClassName		(std::move(Another.ClassName)),
		MethodName		(std::move(Another.MethodName)),
		FileName		(std::move(Another.FileName)),
		FileLine		(std::move(Another.FileLine))
{
}

IniException::~IniException()
{
}
