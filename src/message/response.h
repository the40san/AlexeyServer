#pragma once

#include <string>

namespace Message
{

class Response
{
 public:
  virtual const std::string GetPayload() = 0;
  virtual bool HasResponse() = 0;
};

}
