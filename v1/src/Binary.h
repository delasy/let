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

#ifndef SRC_BINARY_H
#define SRC_BINARY_H

#include <vector>

#include "types.h"

namespace let {
  class Binary : private std::vector<uint8> {
   public:
    using vector::operator[];

    Binary &operator+=(const Binary &);
    Binary &operator+=(const String &);
    Binary &operator+=(const std::vector<int8> &);
    Binary &operator+=(const std::vector<uint8> &);
    Binary &operator+=(int8);
    Binary &operator+=(int16);
    Binary &operator+=(int32);
    Binary &operator+=(int48);
    Binary &operator+=(int64);
    Binary &operator+=(uint8);
    Binary &operator+=(uint16);
    Binary &operator+=(uint32);
    Binary &operator+=(uint48);
    Binary &operator+=(uint64);

    Binary appendString(const String &, uint32);
    Binary appendZero(uint32);
    uint8 *getData();
    uint32 getSize();
  };
}

#endif
