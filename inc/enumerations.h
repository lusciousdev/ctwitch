#ifndef _ENUMERATIONS_H_
#define _ENUMERATIONS_H_

#include <string>
#include "stringutil.h"


class SortEnum
{
public:
  enum Type : uint8_t {TIME = 0, TRENDING = 1, VIEWS = 2};

  SortEnum() { m_value = Type::TIME; }

  SortEnum(Type val) { m_value = val; }
  
  SortEnum(std::string sortString)
  {
    if (stringutil::iequals(sortString, "trending"))
    {
      m_value = Type::TRENDING;
    }
    else if (stringutil::iequals(sortString, "views"))
    {
      m_value = Type::VIEWS;
    }
    else
    {
      m_value = Type::TIME;
    }
  }

  operator std::string() const
  {
    switch (m_value)
    {
      case TRENDING:
        return "trending";
      case VIEWS:
        return "views";
      case TIME:
      default:
        return "time";
    }
  }

private: 
  Type m_value;
};



class PeriodEnum
{
public:
  enum Type : uint8_t
  {
    ALL = 0,
    DAY = 1,
    MONTH = 2,
    WEEK = 3
  };

  PeriodEnum() { m_value = Type::ALL; }

  PeriodEnum(Type period) { m_value = period; }

  PeriodEnum(std::string periodString)
  {
    if (stringutil::iequals(periodString, "day"))
    {
      m_value = Type::DAY;
    }
    else if (stringutil::iequals(periodString, "month"))
    {
      m_value = Type::MONTH;
    }
    else if (stringutil::iequals(periodString, "week"))
    {
      m_value = Type::WEEK;
    }
    else
    {
      m_value = Type::ALL;
    }
  }

  operator std::string() const
  {
    switch (m_value)
    {
      case Type::DAY:
        return "day";
      case Type::MONTH:
        return "month";
      case Type::WEEK:
        return "week";
      case Type::ALL:
      default:
        return "all";
    }
  }

  PeriodEnum::Type GetValue() { return m_value; }

private:
  Type m_value;
};

struct VideoTypeEnum
{
public:
  enum Type : uint8_t
  {
    ALL = 0,
    ARCHIVE = 1,
    HIGHLIGHT = 2,
    UPLOAD = 3
  };

  VideoTypeEnum() { m_value = Type::ALL; }

  VideoTypeEnum(Type val) { m_value = val; }

  VideoTypeEnum(std::string videoTypeString)
  {
    if (stringutil::iequals(videoTypeString, "archive"))
    {
      m_value = Type::ARCHIVE;
    }
    else if (stringutil::iequals(videoTypeString, "highlight"))
    {
      m_value = Type::HIGHLIGHT;
    }
    else if (stringutil::iequals(videoTypeString, "upload"))
    {
      m_value = Type::UPLOAD;
    }
    else
    {
      m_value = Type::ALL;
    }
  }

  operator std::string() const
  {
    switch (m_value)
    {
      case Type::ARCHIVE:
        return "archive";
      case Type::HIGHLIGHT:
        return "highlight";
      case Type::UPLOAD:
        return "upload";
      case Type::ALL:
      default:
        return "all";
    }
  }

  VideoTypeEnum::Type GetValue() { return m_value; }

private:
  Type m_value;
};

#endif