#include <iostream>
#include <thread>
#include <chrono>
#include "shell.h"
#include "CLI/CLI.hpp"


int main(int argc, char **argv)
{
  CLI::App app{"CBSD shell"};
  // Shell s("/tmp/cbsd.sock");
  auto construct = app.add_subcommand("construct", "Construct resource");
  auto start = app.add_subcommand("start", "Start resource");
  auto stop = app.add_subcommand("stop", "Stop resource");
  app.require_subcommand(1);
  CLI11_PARSE(app, argc, argv);
  std::cout << "Subcommand: " << app.get_subcommands()[0]->get_name() << std::endl;
  return 0;
}
