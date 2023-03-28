#pragma once
#ifndef WINDOWS_CLASSES__UTILITY_H
#define WINDOWS_CLASSES__UTILITY_H

#include <string>
#include <Windows.h>

class Utility
{
	public:
		~Utility(){};

		static std::wstring MESSAGE_BOX_TITLE;
		static UINT         MESSAGE_BOX_ICON;

		static void DebugMessage(const std::wstring & Message);
		
		template <class T>
		static std::wstring MakeWString(T Number);
		template <class T>
		static std::wstring MakeWString(const std::wstring & Text, T Number);
		template <class T1, class T2>
		static std::wstring MakeWString(T1 Number1, const std::wstring & Text, T2 Number2);
		template <class T1, class T2>
		static std::wstring MakeWString(const std::wstring & Text1, T1 Number1,
										const std::wstring & Text2, T2 Number2,
										const std::wstring & Text3);
		template <class T1, class T2, class T3>
		static std::wstring MakeWString(T1 Number1, const std::wstring & Text1,
										T2 Number2, const std::wstring & Text2,
										T3 Number3);
		template <class T1, class T2>
		static std::wstring MakeWString(const std::wstring & Text1, T1 Number1,
										const std::wstring & Text2, T2 Number2);


	private:
		Utility(){};
};

template <class T>
std::wstring Utility::MakeWString(T Number)
{
	std::wstringstream ss;//(Number);
	ss << Number;
	return ss.str();
}

template <class T>
std::wstring Utility::MakeWString(const std::wstring & Text, T Number)
{
	std::wstringstream ss;
	ss << Text << Number;
	return ss.str();
}

template <class T1, class T2>
std::wstring Utility::MakeWString(T1 Number1, const std::wstring & Text, T2 Number2)
{
	std::wstringstream ss;
	ss << Number1 << Text << Number2;
	return ss.str();
}

template <class T1, class T2>
std::wstring Utility::MakeWString(	const std::wstring & Text1, T1 Number1,
									const std::wstring & Text2, T2 Number2,
									const std::wstring & Text3)
{
	std::wstringstream ss;
	ss << Text1 << Number1 << Text2 << Number2 << Text3;
	return ss.str();
}

template <class T1, class T2, class T3>
std::wstring Utility::MakeWString(	T1 Number1, const std::wstring & Text1,
									T2 Number2, const std::wstring & Text2,
									T3 Number3 )
{
	std::wstringstream ss;
	ss << Number1 << Text1 << Number2 << Text2 << Number3;
	return ss.str();
}

template <class T1, class T2>
std::wstring Utility::MakeWString(	const std::wstring & Text1, T1 Number1,
									const std::wstring & Text2, T2 Number2)
{
	std::wstringstream ss;
	ss << Text1 << Number1 << Text2 << Number2;
	return ss.str();
}

#endif	// WINDOWS_CLASSES__UTILITY_H
