#include "pagination.h"

#include <iostream>

using namespace ctwitch;

PaginationType::PaginationType(json paginationJson)
{
  m_cursor = "";
  if (paginationJson.contains("cursor"))
    m_cursor = paginationJson["cursor"];
}

json PaginationType::ToJson()
{
  if (stringutil::iequals(m_cursor, ""))
  {
    return json::object();
  }
  else
  {
    return { { "cursor", m_cursor } };
  }
}