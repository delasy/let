#ifndef SRC_ERROR_HPP
#define SRC_ERROR_HPP

#include <string>

class Error : public std::exception {
 public:
  std::string message;

  explicit Error(const std::string &);
};

#endif
