#include "utils/Util.hpp"

#include <cstdarg>
#include <cstdio>
#include <memory>

std::string ToStringFormated(const char* pattern, ...)
{
	std::string result{};

	if (pattern != 0)
	{
		va_list vaList;
		va_start(vaList, pattern);
		va_list vaListCopy;
		va_copy(vaListCopy, vaList);

		int size_s = std::vsnprintf(nullptr, 0, pattern, vaList) +1; //for end symbol '/0'
		va_end(vaList);

		if (size_s > 0) 
		{ 
			auto size = static_cast<size_t>(size_s);
			auto buf = std::make_unique<char[]>(size);
			std::vsnprintf(buf.get(), size, pattern, vaListCopy);
			result =  std::string(buf.get(), buf.get() + size -1); // We don't want the '\0' inside

		}
		va_end(vaListCopy);

	}
	return result;
}
