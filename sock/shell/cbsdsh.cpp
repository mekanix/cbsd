#include "message.h"
#include "parser.h"
#include "shell.h"
#include "socket.h"

int main(int argc, char **argv)
{
  Parser parser;
  parser.parse(argc, argv);
  Socket socket("/tmp/cbsd.sock");
  if (parser.subcommandsSize() == 0)
  {
    Shell shell(parser, socket);
    shell.run();
  }
  else
  {
    std::string data = parser.subcommandName(0);
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
