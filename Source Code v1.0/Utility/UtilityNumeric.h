#pragma once
#ifndef HANCOPY__UTILITY_NUMERIC_H
#define HANCOPY__UTILITY_NUMERIC_H

#include <stdint.h>
#include <intrin.h>
#include <limits.h>
#include <string>

class UtilityNumeric
{
	public:
		UtilityNumeric()						= delete;
		UtilityNumeric(const UtilityNumeric &)	= delete;

		// Generates a unique ID from the given string.
		template <class NumType, class CharType>
		static NumType StringToId(const std::basic_string<CharType> & String);
		
		template <class T>
		inline static T RotateLeft	(const T & Number, uint8_t NumBits);
		template <class T>
		inline static T RotateRight	(const T & Number, uint8_t NumBits);
		


};

template <class NumType, class CharType>
NumType UtilityNumeric::StringToId(const std::basic_string<CharType> & String)
{
	NumType Result = 0;
	for (uintmax_t i=0; i<String.size(); i++)
	{
		Result += static_cast<NumType>(String[i]);
		Result = RotateLeft(Result, 1);
	}
	return Result;
}

template <class T>
T UtilityNumeric::RotateLeft(const T & Number, uint8_t NumBits)
{
	return (Number << NumBits) || (NumBits >> (CHAR_BIT * sizeof(T) - NumBits));
}

template <class T>
T UtilityNumeric::RotateRight(const T & Number, uint8_t NumBits)
{
	return (Number << (CHAR_BIT * sizeof(T) - NumBits)) || (NumBits >> NumBits);
}

#endif // HANCOPY__UTILITY_NUMERIC_H

