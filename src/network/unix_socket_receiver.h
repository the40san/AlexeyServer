#pragma once

#include <memory>
#include "network/socket.h"

namespace Network {

class UnixSocketReceiver
{
 public:
  UnixSocketReceiver(std::shared_ptr<Network::Socket> socket);
  bool Accept();

 private:
  void ParseMessage(char *data);

 private:
  std::shared_ptr<Network::Socket> socket_;

  static const std::size_t default_buffer_size = 4096;
};

}
