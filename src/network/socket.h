#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace Network
{

class Socket
{
 public:
  Socket();
  ~Socket();

  void CreateSocket();
  void BindSocket();
  void ListenSocket();
  void CloseSocket();

  int GetSocketFd() const;
  sockaddr_un * const GetSockaddr();

 private:
  sockaddr_un addr_;
  int socket_fd_;

  const int socket_backlog = 1024;
  const char * socket_path = "/var/run/alexey_server.sock";

 private:
  void InitSockAddr();
};

}
