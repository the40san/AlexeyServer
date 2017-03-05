#include <cpp_redis/cpp_redis>
#include <sstream>

#include "update_high_score.h"
#include "util/logger.h"

using namespace Message;

UpdateHighScore::UpdateHighScore(msgpack::object deserialized)
  :msgpack_object_(deserialized)
{
  // RPC_ID, new_score_
  msgpack::type::tuple<uint32_t, uint32_t> dst;
  msgpack_object_.convert(dst);
  this->new_score_ = dst.get<1>();
}

const std::string UpdateHighScore::GetPayload()
{
  int64_t current_high_score = UpdateRedisScore();

  msgpack::type::tuple<uint32_t> src(static_cast<uint32_t>(current_high_score));

  std::stringstream buffer;
  msgpack::pack(buffer, src);
  buffer.seekg(0);

  return std::string(buffer.str());
}

bool UpdateHighScore::HasResponse()
{
  return true;
}

int64_t UpdateHighScore::UpdateRedisScore()
{
  // redis host is always "redis" (see docker-compose.yml) for now.
  cpp_redis::redis_client client;
  client.connect(std::string(std::getenv("REDIS_HOST")));

  int64_t current_high_score = 0;
  client.get(this->score_redis_key, [&current_high_score](cpp_redis::reply& reply) {
    if(!reply.is_null())
    {
      current_high_score = std::stoi(reply.as_string());
    }
  });
  client.sync_commit();

  if (current_high_score >= this->new_score_)
  {
    return current_high_score;
  }

  // let's update high score!
  client.set(this->score_redis_key, std::to_string(this->new_score_));
  client.sync_commit();
  client.disconnect();
  Util::Logger::Log("New high score: " + std::to_string(this->new_score_));

  return this->new_score_;
}
