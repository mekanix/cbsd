#include <iostream>
#include <thread>
#include <chrono>
#include "shell.h"
#include "CLI/CLI.hpp"


std::string jailName;


int main(int argc, char **argv)
{
  CLI::App app{"CBSD shell"};
  app.require_subcommand(1);
  // Shell s("/tmp/cbsd.sock");

  // Start command
  {
    auto subcommand = app.add_subcommand("start", "Start resource");
    subcommand->add_option("jail", jailName, "Jail name")->required();
  }

  // Stop command
  {
    auto subcommand = app.add_subcommand("stop", "Stop resource");
    subcommand->add_option("jail", jailName, "Jail name")->required();
  }

  CLI11_PARSE(app, argc, argv);
  std::cout << "Subcommand: " << app.get_subcommands()[0]->get_name() << std::endl;
  std::cout << "Jail name: " << jailName << std::endl;
  return 0;
}
