#ifndef SRC_EXCEPTION_HPP
#define SRC_EXCEPTION_HPP

#include "Reader.hpp"

class Exception : public std::exception {
 public:
  std::string message;

  explicit Exception(const std::string &);
  explicit Exception(const std::string &, const Reader &);
};

#endif
