#ifndef CHAR_TRAITS__CASE_INSENSITIVE_H
#define CHAR_TRAITS__CASE_INSENSITIVE_H

#include <string>
#include <iostream>
#include <cctype>

template <class CharType>
class CharTraits_CaseInsensitive : public std::char_traits<CharType>
{
	public:
		static bool eq(CharType c1, CharType c2)
		{
			return std::toupper(c1) == std::toupper(c2);
		}

		static bool lt(CharType c1, CharType c2)
		{
			return std::toupper(c1) <  std::toupper(c2);
		}

		static int compare(const CharType * s1, const CharType * s2, size_t n)
		{
			while ( n-- != 0 )
			{
				if (std::toupper(*s1) < std::toupper(*s2)) return -1;
				if (std::toupper(*s1) > std::toupper(*s2)) return +1;
				++s1;
				++s2;
			}
			return 0;
		}

		static const CharType * find(const CharType * s, int n, CharType a)
		{
			const auto ua (std::toupper(a));
			while (n-- != 0) 
			{
				if (std::toupper(*s) == ua)
				{
					return s;
				}
				s++;
			}
			return nullptr;
		}
};

#endif	// CHAR_TRAITS__CASE_INSENSITIVE_H
