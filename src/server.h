#pragma once

#include <memory>

#include "network/socket.h"

class Server
{
 public:
   Server();
   void run();

 private:
   std::shared_ptr<Network::Socket> socket_;

 private:
   void SetupSocket();
   void ServerMainLoop();
};
