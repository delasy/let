#include "VariableMap.hpp"

VariableMapItem VariableMap::get(const std::string &name) const {
  for (VariableMapItem item : *this) {
    if (item.name == name) {
      return item;
    }
  }

  return VariableMapItem();
}

unsigned int VariableMap::getSize() const {
  return this->size();
}

bool VariableMap::isEmpty() const {
  return this->empty();
}

VariableMapItem VariableMap::set(const std::string &name, unsigned int size) {
  unsigned int address = 0x2000;
  unsigned int addressLocal = 0x0;

  if (!this->empty()) {
    unsigned int idx = this->size();
    VariableMapItem last = (*this)[idx - 1];

    address = last.address + last.size;
    addressLocal = last.addressLocal + last.size;
  }

  VariableMapItem item;

  item.address = address;
  item.addressLocal = addressLocal;
  item.name = name;
  item.size = size;

  this->push_back(item);
  return item;
}

bool VariableMapItem::isEmpty() const {
  return this->size == 0;
}
