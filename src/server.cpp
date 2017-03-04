#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "server.h"
#include "network/unix_socket_receiver.h"

Server::Server()
  : socket_(nullptr)
{
}

Server::~Server()
{
  ReleasePidFile();
}

void Server::run()
{
  SetupPidFile();
  SetupSocket();
  ServerMainLoop();
}

void Server::ReleasePidFile()
{
  unlink(this->pid_file_path_.c_str());
}

void Server::SetupPidFile()
{
  pid_t pid = getpid();
  int pid_file_fd = creat(this->pid_file_path_.c_str(), 0666);
  std::string buffer = std::to_string(static_cast<int>(pid));
  write(pid_file_fd, buffer.data(), buffer.size());
  close(pid_file_fd);
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
