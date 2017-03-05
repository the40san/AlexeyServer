#pragma once

#include <string>

namespace Message
{

class Score
{
 public:
  void Post(int score);

 private:
  const std::string score_redis_key = "alexey:score";
};

}
