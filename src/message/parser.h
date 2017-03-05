#pragma once

#include <memory>
#include "response.h"

namespace Message
{

class Parser
{
 public:
  Parser(char *data);
  std::shared_ptr<Response> GetResponse();

 private:
  char *raw_data_;

 private:
  static constexpr int RPC_UPDATE_HIGH_SCORE = 0;
  static constexpr int RPC_GET_HIGH_SCORE = 1;
};

}
