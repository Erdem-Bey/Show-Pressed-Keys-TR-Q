#pragma once

#ifndef HANCOPY__STRING_OPERATIONS_H
#define HANCOPY__STRING_OPERATIONS_H

#include <string>
#include <sstream>
#include <vector>

class StringOperations
{
	public:
		template <class CharType, class CharTraits, class Allocator>
		static std::vector<std::basic_string<CharType, CharTraits, Allocator>> SplitString(	const	std::basic_string<CharType, CharTraits, Allocator>	& String,
																							const	CharType											& Delimiter);
		
		
		
		
};

template <class CharType, class CharTraits, class Allocator>
std::vector<std::basic_string<CharType, CharTraits, Allocator>> StringOperations::SplitString(	const	std::basic_string<CharType, CharTraits, Allocator>	& String,
																								const	CharType											& Delimiter)
{
	std::basic_istringstream<CharType, CharTraits, Allocator> Iss(String);
	std::basic_string<CharType, CharTraits, Allocator> Token;
	std::vector<std::basic_string<CharType, CharTraits, Allocator>> Result;
	while (std::getline(Iss, Token, Delimiter))
	{
		Result.push_back(Token);
	}
	return Result;
}

/*std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}*/


#endif // HANCOPY__STRING_OPERATIONS_H
