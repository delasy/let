/**
 * @created_at: 2019-06-30 20:46:41
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

#include "Mac64CommandSymTab.h"

namespace let {
  uint32 CodegenMac64CommandSymTab::getSize() {
    return sizeof(this->symTabOffset) +
      sizeof(this->symTabCount) +
      sizeof(this->strTabOffset) +
      sizeof(this->strTabSize);
  }

  Binary CodegenMac64CommandSymTab::toBinary() {
    Binary binary;

    binary += this->symTabOffset;
    binary += this->symTabCount;
    binary += this->strTabOffset;
    binary += this->strTabSize;

    return binary;
  }
}
