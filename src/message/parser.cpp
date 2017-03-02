#include <msgpack.hpp>
#include <iostream>

#include "parser.h"

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
  msgpack::type::tuple<uint64_t> dst;
  deserialized.convert(dst);
  std::cout << dst.get<0>() << std::endl;
}
