#include "Exception.hpp"

Exception::Exception(const std::string &message) {
  this->message += "\x1B[31m";
  this->message += "Error: " + message;
  this->message += "\x1B[0m";
}

Exception::Exception(const std::string &message, const Reader &reader) {
  this->message += "\x1B[31m";
  this->message += "SyntaxError: " + message;
  this->message += "\n  at ";
  this->message += reader.filePath;
  this->message += ":" + std::to_string(reader.cursor3.lineNum);
  this->message += ":" + std::to_string(reader.cursor3.charIdx);
  this->message += "\x1B[0m";
}
