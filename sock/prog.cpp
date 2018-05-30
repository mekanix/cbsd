#include <iostream>
#include <sstream>
#include "message.h"


int main()
{
  Message m(1, 3, "opala");
  std::cout << m << std::endl;

  std::stringstream s;
  s << 8 << ' ' << 2 << " 7 payload";
  s >> m;
  std::cout << m << std::endl;

  s << 8 << 2 << " payload";
  s >> m;
  if (s.fail())
  {
    std::cerr << "Global fail" << std::endl;
  }
  return 0;
}
