#include "CLI/CLI.hpp"
#include "shell.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::string jail;
std::string result;

int main(int argc, char **argv)
{
  CLI::App app{"CBSD shell"};
  app.set_help_all_flag("--help-all", "Expand all help");
  // Shell s("/tmp/cbsd.sock");
  auto construct = app.add_subcommand("construct", "Construct resource");
  construct->add_option("-j,--jail", jail, "Jail name")->required();
  app.add_subcommand("start", "Start resource");
  app.add_subcommand("stop", "Stop resource");
  app.require_subcommand(1);
  CLI11_PARSE(app, argc, argv);
  std::cout << app.get_subcommands()[0]->get_name() << ' ' << jail << std::endl;
  return 0;
}
