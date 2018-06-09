/**
 * @created_at: 2019-06-30 20:48:41
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

#include "Mac64CommandDyLdInfo.h"

namespace let {
  uint32 CodegenMac64CommandDyLdInfo::getSize() {
    return sizeof(this->rebaseOffset) +
      sizeof(this->rebaseSize) +
      sizeof(this->bindOffset) +
      sizeof(this->bindSize) +
      sizeof(this->weakBindOffset) +
      sizeof(this->weakBindSize) +
      sizeof(this->lazyBindOffset) +
      sizeof(this->lazyBindSize) +
      sizeof(this->exportOffset) +
      sizeof(this->exportSize);
  }

  Binary CodegenMac64CommandDyLdInfo::toBinary() {
    Binary binary;

    binary += this->rebaseOffset;
    binary += this->rebaseSize;
    binary += this->bindOffset;
    binary += this->bindSize;
    binary += this->weakBindOffset;
    binary += this->weakBindSize;
    binary += this->lazyBindOffset;
    binary += this->lazyBindSize;
    binary += this->exportOffset;
    binary += this->exportSize;

    return binary;
  }
}
