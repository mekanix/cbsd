#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"


Shell::Shell(const std::string &socket_path)
  : socketPath{socket_path}
{
  struct sockaddr_un addr;
  char buf[128];
  int rc;
  const char * const quit = "quit";
  int quit_size = strlen(quit);

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socketPath.data(), sizeof(addr.sun_path)-1);

  if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
  {
    perror("connect error");
    exit(-1);
  }
}


Shell::~Shell()
{
  close(fd);
}


int Shell::put(const std::string &data)
{
  if (write(fd, data.data(), data.size()) != data.size())
  {
    perror("write error");
    exit(-1);
  }
  return 0;
}
