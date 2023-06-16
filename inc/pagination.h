#ifndef _PAGINATION_H_
#define _PAGINATION_H_

#include <string>
#include "json.hpp"
#include "stringutil.h"

using json = nlohmann::json;

class PaginationType
{
public:
  PaginationType() { m_cursor = ""; };

  PaginationType(json paginationJson);

  ~PaginationType() {};

  void SetCursor(std::string cursor) { m_cursor = cursor; }
  std::string GetCursor() { return m_cursor; }

  bool ContinuePaging() { return !stringutil::iequals(m_cursor, ""); }

private:
  std::string m_cursor;
};

#endif