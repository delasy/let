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

#ifndef SRC_CODEGEN_MAC64COMMANDDYSYMTAB_H
#define SRC_CODEGEN_MAC64COMMANDDYSYMTAB_H

#include "../Binary.h"

namespace let {
  class CodegenMac64CommandDySymTab {
   public:
    uint32 locSymIndex = 0;
    uint32 locSymCount = 0;
    uint32 defExtSymIndex = 0;
    uint32 defExtSymCount = 0;
    uint32 undefExtSymIndex = 0;
    uint32 undefExtSymCount = 0;
    uint32 tocTableOffset = 0;
    uint32 tocTableCount = 0;
    uint32 moduleTableOffset = 0;
    uint32 moduleTableCount = 0;
    uint32 extRefTableOffset = 0;
    uint32 extRefTableEntries = 0;
    uint32 indSymTableOffset = 0;
    uint32 indSymTableEntries = 0;
    uint32 extRelTableOffset = 0;
    uint32 extRelTableEntries = 0;
    uint32 locRelTableOffset = 0;
    uint32 locRelTableEntries = 0;

    uint32 getSize();
    Binary toBinary();
  };
}

#endif
