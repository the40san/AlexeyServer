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

  int accept_socket_fd = accept(socket_->GetSocketFd(), NULL, NULL);

  if (accept_socket_fd == -1)
  {
    Logger::LogError("Accepting socket failed.");

    return false;
  }

  char buffer[UnixSocketReceiver::default_buffer_size];
  memset(buffer, 0, sizeof(buffer));
  read(accept_socket_fd, buffer, sizeof(buffer));

  WriteResponse(buffer, accept_socket_fd);

  close(accept_socket_fd);

  return true;
}


void UnixSocketReceiver::WriteResponse(char *data, int accept_socket_fd)
{
  Message::Parser parser(data);
  std::shared_ptr<Message::Response> response = parser.GetResponse();

  if (response == nullptr)
  {
    return;
  }

  if (response->HasResponse())
  {
    std::string payload = response->GetPayload();
    write(accept_socket_fd, payload.data(), payload.size());
  }
}
