#pragma once

namespace Message
{

class Parser
{
 public:
  Parser(char *data);

 private:
  char *raw_data_;

 private:
  void ParseMessagePack();
};

}
