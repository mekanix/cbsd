#include <iostream>
#include <thread>
#include <chrono>
#include "shell.h"


int main()
{
  Shell s("/tmp/cbsd.sock");
  while(1)
  {
    s.put("quit");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}
