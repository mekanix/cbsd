#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "asyncworker.h"


bool AsyncWorker::quit = false;
std::mutex AsyncWorker::mutex;
std::condition_variable AsyncWorker::condition;
std::list<AsyncWorker *> AsyncWorker::finished;
static auto finishedThread = std::thread(&AsyncWorker::removeFinished);


AsyncWorker::AsyncWorker(const int &cl)
  : client{cl}
{
  t = std::thread(&AsyncWorker::_process, this);
}


AsyncWorker::~AsyncWorker()
{
  t.join();
}


void AsyncWorker::cleanup()
{
  if (client != -1)
  {
    close(client);
    client = -1;
  }
}


void AsyncWorker::process()
{
  while(!quit)
  {
    int rc;
    char buf[128];
    std::string result;

    rc = read(client, buf, sizeof(buf));
    if (rc < 0)
    {
      perror("read");
      cleanup();
      return;
    }
    else if (rc == 0)
    {
      cleanup();
      return;
    }
    else if (rc != sizeof(buf))
    {
      buf[rc] = '\0';
    }
    result = buf;
    std::cout << result << std::flush;
    if (result == "quit")
    {
      kill(getpid(), SIGINT);
    }
  }
}


void AsyncWorker::_process()
{
  process();
  std::unique_lock<std::mutex> lock(mutex);
  finished.push_back(this);
  condition.notify_one();
}


void AsyncWorker::removeFinished()
{
  while(1)
  {
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, []{
      return !finished.empty();
    });
    auto worker = finished.front();
    finished.pop_front();
    if (worker != nullptr)
    {
      delete worker;
    }
    if (quit && finished.empty())
    {
      return;
    }
  }
}


void AsyncWorker::terminate()
{
  quit = true;
  std::unique_lock<std::mutex> lock(mutex);
  finished.push_back(nullptr);
  condition.notify_all();
}


void AsyncWorker::wait()
{
  finishedThread.join();
}
