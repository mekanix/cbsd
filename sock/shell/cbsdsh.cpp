#include "message.h"
#include "parser.h"
#include "socket.h"

#include <chrono>
#include <iostream>
#include <map>
#include <replxx.hxx>
#include <thread>
#include <vector>

int main(int argc, char **argv)
{
  Parser p;
  p.parse(argc, argv);
  Socket s("/tmp/cbsd.sock");
  if (p.app.get_subcommands().size() == 0)
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
    std::stringstream ss;
    std::vector<std::string> args;
    bool ok = true;
    ss << raw_input;
    while(!ss.eof())
    {
      std::string s;
      ss >> s;
      if (ss.fail())
      {
        ok = false;
        break;
      }
      args.insert(args.begin(), s);
    }
    if (ok)
    {
      p.parse(args);
      rx.history_add(raw_input);
      std::string data = p.app.get_subcommands()[0]->get_name();
      for (auto jail : p.jails())
      {
        data += ' ';
        data += jail;
      }
      Message m;
      m.data(0, 0, data);
      s << m;
    }
    rx.history_save(history_file);
  }
  else
  {
    std::string data = p.app.get_subcommands()[0]->get_name();
    for (auto jail : p.jails())
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
