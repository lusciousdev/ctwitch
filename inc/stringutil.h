#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_

#include <string>
#include <algorithm>

namespace stringutil 
{
  static bool iequals(const std::string& lhs, const std::string& rhs)
  {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](char a, char b) { return tolower(a) == tolower(b); });
  };
}

#endif