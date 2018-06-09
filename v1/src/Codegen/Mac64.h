/**
 * @created_at: 2019-06-29 20:24:29
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

#ifndef SRC_CODEGEN_MAC64_H
#define SRC_CODEGEN_MAC64_H

#include "Mac64Command.h"
#include "Mac64Header.h"
#include "../AST.h"
#include "../Arguments.h"
#include "../Binary.h"

namespace let {
  class CodegenMac64 {
   public:
    Binary binary;

    explicit CodegenMac64(const AST &);

    void addCommandDataInCode();
    void addCommandDyLdInfoOnly();
    void addCommandDySymTab();
    void addCommandLoadDyLib();
    void addCommandLoadDyLinker();
    void addCommandMain();
    void addCommandSegmentData();
    void addCommandSegmentLinkEdit();
    void addCommandSegmentPagezero();
    void addCommandSegmentText();
    void addCommandSymTab();
    void addCommandSourceVersion();
    void addCommandVersionMinMacOSX();
    void addHeader();
    void generateBinary();
    void processAST(const AST &);

   private:
    std::vector<CodegenMac64Command> cmds;
    Binary dyLdInfo;
    CodegenMac64Header header;
    Binary secData;
    uint64 secDataAddress = 0;
    uint32 secDataOffset = 0;
    uint64 secDataSize = 0;
    Binary secText;
    uint64 secTextAddress = 0;
    uint32 secTextOffset = 0;
    uint64 secTextSize = 0;
    Binary strTab;
    Binary symTab;
  };
}

#endif
