#ifndef INI_EXCEPTION_H
#define INI_EXCEPTION_H

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

#include <string>

class IniException
{
	public:
		IniException()								= delete;
		IniException(IniException &);
		IniException(IniException &&);
		IniException & operator=(IniException &)	= delete;
		IniException & operator=(IniException &&)	= delete;

		IniException(	unsigned char			ErrorCode,
						const std::wstring &	ErrorMessage,
						const std::wstring &	ClassName,
						const std::wstring &	MethodName,
						const std::wstring &	FileName,
						unsigned int			FileLine);

		const unsigned char	ErrorCode;
		const std::wstring	ErrorMessage;
		const std::wstring	ClassName;
		const std::wstring	MethodName;
		const std::wstring	FileName;
		unsigned int		FileLine;

		~IniException();
};

#endif // INI_EXCEPTION_H
