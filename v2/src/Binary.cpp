#include "Binary.hpp"
#include <fstream>

Binary &Binary::operator+=(const Binary &rhs) {
  for (unsigned char byte : rhs) {
    *this += byte;
  }

  return *this;
}

Binary &Binary::operator+=(const std::string &rhs) {
  this->appendString(rhs, rhs.size());
  return *this;
}

Binary &Binary::operator+=(const std::vector<char> &rhs) {
  for (char ch : rhs) {
    *this += ch;
  }

  return *this;
}

Binary &Binary::operator+=(const std::vector<unsigned char> &rhs) {
  for (unsigned char ch : rhs) {
    *this += ch;
  }

  return *this;
}

Binary &Binary::operator+=(char rhs) {
  this->push_back((unsigned char) rhs & 0xFFu);
  return *this;
}

Binary &Binary::operator+=(short rhs) {
  unsigned short urhs = rhs;

  this->push_back(urhs & 0xFFu);
  this->push_back(((unsigned) urhs >> 8u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(int rhs) {
  unsigned int urhs = rhs;

  this->push_back(urhs & 0xFFu);
  this->push_back((urhs >> 8u) & 0xFFu);
  this->push_back((urhs >> 16u) & 0xFFu);
  this->push_back((urhs >> 24u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(long rhs) {
  unsigned long urhs = rhs;

  this->push_back(urhs & 0xFFu);
  this->push_back((urhs >> 8u) & 0xFFu);
  this->push_back((urhs >> 16u) & 0xFFu);
  this->push_back((urhs >> 24u) & 0xFFu);
  this->push_back((urhs >> 32u) & 0xFFu);
  this->push_back((urhs >> 40u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(long long rhs) {
  unsigned long long urhs = rhs;

  this->push_back(urhs & 0xFFu);
  this->push_back((urhs >> 8u) & 0xFFu);
  this->push_back((urhs >> 16u) & 0xFFu);
  this->push_back((urhs >> 24u) & 0xFFu);
  this->push_back((urhs >> 32u) & 0xFFu);
  this->push_back((urhs >> 40u) & 0xFFu);
  this->push_back((urhs >> 48u) & 0xFFu);
  this->push_back((urhs >> 56u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(unsigned char rhs) {
  this->push_back(rhs & 0xFFu);
  return *this;
}

Binary &Binary::operator+=(unsigned short rhs) {
  this->push_back(rhs & 0xFFu);
  this->push_back(((unsigned) rhs >> 8u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(unsigned int rhs) {
  this->push_back(rhs & 0xFFu);
  this->push_back((rhs >> 8u) & 0xFFu);
  this->push_back((rhs >> 16u) & 0xFFu);
  this->push_back((rhs >> 24u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(unsigned long rhs) {
  this->push_back(rhs & 0xFFu);
  this->push_back((rhs >> 8u) & 0xFFu);
  this->push_back((rhs >> 16u) & 0xFFu);
  this->push_back((rhs >> 24u) & 0xFFu);
  this->push_back((rhs >> 32u) & 0xFFu);
  this->push_back((rhs >> 40u) & 0xFFu);

  return *this;
}

Binary &Binary::operator+=(unsigned long long rhs) {
  this->push_back(rhs & 0xFFu);
  this->push_back((rhs >> 8u) & 0xFFu);
  this->push_back((rhs >> 16u) & 0xFFu);
  this->push_back((rhs >> 24u) & 0xFFu);
  this->push_back((rhs >> 32u) & 0xFFu);
  this->push_back((rhs >> 40u) & 0xFFu);
  this->push_back((rhs >> 48u) & 0xFFu);
  this->push_back((rhs >> 56u) & 0xFFu);

  return *this;
}

Binary Binary::appendString(const std::string &string, unsigned int size) {
  unsigned int strSize = string.size();
  unsigned int i;

  for (i = 0; i < strSize; i++) {
    this->push_back((unsigned char) string[i] & 0xFFu);
  }

  this->appendZero(size - i);
  return *this;
}

Binary Binary::appendZero(unsigned int times) {
  for (unsigned int i = 0; i < times; i++) {
    this->push_back(0u & 0xFFu);
  }

  return *this;
}

const unsigned char *Binary::getData() const {
  return this->data();
}

unsigned int Binary::getSize() const {
  return this->size();
}

void Binary::writeToFile(const std::filesystem::path &path) const {
  std::fstream file(path, std::ios::out | std::ios::binary);

  file.write((char *) &this->getData()[0], this->getSize());
  file.close();
}
