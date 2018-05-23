#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <iostream>


class AsyncWorker {
  public:
    AsyncWorker(std::mutex &m, const std::string &name = "");
    ~AsyncWorker();
    void process() const;

  protected:
    bool quit;
    const std::string name;
    std::mutex &m;
    std::thread t;
};

