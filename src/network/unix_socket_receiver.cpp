#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>

#include "unix_socket_receiver.h"
#include "util/logger.h"

#include "message/parser.h"

using namespace Network;
using namespace Util;

UnixSocketReceiver::UnixSocketReceiver(std::shared_ptr<Network::Socket> socket)
  :socket_(socket)
{
}

bool UnixSocketReceiver::Accept()
{
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(socket_->GetSocketFd(), &fds);

  int select_result = select(socket_->GetSocketFd() + 1, &fds, NULL, NULL, NULL);

  if (select_result == -1)
  {
    Logger::LogError("shuting down...");
    return false;
  }

  this->accept_socket_fd_ = accept(socket_->GetSocketFd(), NULL, NULL);

  if (this->accept_socket_fd_ == -1)
  {
    Logger::LogError("Accepting socket failed.");

    return false;
  }

  char buffer[UnixSocketReceiver::default_buffer_size];
  memset(buffer, 0, sizeof(buffer));
  read(accept_socket_fd_, buffer, sizeof(buffer));

  ParseMessage(buffer);

  return true;
}


void UnixSocketReceiver::ParseMessage(char *data)
{
  Message::Parser parser(data);
}
