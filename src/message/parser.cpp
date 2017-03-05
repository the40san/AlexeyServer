#include <msgpack.hpp>
#include <iostream>

#include "parser.h"
#include "score.h"

using namespace Message;

Parser::Parser(char *data)
  :raw_data_(data)
{
  ParseMessagePack();
}

void Parser::ParseMessagePack()
{
  msgpack::object_handle result;

  msgpack::unpack(result, raw_data_, sizeof(raw_data_));

  msgpack::object deserialized = result.get();

  // TODO: parse message
  msgpack::type::tuple<uint32_t> dst;
  deserialized.convert(dst);
  std::cout << dst.get<0>() << std::endl;

  Score score;
  score.Post(dst.get<0>());
}
