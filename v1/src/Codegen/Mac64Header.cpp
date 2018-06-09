/**
 * @created_at: 2019-06-29 23:10:03
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

#include "Mac64Header.h"

namespace let {
  uint32 CodegenMac64Header::getSize() {
    return sizeof(this->magic) +
      sizeof(this->cpuType) +
      sizeof(this->cpuSubType) +
      sizeof(this->fileType) +
      sizeof(this->cmdsCount) +
      sizeof(this->cmdsSize) +
      sizeof(this->flags) +
      sizeof(this->reserved);
  }

  Binary CodegenMac64Header::toBinary() {
    Binary binary;

    binary += this->magic;
    binary += this->cpuType;
    binary += this->cpuSubType;
    binary += this->fileType;
    binary += this->cmdsCount;
    binary += this->cmdsSize;
    binary += this->flags;
    binary += this->reserved;

    return binary;
  }
}
