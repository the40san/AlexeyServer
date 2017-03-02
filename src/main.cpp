#include <memory>
#include <signal.h>

#include "server.h"


void SignalHandler(int signum) {
}

int main(int argc, char **argv)
{
  signal(SIGINT,  SignalHandler);
  signal(SIGTERM, SignalHandler);
  signal(SIGUSR1, SignalHandler);
  std::unique_ptr<Server> server(new Server());
  server->run();

  return 0;
}
