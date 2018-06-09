/**
 * @created_at: 2019-06-30 14:30:49
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

#include "Mac64Section.h"

namespace let {
  CodegenMac64Section::CodegenMac64Section(
    const String &secName, const String &segName
  ) {
    this->secName = secName;
    this->segName = segName;
  }

  uint32 CodegenMac64Section::getSize() {
    return this->secNameSize +
      this->segNameSize +
      sizeof(this->address) +
      sizeof(this->size) +
      sizeof(this->offset) +
      sizeof(this->align) +
      sizeof(this->reallocOffset) +
      sizeof(this->reallocCount) +
      sizeof(this->flags) +
      sizeof(this->reserved1) +
      sizeof(this->reserved2) +
      sizeof(this->reserved3);
  }

  Binary CodegenMac64Section::toBinary() {
    Binary binary;

    binary.appendString(this->secName, this->secNameSize);
    binary.appendString(this->segName, this->segNameSize);

    binary += this->address;
    binary += this->size;
    binary += this->offset;
    binary += this->align;
    binary += this->reallocOffset;
    binary += this->reallocCount;
    binary += this->flags;
    binary += this->reserved1;
    binary += this->reserved2;
    binary += this->reserved3;

    return binary;
  }
}
