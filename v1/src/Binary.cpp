/**
 * @created_at: 2019-07-01 13:43:13
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

#include "Binary.h"

namespace let {
  Binary &Binary::operator+=(const Binary &rhs) {
    for (uint8 byte : rhs) {
      *this += byte;
    }

    return *this;
  }

  Binary &Binary::operator+=(const String &rhs) {
    uint32 rhsSize = rhs.size();

    this->appendString(rhs, rhsSize);

    return *this;
  }

  Binary &Binary::operator+=(const std::vector<int8> &rhs) {
    for (int8 ch : rhs) {
      *this += ch;
    }

    return *this;
  }

  Binary &Binary::operator+=(const std::vector<uint8> &rhs) {
    for (int8 ch : rhs) {
      *this += ch;
    }

    return *this;
  }

  Binary &Binary::operator+=(int8 rhs) {
    uint8 urhs = rhs;

    this->push_back(urhs & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(int16 rhs) {
    uint16 urhs = rhs;

    this->push_back(urhs & 0xFFu);
    this->push_back(((unsigned) urhs >> 8u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(int32 rhs) {
    uint32 urhs = rhs;

    this->push_back(urhs & 0xFFu);
    this->push_back((urhs >> 8u) & 0xFFu);
    this->push_back((urhs >> 16u) & 0xFFu);
    this->push_back((urhs >> 24u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(int48 rhs) {
    uint48 urhs = rhs;

    this->push_back(urhs & 0xFFu);
    this->push_back((urhs >> 8u) & 0xFFu);
    this->push_back((urhs >> 16u) & 0xFFu);
    this->push_back((urhs >> 24u) & 0xFFu);
    this->push_back((urhs >> 32u) & 0xFFu);
    this->push_back((urhs >> 40u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(int64 rhs) {
    uint64 urhs = rhs;

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

  Binary &Binary::operator+=(uint8 rhs) {
    this->push_back(rhs & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(uint16 rhs) {
    this->push_back(rhs & 0xFFu);
    this->push_back(((unsigned) rhs >> 8u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(uint32 rhs) {
    this->push_back(rhs & 0xFFu);
    this->push_back((rhs >> 8u) & 0xFFu);
    this->push_back((rhs >> 16u) & 0xFFu);
    this->push_back((rhs >> 24u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(uint48 rhs) {
    this->push_back(rhs & 0xFFu);
    this->push_back((rhs >> 8u) & 0xFFu);
    this->push_back((rhs >> 16u) & 0xFFu);
    this->push_back((rhs >> 24u) & 0xFFu);
    this->push_back((rhs >> 32u) & 0xFFu);
    this->push_back((rhs >> 40u) & 0xFFu);

    return *this;
  }

  Binary &Binary::operator+=(uint64 rhs) {
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

  Binary Binary::appendString(const String &str, uint32 size) {
    uint32 strSize = str.size();
    uint32 i;

    for (i = 0; i < strSize; i++) {
      uint8 uch = str[i];

      this->push_back(uch & 0xFFu);
    }

    this->appendZero(size - i);

    return *this;
  }

  Binary Binary::appendZero(uint32 times) {
    for (uint32 i = 0; i < times; i++) {
      this->push_back(0u & 0xFFu);
    }

    return *this;
  }

  uint8 *Binary::getData() {
    return this->data();
  }

  uint32 Binary::getSize() {
    return this->size();
  }
}
