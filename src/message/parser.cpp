#include <msgpack.hpp>
#include <iostream>
#include <memory>

#include "parser.h"
#include "update_high_score.h"
#include "get_high_score.h"

using namespace Message;

Parser::Parser(char *data)
  :raw_data_(data)
{
}

std::shared_ptr<Response> Parser::GetResponse()
{
  msgpack::object_handle result;

  msgpack::unpack(result, raw_data_, sizeof(raw_data_));

  msgpack::object deserialized = result.get();

  msgpack::type::tuple<uint32_t> dst;
  deserialized.convert(dst);

  switch(dst.get<0>())
  {
    case Parser::RPC_UPDATE_HIGH_SCORE:
      return std::static_pointer_cast<Response>( std::make_shared<UpdateHighScore>(deserialized) );
    case Parser::RPC_GET_HIGH_SCORE:
      return std::static_pointer_cast<Response>( std::make_shared<GetHighScore>() );

  }

  return nullptr;
}
