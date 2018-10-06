#include "CLI/CLI.hpp"
#include "socket.h"
#include "message.h"

#include <chrono>
#include <iostream>
#include <map>
#include <replxx.hxx>
#include <thread>
#include <vector>

std::map<std::string, std::string> options;
std::vector<std::string> jails;

int main(int argc, char **argv)
{
  CLI::App app{"CBSD shell"};
  app.set_help_all_flag("--help-all", "Expand all help");
  auto construct = app.add_subcommand("construct", "Construct resource");
  construct->add_option("jail", jails, "Jail name")->required();
  auto start = app.add_subcommand("start", "Start resource");
  start->add_option("jail", jails, "Jail name")->required();
  auto stop = app.add_subcommand("stop", "Stop resource");
  stop->add_option("jail", jails, "Jail name")->required();
  CLI11_PARSE(app, argc, argv);
  Socket s("/tmp/cbsd.sock");
  if (app.get_subcommands().size() == 0)
  {
    std::cout << "Interactive shell" << std::endl;
    replxx::Replxx rx;
    std::string raw_input = rx.input("> ");
  }
  else
  {
    std::string data = app.get_subcommands()[0]->get_name();
    for (auto jail : jails)
    {
      data += ' ';
      data += jail;
    }
    Message m;
    m.data(0, 0, data);
    s << m;
  }
  return 0;
}
