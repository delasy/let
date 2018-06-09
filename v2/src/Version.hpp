#ifndef SRC_VERSION_HPP
#define SRC_VERSION_HPP

#include <string>
#include <vector>

class Version {
 public:
  static const std::string NAME;
  static const std::string NUMBER;

  static unsigned int a16b8c8(const std::string &);
  static unsigned long long a24b10c10d10e10(const std::string &);
  static std::vector<unsigned int> toVector(const std::string &);
};

#endif
