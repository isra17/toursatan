#ifndef CTOUREXCEPTION_H
#define CTOUREXCEPTION_H

#include <exception>
#include <string>

class CTourException : public std::exception {
  private:
	  std::string m_err;
  public:
	  CTourException ( const std::string &err) : m_err(err) {}
    const char* what() { return m_err.c_str(); }
};

#endif //CTOUREXCEPTION_H
