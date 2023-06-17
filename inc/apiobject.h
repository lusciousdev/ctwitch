#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

namespace ctwitch
{
  class ApiObject
  {
  public:
    ApiObject() {};
    ApiObject(json responseJson) { std::cerr << "Undefined JSON parse." << std::endl; };
    virtual ~ApiObject() {};

    virtual json ToJson() { return "null"_json; };
  };
}

#endif