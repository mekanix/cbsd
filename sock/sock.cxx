#include <iostream>
#include "asyncworker.h"


int main()
{
  std::cout << "Hello World!" << std::endl;
  std::mutex m;
  AsyncWorker w(m, "<some id>");
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  return 0;
}
