#include "message.h"
#include "parser.h"
#include "socket.h"

#include <iostream>
#include <replxx.hxx>
#include <vector>

int main(int argc, char **argv)
{
  Parser parser;
  parser.parse(argc, argv);
  Socket socket("/tmp/cbsd.sock");
  if (parser.app.get_subcommands().size() == 0)
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
    while (true)
    {
      auto raw_input = rx.input("> ");
      if (raw_input == nullptr)
      {
        if (errno == EAGAIN)
        {
          continue;
        }
        else
        {
          break;
        }
      }
      std::stringstream sstream;
      std::vector<std::string> args;
      bool ok = true;
      bool help = false;
      sstream << raw_input;
      while (!sstream.eof())
      {
        std::string s;
        sstream >> s;
        if (sstream.fail())
        {
          ok = false;
          break;
        }
        std::cout << s << std::endl;
        if (s == "-h" or s == "--help" or s == "--help-all")
        {
          help = true;
        }
        args.insert(args.begin(), s);
      }
      if (ok)
      {
        auto rc = parser.parse(args);
        if (help)
        {
          continue;
        }
        if (rc == 0)
        {
          rx.history_add(raw_input);
          auto subcommands = parser.app.get_subcommands();
          if (subcommands.size() == 0)
          {
            continue;
          }
          if (help)
          {
            continue;
          }
          std::string data = subcommands[0]->get_name();
          for (auto jail : parser.jails())
          {
            data += ' ';
            data += jail;
          }
          Message message;
          message.data(0, 0, data);
          socket << message;
        }
      }
    }
    rx.history_save(history_file);
  }
  else
  {
    std::string data = parser.app.get_subcommands()[0]->get_name();
    for (auto jail : parser.jails())
    {
      data += ' ';
      data += jail;
    }
    Message message;
    message.data(0, 0, data);
    socket << message;
  }
  return 0;
}
