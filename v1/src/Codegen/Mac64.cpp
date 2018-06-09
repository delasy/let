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

#include "Mac64.h"
#include "../Utils.h"
#include "../VariableMap.h"

#include "../version.h"

namespace let {
  CodegenMac64::CodegenMac64(const AST &ast) {
    this->processAST(ast);
    this->addCommandSegmentPagezero();
    this->addCommandSegmentText();
    this->addCommandSegmentData();
    this->addCommandSegmentLinkEdit();
    this->addCommandDyLdInfoOnly();
    this->addCommandSymTab();
    this->addCommandDySymTab();
    this->addCommandLoadDyLinker();
    this->addCommandVersionMinMacOSX();
    this->addCommandSourceVersion();
    this->addCommandMain();
    this->addCommandLoadDyLib();
    this->addCommandDataInCode();
    this->addHeader();
    this->generateBinary();
  }

  void CodegenMac64::addCommandDataInCode() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_DATA_IN_CODE);

    cmd.linkEdit.dataOffset = 0x2000 + this->symTab.getSize();

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandDyLdInfoOnly() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_DYLD_INFO_ONLY);

    cmd.dyLdInfo.exportOffset = 0x2000;
    cmd.dyLdInfo.exportSize = this->dyLdInfo.getSize();

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandDySymTab() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_DYSYMTAB);

    cmd.dySymTab.defExtSymCount = 2;
    cmd.dySymTab.undefExtSymIndex = 2;
    cmd.dySymTab.undefExtSymCount = 1;

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandLoadDyLib() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_LOAD_DYLIB);

    cmd.dyLib.dyLib.name = CodegenMac64String(
      "/usr/lib/libSystem.B.dylib", 32
    );

    cmd.dyLib.dyLib.name.offset = 24;
    cmd.dyLib.dyLib.timestamp = 2;
    cmd.dyLib.dyLib.currentVersion = Utils::versionA16B8C8("1252.250.1");
    cmd.dyLib.dyLib.compatibilityVersion = Utils::versionA16B8C8("1.0.0");

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandLoadDyLinker() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_LOAD_DYLINKER);

    cmd.dyLinker.name = CodegenMac64String("/usr/lib/dyld", 20);
    cmd.dyLinker.name.offset = 12;

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandMain() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_MAIN);

    cmd.entryPoint.entryOffset = 0x1000 - this->secText.getSize();

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSegmentData() {
    CodegenMac64Section sec(
      CODEGEN_MAC64_SECTION_DATA, CODEGEN_MAC64_COMMANDSEGMENT_DATA
    );

    sec.address = this->secDataAddress;
    sec.size = this->secDataSize;
    sec.offset = this->secDataOffset;
    sec.flags = CODEGEN_MAC64_SECTION_FLAG_REGULAR;

    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SEGMENT_64);

    cmd.segment = CodegenMac64CommandSegment(
      CODEGEN_MAC64_COMMANDSEGMENT_DATA
    );

    cmd.segment.vmAddr = 0x2000;
    cmd.segment.vmSize = 0x1000;
    cmd.segment.fileOffset = 0x1000;
    cmd.segment.fileSize = 0x1000;
    cmd.segment.maxProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_ALL;
    cmd.segment.initProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_DEFAULT;

    cmd.segment.addSec(sec);
    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSegmentLinkEdit() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SEGMENT_64);

    cmd.segment = CodegenMac64CommandSegment(
      CODEGEN_MAC64_COMMANDSEGMENT_LINKEDIT
    );

    cmd.segment.vmAddr = 0x3000;
    cmd.segment.vmSize = 0x1000;
    cmd.segment.fileOffset = 0x2000;
    cmd.segment.fileSize = 0x90;
    cmd.segment.maxProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_ALL;
    cmd.segment.initProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_READ;

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSegmentPagezero() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SEGMENT_64);

    cmd.segment = CodegenMac64CommandSegment(
      CODEGEN_MAC64_COMMANDSEGMENT_PAGEZERO
    );

    cmd.segment.vmSize = 0x1000;

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSegmentText() {
    CodegenMac64Section sec(
      CODEGEN_MAC64_SECTION_TEXT, CODEGEN_MAC64_COMMANDSEGMENT_TEXT
    );

    sec.address = this->secTextAddress;
    sec.size = this->secTextSize;
    sec.offset = this->secTextOffset;

    sec.flags = CODEGEN_MAC64_SECTION_FLAG_REGULAR |
      CODEGEN_MAC64_SECTION_FLAG_ATTR_PURE_INSTRUCTIONS |
      CODEGEN_MAC64_SECTION_FLAG_ATTR_SOME_INSTRUCTIONS;

    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SEGMENT_64);

    cmd.segment = CodegenMac64CommandSegment(
      CODEGEN_MAC64_COMMANDSEGMENT_TEXT
    );

    cmd.segment.vmAddr = 0x1000;
    cmd.segment.vmSize = 0x1000;
    cmd.segment.fileSize = 0x1000;
    cmd.segment.maxProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_ALL;

    cmd.segment.initProt = CODEGEN_MAC64_COMMANDSEGMENT_PROT_READ |
      CODEGEN_MAC64_COMMANDSEGMENT_PROT_EXECUTE;

    cmd.segment.addSec(sec);
    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSymTab() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SYMTAB);

    cmd.symTab.symTabOffset = 0x2000 + this->dyLdInfo.getSize();
    cmd.symTab.symTabCount = 3;
    cmd.symTab.strTabOffset = cmd.symTab.symTabOffset + this->symTab.getSize();
    cmd.symTab.strTabSize = this->symTab.getSize();

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandSourceVersion() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_SOURCE_VERSION);

    cmd.sourceVersion.version = Utils::versionA24B10C10D10E10(VERSION);

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addCommandVersionMinMacOSX() {
    CodegenMac64Command cmd(CODEGEN_MAC64_COMMAND_VERSION_MIN_MACOSX);

    cmd.versionMin.version = Utils::versionA16B8C8("10.8.0");
    cmd.versionMin.versionSDK = Utils::versionA16B8C8("10.14.0");

    this->cmds.push_back(cmd);
  }

  void CodegenMac64::addHeader() {
    this->header.cpuType = CODEGEN_MAC_64_HEADER_CPU_TYPE_X86_64;

    this->header.cpuSubType = CODEGEN_MAC_64_HEADER_CPU_SUBTYPE_LIB64 |
      CODEGEN_MAC_64_HEADER_CPU_SUBTYPE_X86_64_ALL;

    this->header.fileType = CODEGEN_MAC_64_HEADER_FILE_TYPE_EXECUTE;
    this->header.cmdsCount += this->cmds.size();

    for (CodegenMac64Command cmd : this->cmds) {
      this->header.cmdsSize += cmd.getSize();
    }

    this->header.flags = CODEGEN_MAC_64_HEADER_FLAG_NOUNDEFS |
      CODEGEN_MAC_64_HEADER_FLAG_DYLDLINK |
      CODEGEN_MAC_64_HEADER_FLAG_TWOLEVEL;
  }

  void CodegenMac64::generateBinary() {
    this->binary += this->header.toBinary();

    for (CodegenMac64Command cmd : this->cmds) {
      this->binary += cmd.toBinary();
    }

    this->binary.appendZero(
      0x1000 - this->binary.getSize() - this->secText.getSize()
    );

    this->binary += this->secText;
    this->binary += this->secData;

    this->binary.appendZero(0x2000 - this->binary.getSize());

    this->binary += this->dyLdInfo;
    this->binary += this->symTab;
    this->binary += this->strTab;
  }

  void CodegenMac64::processAST(const AST &ast) {
    VariableMap varMap;

    for (const Parser &parser : ast.parsers) {
      if (parser.token == PARSER_ASSIGN_EXPR) {
        ParserAssignExpr assignExpr = parser.assignExpr;
        std::vector<int8> value;

        if (assignExpr.expr.token == PARSER_EXPR_ID) {
          VariableMapItem item = varMap.get(assignExpr.expr.id.l.value);

          if (!item.isEmpty()) {
            for (uint32 i = 0; i < item.size; i++) {
              value.push_back(this->secData[item.addressLocal + i]);
            }
          }
        } else if (assignExpr.expr.token == PARSER_EXPR_LITERAL) {
          String preValue = assignExpr.expr.literal.l.value;

          for (int8 ch : preValue) {
            value.push_back(ch);
          }
        }

        if (value.empty()) {
          continue;
        }

        String name = assignExpr.id.l.value;

        varMap.set(name, value.size());

        this->secData += value;
      } else if (parser.token == PARSER_CALL_EXPR) {
        ParserCallExpr callExpr = parser.callExpr;
        String funcName = callExpr.id.l.value;

        if (funcName == "puts" || funcName == "print") {
          std::vector<int8> str;

          for (const ParserExpr &expr : callExpr.argList.exprs) {
            std::vector<int8> value;

            if (expr.token == PARSER_EXPR_ID) {
              VariableMapItem item = varMap.get(expr.id.l.value);

              if (item.isEmpty()) {
                String preValue = "nil";

                for (int8 ch : preValue) {
                  value.push_back(ch);
                }
              } else {
                for (uint32 i = 0; i < item.size; i++) {
                  value.push_back(this->secData[item.addressLocal + i]);
                }
              }
            } else if (expr.token == PARSER_EXPR_LITERAL) {
              String preValue = expr.literal.l.value;

              for (int8 ch : preValue) {
                value.push_back(ch);
              }
            }

            if (value.empty()) {
              continue;
            }

            for (int8 ch : value) {
              str.push_back(ch);
            }
          }

          if (funcName == "puts") {
            uint32 newLineLen = sizeof(OS_EOL) / sizeof(uint8);

            for (uint32 i = 0; i < newLineLen - 1; i++) {
              str.push_back(OS_EOL[i]);
            }
          }

          if (str.empty()) {
            continue;
          }

          uint32 strSize = str.size();
          VariableMapItem item = varMap.set("", strSize);

          for (int8 ch : str) {
            this->secData += ch;
          }

          std::vector<uint8> printMovl$0x2000004ToEax = {
            0xB8, 0x04, 0x00, 0x00, 0x02
          };

          this->secText += printMovl$0x2000004ToEax;

          std::vector<uint8> printMovl$0x1ToEdi = {
            0xBF, 0x01, 0x00, 0x00, 0x00
          };

          this->secText += printMovl$0x1ToEdi;

          std::vector<uint8> printMovabsq$xToRsi = {
            0x48, 0xBE
          };

          this->secText += printMovabsq$xToRsi;
          this->secText += item.address;

          std::vector<uint8> printMovl$xToEdx = {
            0xBA
          };

          this->secText += printMovl$xToEdx;
          this->secText += strSize;

          std::vector<uint8> printSyscall = {
            0x0F, 0x05
          };

          this->secText += printSyscall;
        }
      }
    }

    std::vector<uint8> secTextEndMovl$0x2000001ToEax = {
      0xB8, 0x01, 0x00, 0x00, 0x02
    };

    this->secText += secTextEndMovl$0x2000001ToEax;

    std::vector<uint8> secTextEndMovl$0x0ToEdi = {
      0xBF, 0x00, 0x00, 0x00, 0x00
    };

    this->secText += secTextEndMovl$0x0ToEdi;

    std::vector<uint8> secTextEndSyscall = {
      0x0F, 0x05
    };

    this->secText += secTextEndSyscall;

    this->secDataAddress = 0x2000;
    this->secDataOffset = 0x1000;
    this->secDataSize = this->secData.getSize();
    this->secTextAddress = 0x2000 - this->secText.getSize();
    this->secTextOffset = 0x1000 - this->secText.getSize();
    this->secTextSize = this->secText.getSize();

    std::vector<uint8> dyLdInfoFirst = {
      0x00,
      0x01,
      0x5F, 0x00,
      0x05
    };

    this->dyLdInfo += dyLdInfoFirst;

    std::vector<uint8> dyLdInfoSecond = {
      0x00,
      0x02,
      0x5F, 0x6D, 0x68, 0x5F, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x65, 0x5F,
      0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00,
      0x21,
      0x6D, 0x61, 0x69, 0x6E, 0x00,
      0x25
    };

    this->dyLdInfo += dyLdInfoSecond;

    std::vector<uint8> dyLdInfoThird = {
      0x02,
      0x00,
      0x00,
      0x00
    };

    this->dyLdInfo += dyLdInfoThird;

    std::vector<uint8> dyLdInfoFourthStart = {
      0x03,
      0x00
    };

    uint16 secTextAddressUint16 = this->secTextAddress;

    std::vector<uint8> dyLdInfoFourthEnd = {
      0x00
    };

    this->dyLdInfo += dyLdInfoFourthStart;
    this->dyLdInfo += secTextAddressUint16;
    this->dyLdInfo += dyLdInfoFourthEnd;

    this->dyLdInfo.appendZero(6);

    std::vector<uint8> symbolTableFirst = {
      0x02, 0x00, 0x00, 0x00,
      0x03,
      0x01,
      0x10, 0x00,
      0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    this->symTab += symbolTableFirst;

    std::vector<uint8> symbolTableSecondStart = {
      0x16, 0x00, 0x00, 0x00,
      0x0F,
      0x01,
      0x00, 0x00
    };

    this->symTab += symbolTableSecondStart;
    this->symTab += this->secTextAddress;

    std::vector<uint8> symbolTableThird = {
      0x1C, 0x00, 0x00, 0x00,
      0x01,
      0x00,
      0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    this->symTab += symbolTableThird;

    std::vector<uint8> stringTable = {
      0x20, 0x00,

      0x5F, 0x5F, 0x6D, 0x68, 0x5F, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x65,
      0x5F, 0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00,

      0x5F, 0x6D, 0x61, 0x69, 0x6E, 0x00,

      0x64, 0x79, 0x6C, 0x64, 0x5F, 0x73, 0x74, 0x75, 0x62, 0x5F, 0x62, 0x69,
      0x6E, 0x64, 0x65, 0x72, 0x00,

      0x00, 0x00, 0x00
    };

    this->strTab += stringTable;
  }
}
