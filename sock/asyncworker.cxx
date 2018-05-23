#include "asyncworker.h"


AsyncWorker::AsyncWorker(std::mutex &m, const std::string &name)
  : quit{false}
  , name{name}
  , m{m}
{
  t = std::thread(&AsyncWorker::process, this);
}

AsyncWorker::~AsyncWorker()
{
  quit = true;
  t.join();
  std::cout << name << ": Good bye, cruel world!" << std::endl;
}

void AsyncWorker::process() const
{
  while(1)
  {
    if (quit) {return;}
    // simulate work before lock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock(m);
    std::cout << "hello from member function " << name << std::endl;
    // simulate work inside lock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
