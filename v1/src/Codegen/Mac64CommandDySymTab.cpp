/**
 * @created_at: 2019-06-30 20:48:11
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

#include "Mac64CommandDySymTab.h"

namespace let {
  uint32 CodegenMac64CommandDySymTab::getSize() {
    return sizeof(this->locSymIndex) +
      sizeof(this->locSymCount) +
      sizeof(this->defExtSymIndex) +
      sizeof(this->defExtSymCount) +
      sizeof(this->undefExtSymIndex) +
      sizeof(this->undefExtSymCount) +
      sizeof(this->tocTableOffset) +
      sizeof(this->tocTableCount) +
      sizeof(this->moduleTableOffset) +
      sizeof(this->moduleTableCount) +
      sizeof(this->extRefTableOffset) +
      sizeof(this->extRefTableEntries) +
      sizeof(this->indSymTableOffset) +
      sizeof(this->indSymTableEntries) +
      sizeof(this->extRelTableOffset) +
      sizeof(this->extRelTableEntries) +
      sizeof(this->locRelTableOffset) +
      sizeof(this->locRelTableEntries);
  }

  Binary CodegenMac64CommandDySymTab::toBinary() {
    Binary binary;

    binary += this->locSymIndex;
    binary += this->locSymCount;
    binary += this->defExtSymIndex;
    binary += this->defExtSymCount;
    binary += this->undefExtSymIndex;
    binary += this->undefExtSymCount;
    binary += this->tocTableOffset;
    binary += this->tocTableCount;
    binary += this->moduleTableOffset;
    binary += this->moduleTableCount;
    binary += this->extRefTableOffset;
    binary += this->extRefTableEntries;
    binary += this->indSymTableOffset;
    binary += this->indSymTableEntries;
    binary += this->extRelTableOffset;
    binary += this->extRelTableEntries;
    binary += this->locRelTableOffset;
    binary += this->locRelTableEntries;

    return binary;
  }
}
