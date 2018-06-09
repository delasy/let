/**
 * @created_at: 2019-06-23 23:47:03
 * @author: Aaron Delasy
 * @license_start
 *
 * Copyright (c) 2018-2019  Aaron Delasy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @license_end
 */

#include "VariableMap.h"

namespace let {
  VariableMapItem VariableMap::get(const String &name) {
    for (VariableMapItem item : *this) {

      if (item.name == name) {
        return item;
      }
    }

    return VariableMapItem();
  }

  uint32 VariableMap::getSize() {
    return this->size();
  }

  bool VariableMap::isEmpty() {
    return this->empty();
  }

  VariableMapItem VariableMap::set(const String &name, uint32 size) {
    uint32 address = 0x2000;
    uint32 addressLocal = 0x0;

    if (!this->empty()) {
      uint32 idx = this->size();
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
}
