#include <iostream>
#include <thread>
#include <chrono>
#include "shell.h"
#include "CLI/CLI.hpp"


std::string jail;
std::string result;


int main(int argc, char **argv)
{
  CLI::App app{"CBSD shell"};
  app.set_help_all_flag("--help-all", "Expand all help");
  // Shell s("/tmp/cbsd.sock");
  auto construct = app.add_subcommand("construct", "Construct resource");
  auto constructJail = construct->add_option("-j,--jail", [](std::vector &args) {
    std::cout << "Adding jail to result" << std::endl;
    result += ' ';
    result += jail;
  }, "Jail name");
  auto start = app.add_subcommand("start", "Start resource");
  auto stop = app.add_subcommand("stop", "Stop resource");
  construct->set_callback([&]() {
    std::cout << "Adding construct to result" << std::endl;
    result += "construct";
  });
  app.require_subcommand(1);
  CLI11_PARSE(app, argc, argv);
  std::cout << "Subcommand: " << app.get_subcommands()[0]->get_name() << std::endl;
  std::cout << "Result: " << result << std::endl;
  return 0;
}
