#pragma once

#include <iostream>


class MyStream : public std::iostream, private std::streambuf
{
  public:
    MyStream() : std::iostream(this), str() { }

    void print()
    {
        std::cout << str;
    }

  protected:
    std::string str;

    virtual std::streamsize xsputn(const char* s, std::streamsize n)
    {
        str.append(s, n);
        setp(&(*str.begin()), &(*str.end()));
        return n;
    }

    virtual int overflow(char c)
    {
        str.push_back(c);
        setp(&(*str.begin()), &(*str.end()));
        return c;
    }
};
