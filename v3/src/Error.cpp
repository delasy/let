#include "Error.hpp"

Error::Error(const std::string &message) {
  this->message += "\x1B[31m";
  this->message += "Error: " + message;
  this->message += "\x1B[0m";
}
