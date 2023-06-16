#include "pagination.h"

#include <iostream>

PaginationType::PaginationType(json paginationJson)
{
  m_cursor = "";
  if (paginationJson.contains("cursor"))
    m_cursor = paginationJson["cursor"];
}