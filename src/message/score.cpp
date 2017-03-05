#include <cpp_redis/cpp_redis>

#include "score.h"

using namespace Message;

void Score::Post(int score)
{

  cpp_redis::redis_client client;
  // redis host is always "redis" for now.
  client.connect("redis");

  client.get("hello", [](cpp_redis::reply& reply) {
    std::cout << reply << std::endl;
  });
  client.sync_commit();

  client.set("hello", "10");
  client.sync_commit();

  client.get("hello", [](cpp_redis::reply& reply) {
    std::cout << reply << std::endl;
  });
  client.sync_commit();

  client.disconnect();
}
