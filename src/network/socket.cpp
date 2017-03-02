#include <memory>
#include <unistd.h>
#include <cstdlib>

#include "socket.h"
#include "util/logger.h"

using namespace Network;
using namespace Util;

Socket::Socket()
  :socket_fd_(0)
{
  InitSockAddr();
}

Socket::~Socket()
{
  CloseSocket();
}

void Socket::CreateSocket()
{
  if (socket_fd_ != 0) { Logger::LogWarn("Socket is already initialized."); }

  this->socket_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);

  if (socket_fd_ == -1)
  {
    Logger::LogError("Createing socket failed.");

    exit(EXIT_FAILURE);
  }
}

void Socket::BindSocket()
{
  int bind_result = bind(
    this->socket_fd_,
    reinterpret_cast<sockaddr *>(&this->addr_),
    sizeof(this->addr_)
  );

  if (bind_result == -1)
  {
    Logger::LogError("binding socket failed.");

    exit(EXIT_FAILURE);
  }
}

void Socket::ListenSocket()
{
  int listen_result = listen(socket_fd_, this->socket_backlog);

  if (listen_result == -1)
  {
    Logger::LogError("listening socket failed.");

    exit(EXIT_FAILURE);
  }
}

void Socket::CloseSocket()
{
  close(socket_fd_);
  unlink(this->socket_path);
}

void Socket::InitSockAddr()
{
  this->addr_.sun_family = AF_UNIX;
  strcpy(this->addr_.sun_path, this->socket_path);
}

int Socket::GetSocketFd() const
{
  return this->socket_fd_;
}

sockaddr_un * const Socket::GetSockaddr()
{
  return &(this->addr_);
}
