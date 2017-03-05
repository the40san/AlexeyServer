#pragma once

#include <string>
#include <msgpack.hpp>

#include "response.h"

namespace Message
{

class UpdateHighScore : public Response
{
 public:
  UpdateHighScore(msgpack::object deserialized);
  const std::string GetPayload();
  bool HasResponse();

 private:
  int64_t UpdateRedisScore();

 private:
  const std::string score_redis_key = "alexey:score";
  msgpack::object msgpack_object_;
  int64_t new_score_;
};

}
