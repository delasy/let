/**
 * @created_at: 2019-06-30 14:26:32
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

#ifndef SRC_CODEGEN_MAC64COMMANDSEGMENT_H
#define SRC_CODEGEN_MAC64COMMANDSEGMENT_H

#include "Mac64Section.h"

#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_UNKNOWN 0x0u
#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_HIGHVM 0x1u
#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_FVMLIB 0x2u
#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_NORELOC 0x4u
#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_PROTECTED_VERSION_1 0x8u
#define CODEGEN_MAC64_COMMANDSEGMENT_FLAG_READ_ONLY 0x10u

#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_NONE 0x00u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_READ 0x01u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_WRITE 0x02u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_EXECUTE 0x04u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_DEFAULT \
  (CODEGEN_MAC64_COMMANDSEGMENT_PROT_READ | \
    CODEGEN_MAC64_COMMANDSEGMENT_PROT_WRITE)
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_ALL \
  (CODEGEN_MAC64_COMMANDSEGMENT_PROT_READ | \
    CODEGEN_MAC64_COMMANDSEGMENT_PROT_WRITE | \
    CODEGEN_MAC64_COMMANDSEGMENT_PROT_EXECUTE)
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_NO_CHANGE 0x08u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_COPY 0x10u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_WANTS_COPY 0x10u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_IS_MASK 0x40u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_STRIP_READ 0x80u
#define CODEGEN_MAC64_COMMANDSEGMENT_PROT_EXECUTE_ONLY \
  (CODEGEN_MAC64_COMMANDSEGMENT_PROT_EXECUTE | \
    CODEGEN_MAC64_COMMANDSEGMENT_PROT_STRIP_READ)

namespace let {
  class CodegenMac64CommandSegment {
   public:
    uint64 vmAddr = 0;
    uint64 vmSize = 0;
    uint64 fileOffset = 0;
    uint64 fileSize = 0;
    int32 maxProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_NONE;
    int32 initProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_NONE;
    uint32 flags = CODEGEN_MAC64_COMMANDSEGMENT_FLAG_UNKNOWN;

    explicit CodegenMac64CommandSegment() = default;
    explicit CodegenMac64CommandSegment(const String &);

    void addSec(const CodegenMac64Section &);
    uint32 getSize();
    Binary toBinary();

   private:
    String segName;
    uint32 segNameSize = 16;
    std::vector<CodegenMac64Section> secs;
    uint32 secsCount = 0;
  };
}

#endif
