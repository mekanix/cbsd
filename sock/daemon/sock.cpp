#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sock.h"


std::vector<Socket *> Socket::all;


Socket::Socket(const std::string &socket_path)
  : socketPath{socket_path}
{
  it = all.emplace(all.end(), this);
  struct sockaddr_un addr;

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socketPath.data(), sizeof(addr.sun_path)-1);
  unlink(socketPath.data());

  if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind error");
    exit(-1);
  }

  if (listen(fd, 5) == -1) {
    perror("listen error");
    exit(-1);
  }
}


Socket::~Socket()
{
  cleanup();
  all.erase(it);
}


void Socket::cleanup()
{
  unlink(socketPath.data());
  if (fd != -1)
  {
    close(fd);
    fd = -1;
  }
}


const int Socket::waitForClient()
{
  int client;
  if ((client = accept(fd, NULL, NULL)) == -1) {
    perror("accept error");
    cleanup();
    exit(1);
  }
  return client;
}