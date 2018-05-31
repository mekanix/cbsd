#pragma once

#include <string>
#include <iostream>


class Message
{
  public:
    Message()
    {
      id = 0;
      type = 0;
      payload = '';
    }
    Message(const int &_id, const int &_type, const std::string &_payload)
    {
      id = _id;
      type = _type;
      payload = _payload;
    }

    friend std::ostream & operator<<(std::ostream &os, const Message &m)
    {
      os << m.id << ' ' << m.type << ' ';
      os << m.payload.size() << ' ' << m.payload;
      return os;
    }
    friend std::istream & operator>>(std::istream &is, Message &m)
    {
      is >> m.id;
      if (is.fail())
      {
        std::cerr << "Failed to load id" << std::endl;
        return is;
      }
      is >> m.type;
      if (is.fail())
      {
        std::cerr << "Failed to load type" << std::endl;
        return is;
      }
      int size;
      is >> size;
      if (is.fail())
      {
        std::cerr << "Failed to load size" << std::endl;
      }
      ++size;
      char c;
      is.get(c);
      if (is.fail())
      {
        std::cerr << "Failed to load space after size" << std::endl;
        return is;
      }
      char buffer[size];
      is.get(buffer, size, '\0');
      if (is.fail())
      {
        std::cerr << "Failed to load payload" << std::endl;
        return is;
      }
      m.payload = buffer;
      return is;
    }

    int id;
    int type;
    std::string payload;
};