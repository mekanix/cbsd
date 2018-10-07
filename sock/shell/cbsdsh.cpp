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
    std::cout << "Welcome to CBSD interactive shell" << std::endl;
    replxx::Replxx rx;
    rx.install_window_change_handler();
    char *raw_home = getenv("HOME");
    std::string home;
    if (!raw_home)
    {
      home = "";
    }
    else
    {
      home = raw_home;
    }
    std::string history_file = home + "/.cbsdsh_history";
    rx.history_load(history_file);
    auto raw_input = rx.input("> ");
    if (raw_input == nullptr)
    {
      return 0;
    }
    rx.history_add(raw_input);
    rx.history_save(history_file);
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
