#ifndef SRC_BINARY_HPP
#define SRC_BINARY_HPP

#include <filesystem>
#include <vector>

class Binary : public std::vector<unsigned char> {
 public:
  using vector::operator[];

  Binary &operator+=(const Binary &);
  Binary &operator+=(const std::string &);
  Binary &operator+=(const std::vector<char> &);
  Binary &operator+=(const std::vector<unsigned char> &);
  Binary &operator+=(char);
  Binary &operator+=(short);
  Binary &operator+=(int);
  Binary &operator+=(long);
  Binary &operator+=(long long);
  Binary &operator+=(unsigned char);
  Binary &operator+=(unsigned short);
  Binary &operator+=(unsigned int);
  Binary &operator+=(unsigned long);
  Binary &operator+=(unsigned long long);

  Binary appendString(const std::string &, unsigned int);
  Binary appendZero(unsigned int);
  const unsigned char *getData() const;
  unsigned int getSize() const;
  void writeToFile(const std::filesystem::path &) const;
};

#endif
