#ifndef SRC_VARIABLEMAP_HPP
#define SRC_VARIABLEMAP_HPP

#include <string>
#include <vector>

class VariableMapItem {
 public:
  unsigned long long address = 0;
  unsigned long long addressLocal = 0;
  std::string name;
  unsigned int size = 0;

  bool isEmpty() const;
};

class VariableMap : public std::vector<VariableMapItem> {
 public:
  VariableMapItem get(const std::string &) const;
  unsigned int getSize() const;
  bool isEmpty() const;
  VariableMapItem set(const std::string &, unsigned int);
};

#endif
