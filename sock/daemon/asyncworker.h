#pragma once

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>


class AsyncWorker {
  public:
    AsyncWorker(const int &client);
    ~AsyncWorker();

    static std::list<AsyncWorker *> finished;
    static void removeFinished();
    static void terminate();
    static void wait();

    void process();
    void cleanup();

  protected:
    int client;
    std::thread t;

    static std::mutex mutex;
    static std::condition_variable condition;
    static bool quit;

  private:
    void _process();
};
