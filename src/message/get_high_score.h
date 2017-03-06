#pragma once

#include "response.h"

namespace Message
{

class GetHighScore : public Response
{
 public:
  const std::string GetPayload();
  bool HasResponse();

 private:
  int64_t GetCurrentHighScore();

 private:
  const std::string score_redis_key = "alexey:score";
};

};
