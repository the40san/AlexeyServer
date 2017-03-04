#pragma once

#include <memory>
#include <string>

#include "network/socket.h"

class Server
{
 public:
   Server();
   ~Server();
   void run();

 private:
   std::shared_ptr<Network::Socket> socket_;
   const std::string pid_file_path_ = "/var/run/alexey_server.pid";

 private:
   void SetupPidFile();
   void ReleasePidFile();
   void SetupSocket();
   void ServerMainLoop();
};
