#pragma once

#include <string>


class Shell
{
  public:
    Shell(const std::string &socketPath);
    ~Shell();

    int put(const std::string &data);

  protected:
    int fd;
    std::string socketPath;
};
