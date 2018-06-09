/**
 * @created_at: 2019-06-30 20:48:52
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

#ifndef SRC_CODEGEN_MAC64DYLIB_H
#define SRC_CODEGEN_MAC64DYLIB_H

#include "Mac64String.h"
#include "../Binary.h"

namespace let {
  class CodegenMac64DyLib {
   public:
    CodegenMac64String name;
    uint32 timestamp = 0;
    uint32 currentVersion = 0;
    uint32 compatibilityVersion = 0;

    uint32 getSize();
    Binary toBinary();
  };
}

#endif
