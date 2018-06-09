#include "CodegenMac64.hpp"
#include "Exception.hpp"
#include "VariableMap.hpp"
#include "Version.hpp"

CodegenMac64::CodegenMac64(const AST &ast) {
  this->processAST(ast);
  this->addCmdSegPagezero();
  this->addCmdSegText();
  this->addCmdSegData();
  this->addCmdSegLinkEdit();
  this->addCmdDyLdInfoOnly();
  this->addCmdSymTab();
  this->addCmdDySymTab();
  this->addCmdLoadDyLinker();
  this->addCmdVersionMinMacOSX();
  this->addCmdSourceVersion();
  this->addCmdMain();
  this->addCmdLoadDyLib();
  this->addCmdDataInCode();
  this->addHeader();
  this->generateBinary();
}

void CodegenMac64::addCmdDataInCode() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::DATA_IN_CODE);

  cmd.linkEdit.dataOffset = 0x2000 + this->_symTab.getSize();

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdDyLdInfoOnly() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::DYLD_INFO_ONLY);

  cmd.dyLdInfo.exportOffset = this->_secDataAddress;
  cmd.dyLdInfo.exportSize = this->_dyLdInfo.getSize();

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdDySymTab() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::DYSYMTAB);

  cmd.dySymTab.defExtSymCount = 2;
  cmd.dySymTab.undefExtSymIndex = 2;
  cmd.dySymTab.undefExtSymCount = 1;

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdLoadDyLib() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::LOAD_DYLIB);

  cmd.dyLib.dyLib.compatibilityVersion = Version::a16b8c8("1.0.0");
  cmd.dyLib.dyLib.currentVersion = Version::a16b8c8("1252.250.1");
  cmd.dyLib.dyLib.name.string = "/usr/lib/libSystem.B.dylib";
  cmd.dyLib.dyLib.name.stringSize = 32;
  cmd.dyLib.dyLib.name.offset = 24;
  cmd.dyLib.dyLib.timestamp = 2;

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdLoadDyLinker() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::LOAD_DYLINKER);

  cmd.dyLinker.name.string = "/usr/lib/dyld";
  cmd.dyLinker.name.stringSize = 20;
  cmd.dyLinker.name.offset = 12;

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdMain() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::MAIN);

  cmd.entryPoint.entryOffset = 0x1000 - this->_secText.getSize();

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSegData() {
  CodegenMac64Sec sec;

  sec.secName = CodegenMac64Sec::DATA;
  sec.segName = CodegenMac64CmdSeg::DATA;
  sec.address = this->_secDataAddress;
  sec.offset = this->_secDataOffset;
  sec.flags = CodegenMac64Sec::FLAG_REGULAR;
  sec.size = this->_secDataSize;

  CodegenMac64Cmd cmd(CodegenMac64Cmd::SEG_64);

  cmd.seg.segName = CodegenMac64CmdSeg::DATA;
  cmd.seg.fileOffset = 0x1000;
  cmd.seg.fileSize = 0x1000;
  cmd.seg.initProt = CodegenMac64CmdSeg::PROT_DEFAULT;
  cmd.seg.maxProt = CodegenMac64CmdSeg::PROT_ALL;
  cmd.seg.vmAddr = this->_secDataAddress;
  cmd.seg.vmSize = 0x1000;
  cmd.seg.secs.push_back(sec);

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSegLinkEdit() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::SEG_64);

  cmd.seg.segName = CodegenMac64CmdSeg::LINKEDIT;
  cmd.seg.fileOffset = this->_secDataAddress;
  cmd.seg.fileSize = 0x90;
  cmd.seg.initProt = CodegenMac64CmdSeg::PROT_READ;
  cmd.seg.maxProt = CodegenMac64CmdSeg::PROT_ALL;
  cmd.seg.vmAddr = 0x3000;
  cmd.seg.vmSize = 0x1000;

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSegPagezero() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::SEG_64);

  cmd.seg.segName = CodegenMac64CmdSeg::PAGEZERO;
  cmd.seg.vmSize = 0x1000;

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSegText() {
  CodegenMac64Sec sec;

  sec.secName = CodegenMac64Sec::TEXT;
  sec.segName = CodegenMac64CmdSeg::TEXT;
  sec.address = this->_secTextAddress;
  sec.flags = CodegenMac64Sec::FLAG_REGULAR |
    CodegenMac64Sec::FLAG_ATTR_PURE_INSTRUCTIONS |
    CodegenMac64Sec::FLAG_ATTR_SOME_INSTRUCTIONS;
  sec.offset = this->_secTextOffset;
  sec.size = this->_secTextSize;

  CodegenMac64Cmd cmd(CodegenMac64Cmd::SEG_64);

  cmd.seg.segName = CodegenMac64CmdSeg::TEXT;
  cmd.seg.fileSize = 0x1000;
  cmd.seg.initProt = CodegenMac64CmdSeg::PROT_READ |
    CodegenMac64CmdSeg::PROT_EXECUTE;
  cmd.seg.maxProt = CodegenMac64CmdSeg::PROT_ALL;
  cmd.seg.vmAddr = 0x1000;
  cmd.seg.vmSize = 0x1000;
  cmd.seg.secs.push_back(sec);

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSymTab() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::SYMTAB);

  cmd.symTab.symTabOffset = 0x2000 + this->_dyLdInfo.getSize();
  cmd.symTab.symTabCount = 3;
  cmd.symTab.strTabOffset = cmd.symTab.symTabOffset + this->_symTab.getSize();
  cmd.symTab.strTabSize = this->_symTab.getSize();

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdSourceVersion() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::SOURCE_VERSION);

  cmd.sourceVersion.version = Version::a24b10c10d10e10(Version::NUMBER);

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addCmdVersionMinMacOSX() {
  CodegenMac64Cmd cmd(CodegenMac64Cmd::VERSION_MIN_MACOSX);

  cmd.versionMin.version = Version::a16b8c8("10.8.0");
  cmd.versionMin.versionSDK = Version::a16b8c8("10.14.0");

  this->_cmds.push_back(cmd);
}

void CodegenMac64::addHeader() {
  this->_header.magic = CodegenMac64Header::MAGIC;
  this->_header.cpuType = CodegenMac64Header::CPU_TYPE_X86_64;
  this->_header.cpuSubType = CodegenMac64Header::CPU_SUBTYPE_LIB64 |
    CodegenMac64Header::CPU_SUBTYPE_X86_64_ALL;
  this->_header.fileType = CodegenMac64Header::FILE_TYPE_EXECUTE;
  this->_header.flags = CodegenMac64Header::FLAG_NOUNDEFS |
    CodegenMac64Header::FLAG_DYLDLINK |
    CodegenMac64Header::FLAG_TWOLEVEL;
  this->_header.cmdsCount = this->_cmds.size();

  for (CodegenMac64Cmd cmd : this->_cmds) {
    this->_header.cmdsSize += cmd.getSize();
  }
}

void CodegenMac64::generateBinary() {
  this->binary += this->_header.toBinary();

  for (CodegenMac64Cmd cmd : this->_cmds) {
    this->binary += cmd.toBinary();
  }

  this->binary.appendZero(
    0x1000 - this->binary.getSize() - this->_secText.getSize()
  );

  this->binary += this->_secText;
  this->binary += this->_secData;
  this->binary.appendZero(this->_secDataAddress - this->binary.getSize());
  this->binary += this->_dyLdInfo;
  this->binary += this->_symTab;
  this->binary += this->_strTab;
}

void CodegenMac64::processAST(const AST &ast) {
  VariableMap varMap;

  for (const Parser &parser : ast.parsers) {
    if (parser.token == PARSER_ASSIGN_EXPR) {
      ParserAssignExpr assignExpr = parser.assignExpr;
      std::vector<char> value;

      if (assignExpr.expr.token == PARSER_EXPR_ID) {
        VariableMapItem item = varMap.get(assignExpr.expr.id.l.value);

        if (!item.isEmpty()) {
          for (unsigned int i = 0; i < item.size; i++) {
            value.push_back(this->_secData[item.addressLocal + i]);
          }
        }
      } else if (assignExpr.expr.token == PARSER_EXPR_LITERAL) {
        std::string preValue = assignExpr.expr.literal.l.value;

        for (char ch : preValue) {
          value.push_back(ch);
        }
      }

      if (value.empty()) {
        continue;
      }

      this->_secData += value;
      varMap.set(assignExpr.id.l.value, value.size());
    } else if (parser.token == PARSER_CALL_EXPR) {
      ParserCallExpr callExpr = parser.callExpr;
      std::string funcName = callExpr.id.l.value;

      if (funcName == "print") {
        std::vector<char> str;

        for (const ParserExpr &expr : callExpr.argList.exprs) {
          std::vector<char> value;

          if (expr.token == PARSER_EXPR_ID) {
            VariableMapItem item = varMap.get(expr.id.l.value);

            if (item.isEmpty()) {
              std::string preValue = "nil";

              for (char ch : preValue) {
                value.push_back(ch);
              }
            } else {
              for (unsigned int i = 0; i < item.size; i++) {
                value.push_back(this->_secData[item.addressLocal + i]);
              }
            }
          } else if (expr.token == PARSER_EXPR_LITERAL) {
            std::string preValue = expr.literal.l.value;

            for (char ch : preValue) {
              value.push_back(ch);
            }
          }

          if (value.empty()) {
            continue;
          }

          for (char ch : value) {
            str.push_back(ch);
          }
        }

        if (str.empty()) {
          continue;
        }

        unsigned int strSize = str.size();
        VariableMapItem item = varMap.set("", strSize);

        for (char ch : str) {
          this->_secData += ch;
        }

        this->_secText += std::vector<unsigned char> {
          0xB8, 0x04, 0x00, 0x00, 0x02,
          0xBF, 0x01, 0x00, 0x00, 0x00,
          0x48, 0xBE
        };

        this->_secText += item.address;

        this->_secText += std::vector<unsigned char> {
          0xBA
        };

        this->_secText += strSize;

        this->_secText += std::vector<unsigned char> {
          0x0F, 0x05
        };
      } else {
        std::string errorMessage;

        errorMessage += "Call to undefined function '";
        errorMessage += funcName;
        errorMessage += "'";

        throw Exception(errorMessage);
      }
    }
  }

  this->_secText += std::vector<unsigned char> {
    0xB8, 0x01, 0x00, 0x00, 0x02,
    0xBF, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x05
  };

  this->_secDataAddress = 0x2000;
  this->_secDataOffset = 0x1000;
  this->_secDataSize = this->_secData.getSize();
  this->_secTextAddress = 0x2000 - this->_secText.getSize();
  this->_secTextOffset = 0x1000 - this->_secText.getSize();
  this->_secTextSize = this->_secText.getSize();

  this->_dyLdInfo += std::vector<unsigned char> {
    0x00,
    0x01,
    0x5F, 0x00,
    0x05,

    0x00,
    0x02,
    0x5F, 0x6D, 0x68, 0x5F, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x65, 0x5F,
    0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00,
    0x21,
    0x6D, 0x61, 0x69, 0x6E, 0x00,
    0x25,

    0x02,
    0x00,
    0x00,
    0x00,

    0x03,
    0x00
  };

  this->_dyLdInfo += (unsigned short) this->_secTextAddress;

  this->_dyLdInfo += std::vector<unsigned char> {
    0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  this->_symTab += std::vector<unsigned char> {
    0x02, 0x00, 0x00, 0x00,
    0x03,
    0x01,
    0x10, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x16, 0x00, 0x00, 0x00,
    0x0F,
    0x01,
    0x00, 0x00
  };

  this->_symTab += this->_secTextAddress;

  this->_symTab += std::vector<unsigned char> {
    0x1C, 0x00, 0x00, 0x00,
    0x01,
    0x00,
    0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  this->_strTab += std::vector<unsigned char> {
    0x20u, 0x00u,

    0x5F, 0x5F, 0x6D, 0x68, 0x5F, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x65,
    0x5F, 0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00,

    0x5F, 0x6D, 0x61, 0x69, 0x6E, 0x00,

    0x64, 0x79, 0x6C, 0x64, 0x5F, 0x73, 0x74, 0x75, 0x62, 0x5F, 0x62, 0x69,
    0x6E, 0x64, 0x65, 0x72, 0x00,

    0x00, 0x00, 0x00
  };
}

CodegenMac64Cmd::CodegenMac64Cmd(unsigned int cmd) {
  this->cmd = cmd;
}

unsigned int CodegenMac64Cmd::getSize() const {
  unsigned int size = 0;

  size += sizeof(this->cmd);
  size += sizeof(unsigned int);

  switch (this->cmd) {
    case CodegenMac64Cmd::DATA_IN_CODE: {
      size += this->linkEdit.getSize();
      break;
    }
    case CodegenMac64Cmd::DYLD_INFO_ONLY: {
      size += this->dyLdInfo.getSize();
      break;
    }
    case CodegenMac64Cmd::DYSYMTAB: {
      size += this->dySymTab.getSize();
      break;
    }
    case CodegenMac64Cmd::LOAD_DYLIB: {
      size += this->dyLib.getSize();
      break;
    }
    case CodegenMac64Cmd::LOAD_DYLINKER: {
      size += this->dyLinker.getSize();
      break;
    }
    case CodegenMac64Cmd::MAIN: {
      size += this->entryPoint.getSize();
      break;
    }
    case CodegenMac64Cmd::SEG_64: {
      size += this->seg.getSize();
      break;
    }
    case CodegenMac64Cmd::SYMTAB: {
      size += this->symTab.getSize();
      break;
    }
    case CodegenMac64Cmd::SOURCE_VERSION: {
      size += this->sourceVersion.getSize();
      break;
    }
    case CodegenMac64Cmd::VERSION_MIN_MACOSX: {
      size += this->versionMin.getSize();
      break;
    }
  }

  return size;
}

Binary CodegenMac64Cmd::toBinary() const {
  Binary binary;

  binary += this->cmd;
  binary += this->getSize();

  switch (this->cmd) {
    case CodegenMac64Cmd::DATA_IN_CODE: {
      binary += this->linkEdit.toBinary();
      break;
    }
    case CodegenMac64Cmd::DYLD_INFO_ONLY: {
      binary += this->dyLdInfo.toBinary();
      break;
    }
    case CodegenMac64Cmd::DYSYMTAB: {
      binary += this->dySymTab.toBinary();
      break;
    }
    case CodegenMac64Cmd::LOAD_DYLIB: {
      binary += this->dyLib.toBinary();
      break;
    }
    case CodegenMac64Cmd::LOAD_DYLINKER: {
      binary += this->dyLinker.toBinary();
      break;
    }
    case CodegenMac64Cmd::MAIN: {
      binary += this->entryPoint.toBinary();
      break;
    }
    case CodegenMac64Cmd::SEG_64: {
      binary += this->seg.toBinary();
      break;
    }
    case CodegenMac64Cmd::SYMTAB: {
      binary += this->symTab.toBinary();
      break;
    }
    case CodegenMac64Cmd::SOURCE_VERSION: {
      binary += this->sourceVersion.toBinary();
      break;
    }
    case CodegenMac64Cmd::VERSION_MIN_MACOSX: {
      binary += this->versionMin.toBinary();
      break;
    }
  }

  return binary;
}

unsigned int CodegenMac64CmdDyLdInfo::getSize() const {
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

Binary CodegenMac64CmdDyLdInfo::toBinary() const {
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

unsigned int CodegenMac64CmdDyLib::getSize() const {
  return this->dyLib.getSize();
}

Binary CodegenMac64CmdDyLib::toBinary() const {
  Binary binary;

  binary += this->dyLib.toBinary();

  return binary;
}

unsigned int CodegenMac64CmdDyLinker::getSize() const {
  return sizeof(this->name.offset) + this->name.getSize();
}

Binary CodegenMac64CmdDyLinker::toBinary() const {
  Binary binary;

  binary += this->name.offset;
  binary += this->name.toBinary();

  return binary;
}

unsigned int CodegenMac64CmdDySymTab::getSize() const {
  return sizeof(this->locSymIndex) +
    sizeof(this->locSymCount) +
    sizeof(this->defExtSymIndex) +
    sizeof(this->defExtSymCount) +
    sizeof(this->undefExtSymIndex) +
    sizeof(this->undefExtSymCount) +
    sizeof(this->tocTabOffset) +
    sizeof(this->tocTabCount) +
    sizeof(this->moduleTabOffset) +
    sizeof(this->moduleTabCount) +
    sizeof(this->extRefTabOffset) +
    sizeof(this->extRefTabEntries) +
    sizeof(this->indSymTabOffset) +
    sizeof(this->indSymTabEntries) +
    sizeof(this->extRelTabOffset) +
    sizeof(this->extRelTabEntries) +
    sizeof(this->locRelTabOffset) +
    sizeof(this->locRelTabEntries);
}

Binary CodegenMac64CmdDySymTab::toBinary() const {
  Binary binary;

  binary += this->locSymIndex;
  binary += this->locSymCount;
  binary += this->defExtSymIndex;
  binary += this->defExtSymCount;
  binary += this->undefExtSymIndex;
  binary += this->undefExtSymCount;
  binary += this->tocTabOffset;
  binary += this->tocTabCount;
  binary += this->moduleTabOffset;
  binary += this->moduleTabCount;
  binary += this->extRefTabOffset;
  binary += this->extRefTabEntries;
  binary += this->indSymTabOffset;
  binary += this->indSymTabEntries;
  binary += this->extRelTabOffset;
  binary += this->extRelTabEntries;
  binary += this->locRelTabOffset;
  binary += this->locRelTabEntries;

  return binary;
}

unsigned int CodegenMac64CmdEntryPoint::getSize() const {
  return sizeof(this->entryOffset) + sizeof(this->stackSize);
}

Binary CodegenMac64CmdEntryPoint::toBinary() const {
  Binary binary;

  binary += entryOffset;
  binary += stackSize;

  return binary;
}

unsigned int CodegenMac64CmdLinkEdit::getSize() const {
  return sizeof(this->dataOffset) + sizeof(this->dataSize);
}

Binary CodegenMac64CmdLinkEdit::toBinary() const {
  Binary binary;

  binary += this->dataOffset;
  binary += this->dataSize;

  return binary;
}

const std::string CodegenMac64CmdSeg::DATA = "__DATA";
const std::string CodegenMac64CmdSeg::ICON = "__ICON";
const std::string CodegenMac64CmdSeg::IMPORT = "__IMPORT";
const std::string CodegenMac64CmdSeg::LINKEDIT = "__LINKEDIT";
const std::string CodegenMac64CmdSeg::OBJC = "__OBJC";
const std::string CodegenMac64CmdSeg::PAGEZERO = "__PAGEZERO";
const std::string CodegenMac64CmdSeg::TEXT = "__TEXT";
const std::string CodegenMac64CmdSeg::UNIXSTACK = "__UNIXSTACK";

unsigned int CodegenMac64CmdSeg::getSize() const {
  unsigned int size = 0;

  for (CodegenMac64Sec sec : this->secs) {
    size += sec.getSize();
  }

  return CodegenMac64CmdSeg::NAME_SIZE +
    sizeof(this->vmAddr) +
    sizeof(this->vmSize) +
    sizeof(this->fileOffset) +
    sizeof(this->fileSize) +
    sizeof(this->maxProt) +
    sizeof(this->initProt) +
    sizeof(unsigned int) +
    sizeof(this->flags) +
    size;
}

Binary CodegenMac64CmdSeg::toBinary() const {
  Binary binary;

  binary.appendString(this->segName, CodegenMac64CmdSeg::NAME_SIZE);

  binary += this->vmAddr;
  binary += this->vmSize;
  binary += this->fileOffset;
  binary += this->fileSize;
  binary += this->maxProt;
  binary += this->initProt;
  binary += this->secs.size();
  binary += this->flags;

  for (CodegenMac64Sec sec : this->secs) {
    binary += sec.toBinary();
  }

  return binary;
}

unsigned int CodegenMac64CmdSourceVersion::getSize() const {
  return sizeof(this->version);
}

Binary CodegenMac64CmdSourceVersion::toBinary() const {
  Binary binary;

  binary += this->version;

  return binary;
}

unsigned int CodegenMac64CmdSymTab::getSize() const {
  return sizeof(this->symTabOffset) +
    sizeof(this->symTabCount) +
    sizeof(this->strTabOffset) +
    sizeof(this->strTabSize);
}

Binary CodegenMac64CmdSymTab::toBinary() const {
  Binary binary;

  binary += this->symTabOffset;
  binary += this->symTabCount;
  binary += this->strTabOffset;
  binary += this->strTabSize;

  return binary;
}

unsigned int CodegenMac64CmdVersionMin::getSize() const {
  return sizeof(this->version) + sizeof(this->versionSDK);
}

Binary CodegenMac64CmdVersionMin::toBinary() const {
  Binary binary;

  binary += this->version;
  binary += this->versionSDK;

  return binary;
}

unsigned int CodegenMac64DyLib::getSize() const {
  return sizeof(this->name.offset) +
    sizeof(this->timestamp) +
    sizeof(this->currentVersion) +
    sizeof(this->compatibilityVersion) +
    this->name.getSize();
}

Binary CodegenMac64DyLib::toBinary() const {
  Binary binary;

  binary += this->name.offset;
  binary += this->timestamp;
  binary += this->currentVersion;
  binary += this->compatibilityVersion;
  binary += this->name.toBinary();

  return binary;
}

unsigned int CodegenMac64Header::getSize() const {
  return sizeof(this->magic) +
    sizeof(this->cpuType) +
    sizeof(this->cpuSubType) +
    sizeof(this->fileType) +
    sizeof(this->cmdsCount) +
    sizeof(this->cmdsSize) +
    sizeof(this->flags) +
    sizeof(this->reserved);
}

Binary CodegenMac64Header::toBinary() const {
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

const std::string CodegenMac64Sec::BSS = "__bss";
const std::string CodegenMac64Sec::COMMON = "__common";
const std::string CodegenMac64Sec::DATA = "__data";
const std::string CodegenMac64Sec::FVMLIB_INIT0 = "__fvmlib_init0";
const std::string CodegenMac64Sec::FVMLIB_INIT1 = "__fvmlib_init1";
const std::string CodegenMac64Sec::ICON_HEADER = "__header";
const std::string CodegenMac64Sec::ICON_TIFF = "__tiff";
const std::string CodegenMac64Sec::OBJC_MODULES = "__module_info";
const std::string CodegenMac64Sec::OBJC_REFS = "__selector_refs";
const std::string CodegenMac64Sec::OBJC_STRINGS = "__selector_strs";
const std::string CodegenMac64Sec::OBJC_SYMBOLS = "__sym_table";
const std::string CodegenMac64Sec::TEXT = "__text";

unsigned int CodegenMac64Sec::getSize() const {
  return CodegenMac64Sec::NAME_SIZE +
    CodegenMac64CmdSeg::NAME_SIZE +
    sizeof(this->address) +
    sizeof(this->size) +
    sizeof(this->offset) +
    sizeof(this->align) +
    sizeof(this->reallocOffset) +
    sizeof(this->reallocCount) +
    sizeof(this->flags) +
    sizeof(this->reserved1) +
    sizeof(this->reserved2) +
    sizeof(this->reserved3);
}

Binary CodegenMac64Sec::toBinary() const {
  Binary binary;

  binary.appendString(this->secName, CodegenMac64Sec::NAME_SIZE);
  binary.appendString(this->segName, CodegenMac64CmdSeg::NAME_SIZE);

  binary += this->address;
  binary += this->size;
  binary += this->offset;
  binary += this->align;
  binary += this->reallocOffset;
  binary += this->reallocCount;
  binary += this->flags;
  binary += this->reserved1;
  binary += this->reserved2;
  binary += this->reserved3;

  return binary;
}

unsigned int CodegenMac64String::getSize() const {
  return this->stringSize;
}

Binary CodegenMac64String::toBinary() const {
  Binary binary;

  binary.appendString(this->string, this->getSize());

  return binary;
}
