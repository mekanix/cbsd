#include "shell.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

Shell::Shell(const std::string &socket_path) : socketPath{socket_path}
{
  struct sockaddr_un addr;

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socketPath.data(), sizeof(addr.sun_path) - 1);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
      std::cerr << "Connecting to " << socketPath << " failed: ";
    std::cerr << strerror(errno) << std::endl;
    exit(-1);
  }
}

Shell::~Shell() { close(fd); }

int Shell::put(const std::string &data)
{
  auto sentSize = send(fd, data.data(), data.size(), MSG_NOSIGNAL);
  if (sentSize < 0)
  {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(0);
  }
  else if (sentSize == 0)
  {
    std::cerr << "Error: socket closed" << std::endl;
    exit(0);
  }
  char buffer[1024];
  auto receivedSize = recv(fd, buffer, sizeof(buffer), MSG_NOSIGNAL);
  if (receivedSize < 0)
  {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(0);
  }
  else if (receivedSize == 0)
  {
    std::cerr << "Error: socket closed" << std::endl;
    exit(0);
  }
  return 0;
}
