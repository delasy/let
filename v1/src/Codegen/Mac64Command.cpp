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

#include "Mac64Command.h"

namespace let {
  CodegenMac64Command::CodegenMac64Command(uint32 cmd) {
    this->cmd = cmd;
  }

  uint32 CodegenMac64Command::getSize() {
    uint32 size = 0;

    size += sizeof(this->cmd);
    size += sizeof(this->cmdSize);

    switch (this->cmd) {
      case CODEGEN_MAC64_COMMAND_DATA_IN_CODE: {
        size += this->linkEdit.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_DYLD_INFO_ONLY: {
        size += this->dyLdInfo.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_DYSYMTAB: {
        size += this->dySymTab.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_LOAD_DYLIB: {
        size += this->dyLib.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_LOAD_DYLINKER: {
        size += this->dyLinker.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_MAIN: {
        size += this->entryPoint.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SEGMENT_64: {
        size += this->segment.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SYMTAB: {
        size += this->symTab.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SOURCE_VERSION: {
        size += this->sourceVersion.getSize();

        break;
      }
      case CODEGEN_MAC64_COMMAND_VERSION_MIN_MACOSX: {
        size += this->versionMin.getSize();

        break;
      }
    }

    return size;
  }

  Binary CodegenMac64Command::toBinary() {
    Binary binary;

    binary += this->cmd;
    binary += this->getSize();

    switch (this->cmd) {
      case CODEGEN_MAC64_COMMAND_DATA_IN_CODE: {
        binary += this->linkEdit.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_DYLD_INFO_ONLY: {
        binary += this->dyLdInfo.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_DYSYMTAB: {
        binary += this->dySymTab.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_LOAD_DYLIB: {
        binary += this->dyLib.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_LOAD_DYLINKER: {
        binary += this->dyLinker.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_MAIN: {
        binary += this->entryPoint.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SEGMENT_64: {
        binary += this->segment.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SYMTAB: {
        binary += this->symTab.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_SOURCE_VERSION: {
        binary += this->sourceVersion.toBinary();

        break;
      }
      case CODEGEN_MAC64_COMMAND_VERSION_MIN_MACOSX: {
        binary += this->versionMin.toBinary();

        break;
      }
    }

    return binary;
  }
}
