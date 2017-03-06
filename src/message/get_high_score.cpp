#include <cpp_redis/cpp_redis>
#include <msgpack.hpp>
#include <sstream>

#include "get_high_score.h"
#include "util/logger.h"

using namespace Message;

const std::string GetHighScore::GetPayload()
{
  msgpack::type::tuple<uint32_t> src(static_cast<uint32_t>(GetCurrentHighScore()));

  Util::Logger::Log(std::to_string(static_cast<uint32_t>(GetCurrentHighScore())));

  std::stringstream buffer;
  msgpack::pack(buffer, src);
  buffer.seekg(0);

  return std::string(buffer.str());
}

bool GetHighScore::HasResponse()
{
  return true;
}

int64_t GetHighScore::GetCurrentHighScore()
{
  int64_t current_high_score = 0;

  cpp_redis::redis_client client;
  client.connect(std::string(std::getenv("REDIS_HOST")));
  client.get(this->score_redis_key, [&current_high_score](cpp_redis::reply& reply) {
    if(!reply.is_null())
    {
      current_high_score = std::stoi(reply.as_string());
    }
  });
  client.sync_commit();

  return current_high_score;
}
