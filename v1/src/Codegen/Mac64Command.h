/**
 * @created_at: 2019-06-30 14:16:49
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

#ifndef SRC_CODEGEN_MAC64COMMAND_H
#define SRC_CODEGEN_MAC64COMMAND_H

#include "Mac64CommandDyLdInfo.h"
#include "Mac64CommandDyLib.h"
#include "Mac64CommandDyLinker.h"
#include "Mac64CommandDySymTab.h"
#include "Mac64CommandEntryPoint.h"
#include "Mac64CommandLinkEdit.h"
#include "Mac64CommandSegment.h"
#include "Mac64CommandSourceVersion.h"
#include "Mac64CommandSymTab.h"
#include "Mac64CommandVersionMin.h"

#define CODEGEN_MAC64_COMMAND_REQ_DYLD 0x80000000u
#define CODEGEN_MAC64_COMMAND_UNKNOWN 0x0u
#define CODEGEN_MAC64_COMMAND_SEGMENT 0x1u
#define CODEGEN_MAC64_COMMAND_SYMTAB 0x2u
#define CODEGEN_MAC64_COMMAND_SYMSEG 0x3u
#define CODEGEN_MAC64_COMMAND_THREAD 0x4u
#define CODEGEN_MAC64_COMMAND_UNIXTHREAD 0x5u
#define CODEGEN_MAC64_COMMAND_LOADFVMLIB 0x6u
#define CODEGEN_MAC64_COMMAND_IDFVMLIB 0x7u
#define CODEGEN_MAC64_COMMAND_IDENT 0x8u
#define CODEGEN_MAC64_COMMAND_FVMFILE 0x9u
#define CODEGEN_MAC64_COMMAND_PREPAGE 0xAu
#define CODEGEN_MAC64_COMMAND_DYSYMTAB 0xBu
#define CODEGEN_MAC64_COMMAND_LOAD_DYLIB 0xCu
#define CODEGEN_MAC64_COMMAND_ID_DYLIB 0xDu
#define CODEGEN_MAC64_COMMAND_LOAD_DYLINKER 0xEu
#define CODEGEN_MAC64_COMMAND_ID_DYLINKER 0xFu
#define CODEGEN_MAC64_COMMAND_PREBOUND_DYLIB 0x10u
#define CODEGEN_MAC64_COMMAND_ROUTINES 0x11u
#define CODEGEN_MAC64_COMMAND_SUB_FRAMEWORK 0x12u
#define CODEGEN_MAC64_COMMAND_SUB_UMBRELLA 0x13u
#define CODEGEN_MAC64_COMMAND_SUB_CLIENT 0x14u
#define CODEGEN_MAC64_COMMAND_SUB_LIBRARY 0x15u
#define CODEGEN_MAC64_COMMAND_TWOLEVEL_HINTS 0x16u
#define CODEGEN_MAC64_COMMAND_PREBIND_CKSUM 0x17u
#define CODEGEN_MAC64_COMMAND_LOAD_WEAK_DYLIB \
  (0x18u | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_SEGMENT_64 0x19u
#define CODEGEN_MAC64_COMMAND_ROUTINES_64 0x1Au
#define CODEGEN_MAC64_COMMAND_UUID 0x1Bu
#define CODEGEN_MAC64_COMMAND_RPATH (0x1Cu | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_CODE_SIGNATURE 0x1Du
#define CODEGEN_MAC64_COMMAND_SEGMENT_SPLIT_INFO 0x1Eu
#define CODEGEN_MAC64_COMMAND_REEXPORT_DYLIB \
  (0x1Fu | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_LAZY_LOAD_DYLIB 0x20u
#define CODEGEN_MAC64_COMMAND_ENCRYPTION_INFO 0x21u
#define CODEGEN_MAC64_COMMAND_DYLD_INFO 0x22u
#define CODEGEN_MAC64_COMMAND_DYLD_INFO_ONLY \
  (0x22u | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_LOAD_UPWARD_DYLIB \
  (0x23u | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_VERSION_MIN_MACOSX 0x24u
#define CODEGEN_MAC64_COMMAND_VERSION_MIN_IPHONEOS 0x25u
#define CODEGEN_MAC64_COMMAND_FUNCTION_STARTS 0x26u
#define CODEGEN_MAC64_COMMAND_DYLD_ENVIRONMENT 0x27u
#define CODEGEN_MAC64_COMMAND_MAIN (0x28u | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_DATA_IN_CODE 0x29u
#define CODEGEN_MAC64_COMMAND_SOURCE_VERSION 0x2Au
#define CODEGEN_MAC64_COMMAND_DYLIB_CODE_SIGN_DRS 0x2Bu
#define CODEGEN_MAC64_COMMAND_ENCRYPTION_INFO_64 0x2Cu
#define CODEGEN_MAC64_COMMAND_LINKER_OPTION 0x2Du
#define CODEGEN_MAC64_COMMAND_LINKER_OPTIMIZATION_HINT 0x2Eu
#define CODEGEN_MAC64_COMMAND_VERSION_MIN_TVOS 0x2Fu
#define CODEGEN_MAC64_COMMAND_VERSION_MIN_WATCHOS 0x30u
#define CODEGEN_MAC64_COMMAND_NOTE 0x31u
#define CODEGEN_MAC64_COMMAND_BUILD_VERSION 0x32u
#define CODEGEN_MAC64_COMMAND_DYLD_EXPORTS_TRIE \
  (0x33u | CODEGEN_MAC64_COMMAND_REQ_DYLD)
#define CODEGEN_MAC64_COMMAND_DYLD_CHAINED_FIXUPS \
  (0x34u | CODEGEN_MAC64_COMMAND_REQ_DYLD)

namespace let {
  class CodegenMac64Command {
   public:
    CodegenMac64CommandDyLdInfo dyLdInfo;
    CodegenMac64CommandDyLib dyLib;
    CodegenMac64CommandDyLinker dyLinker;
    CodegenMac64CommandDySymTab dySymTab;
    CodegenMac64CommandEntryPoint entryPoint;
    CodegenMac64CommandLinkEdit linkEdit;
    CodegenMac64CommandSegment segment;
    CodegenMac64CommandSourceVersion sourceVersion;
    CodegenMac64CommandSymTab symTab;
    CodegenMac64CommandVersionMin versionMin;

    explicit CodegenMac64Command(uint32);

    uint32 getSize();
    Binary toBinary();

   private:
    uint32 cmd = CODEGEN_MAC64_COMMAND_UNKNOWN;
    uint32 cmdSize = 0;
  };
}

#endif
