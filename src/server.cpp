#include "server.h"
#include "network/unix_socket_receiver.h"

Server::Server()
  : socket_(nullptr)
{
}

void Server::run()
{
  SetupSocket();
  ServerMainLoop();
}

void Server::SetupSocket()
{
  socket_ = std::make_shared<Network::Socket>();
  socket_->CreateSocket();
  socket_->BindSocket();
  socket_->ListenSocket();
}

void Server::ServerMainLoop()
{
  Network::UnixSocketReceiver receiver(socket_);

  bool shutting_down = false;
  while(!shutting_down)
  {
    shutting_down = !receiver.Accept();
  }
}
