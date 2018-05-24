#include <iostream>
#include <signal.h>
#include <sys/un.h>
#include "asyncworker.h"
#include "sock.h"


Socket s("/tmp/cbsd.sock");


void signalHandler(int sig)
{
  signal(sig, SIG_IGN);
  AsyncWorker::terminate();
  AsyncWorker::wait();
  s.cleanup();
  exit(0);
}


int main()
{
  signal(SIGINT, signalHandler);

  while(1)
  {
    auto client = s.waitForClient();
    new AsyncWorker(client);
  }
  return 0;
}
