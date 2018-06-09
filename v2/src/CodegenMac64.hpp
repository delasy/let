#ifndef SRC_CODEGENMAC64_HPP
#define SRC_CODEGENMAC64_HPP

#include "AST.hpp"
#include "Binary.hpp"

class CodegenMac64String {
 public:
  unsigned int offset = 0;
  std::string string;
  unsigned int stringSize = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64DyLib {
 public:
  unsigned int compatibilityVersion = 0;
  unsigned int currentVersion = 0;
  CodegenMac64String name;
  unsigned int timestamp = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdDyLdInfo {
 public:
  unsigned int bindOffset = 0;
  unsigned int bindSize = 0;
  unsigned int exportOffset = 0;
  unsigned int exportSize = 0;
  unsigned int lazyBindOffset = 0;
  unsigned int lazyBindSize = 0;
  unsigned int rebaseOffset = 0;
  unsigned int rebaseSize = 0;
  unsigned int weakBindOffset = 0;
  unsigned int weakBindSize = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdDyLib {
 public:
  CodegenMac64DyLib dyLib;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdDyLinker {
 public:
  CodegenMac64String name;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdDySymTab {
 public:
  unsigned int defExtSymIndex = 0;
  unsigned int defExtSymCount = 0;
  unsigned int extRefTabOffset = 0;
  unsigned int extRefTabEntries = 0;
  unsigned int extRelTabOffset = 0;
  unsigned int extRelTabEntries = 0;
  unsigned int indSymTabOffset = 0;
  unsigned int indSymTabEntries = 0;
  unsigned int locSymIndex = 0;
  unsigned int locSymCount = 0;
  unsigned int locRelTabOffset = 0;
  unsigned int locRelTabEntries = 0;
  unsigned int moduleTabOffset = 0;
  unsigned int moduleTabCount = 0;
  unsigned int tocTabOffset = 0;
  unsigned int tocTabCount = 0;
  unsigned int undefExtSymIndex = 0;
  unsigned int undefExtSymCount = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdEntryPoint {
 public:
  unsigned long long entryOffset = 0;
  unsigned long long stackSize = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdLinkEdit {
 public:
  unsigned int dataOffset = 0;
  unsigned int dataSize = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64Sec {
 public:
  static const std::string BSS;
  static const std::string COMMON;
  static const std::string DATA;
  static const std::string FVMLIB_INIT0;
  static const std::string FVMLIB_INIT1;
  static const std::string ICON_HEADER;
  static const std::string ICON_TIFF;
  static const std::string OBJC_MODULES;
  static const std::string OBJC_REFS;
  static const std::string OBJC_STRINGS;
  static const std::string OBJC_SYMBOLS;
  static const std::string TEXT;

  static const unsigned int FLAG_REGULAR = 0x0;
  static const unsigned int FLAG_ZEROFILL = 0x1;
  static const unsigned int FLAG_CSTRING_LITERALS = 0x2;
  static const unsigned int FLAG_4BYTE_LITERALS = 0x3;
  static const unsigned int FLAG_8BYTE_LITERALS = 0x4;
  static const unsigned int FLAG_LITERAL_POINTERS = 0x5;
  static const unsigned int FLAG_NON_LAZY_SYMBOL_POINTERS = 0x6;
  static const unsigned int FLAG_LAZY_SYMBOL_POINTERS = 0x7;
  static const unsigned int FLAG_SYMBOL_STUBS = 0x8;
  static const unsigned int FLAG_MOD_INIT_FUNC_POINTERS = 0x9;
  static const unsigned int FLAG_MOD_TERM_FUNC_POINTERS = 0xA;
  static const unsigned int FLAG_COALESCED = 0xB;
  static const unsigned int FLAG_GB_ZEROFILL = 0xC;
  static const unsigned int FLAG_INTERPOSING = 0xD;
  static const unsigned int FLAG_16BYTE_LITERALS = 0xE;
  static const unsigned int FLAG_DTRACE_DOF = 0xF;
  static const unsigned int FLAG_LAZY_DYLIB_SYMBOL_POINTERS = 0x10;
  static const unsigned int FLAG_THREAD_LOCAL_REGULAR = 0x11;
  static const unsigned int FLAG_THREAD_LOCAL_ZEROFILL = 0x12;
  static const unsigned int FLAG_THREAD_LOCAL_VARIABLES = 0x13;
  static const unsigned int FLAG_THREAD_LOCAL_VARIABLE_POINTERS = 0x14;
  static const unsigned int FLAG_THREAD_LOCAL_INIT_FUNCTION_POINTERS = 0x15;
  static const unsigned int FLAG_INIT_FUNC_OFFSETS = 0x16;

  static const unsigned int FLAG_ATTR_LOC_RELOC = 0x100;
  static const unsigned int FLAG_ATTR_EXT_RELOC = 0x200;
  static const unsigned int FLAG_ATTR_SOME_INSTRUCTIONS = 0x400;
  static const unsigned int FLAG_ATTR_SYS = 0xFFFF00;
  static const unsigned int FLAG_ATTR_DEBUG = 0x2000000;
  static const unsigned int FLAG_ATTR_SELF_MODIFYING_CODE = 0x4000000;
  static const unsigned int FLAG_ATTR_LIVE_SUPPORT = 0x8000000;
  static const unsigned int FLAG_ATTR_NO_DEAD_STRIP = 0x10000000;
  static const unsigned int FLAG_ATTR_STRIP_STATIC_SYMS = 0x20000000;
  static const unsigned int FLAG_ATTR_NO_TOC = 0x40000000;
  static const unsigned int FLAG_ATTR_PURE_INSTRUCTIONS = 0x80000000;
  static const unsigned int FLAG_ATTR_USR = 0xFF000000;

  static const unsigned int NAME_SIZE = 0x10;

  unsigned long long address = 0;
  unsigned int align = 0;
  unsigned int flags = CodegenMac64Sec::FLAG_REGULAR;
  unsigned int offset = 0;
  unsigned int reallocCount = 0;
  unsigned int reallocOffset = 0;
  unsigned int reserved1 = 0;
  unsigned int reserved2 = 0;
  unsigned int reserved3 = 0;
  std::string secName;
  std::string segName;
  unsigned long long size = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdSeg {
 public:
  static const std::string DATA;
  static const std::string ICON;
  static const std::string IMPORT;
  static const std::string LINKEDIT;
  static const std::string OBJC;
  static const std::string PAGEZERO;
  static const std::string TEXT;
  static const std::string UNIXSTACK;

  static const unsigned int FLAG_UNKNOWN = 0x0;
  static const unsigned int FLAG_HIGHVM = 0x1;
  static const unsigned int FLAG_FVMLIB = 0x2;
  static const unsigned int FLAG_NORELOC = 0x4;
  static const unsigned int FLAG_PROTECTED_VERSION_1 = 0x8;
  static const unsigned int FLAG_READ_ONLY = 0x10;

  static const unsigned int NAME_SIZE = 0x10;

  static const int PROT_NONE = 0x0;
  static const int PROT_READ = 0x1;
  static const int PROT_WRITE = 0x2;
  static const int PROT_EXECUTE = 0x4;
  static const int PROT_DEFAULT = CodegenMac64CmdSeg::PROT_READ |
    CodegenMac64CmdSeg::PROT_WRITE;
  static const int PROT_ALL = CodegenMac64CmdSeg::PROT_READ |
    CodegenMac64CmdSeg::PROT_WRITE |
    CodegenMac64CmdSeg::PROT_EXECUTE;
  static const int PROT_NO_CHANGE = 0x8;
  static const int PROT_COPY = 0x9;
  static const int PROT_WANTS_COPY = 0x10;
  static const int PROT_IS_MASK = 0x40;
  static const int PROT_STRIP_READ = 0x80;
  static const int PROT_EXECUTE_ONLY = CodegenMac64CmdSeg::PROT_EXECUTE |
    CodegenMac64CmdSeg::PROT_STRIP_READ;

  unsigned long long fileOffset = 0;
  unsigned long long fileSize = 0;
  unsigned int flags = CodegenMac64CmdSeg::FLAG_UNKNOWN;
  int initProt = CodegenMac64CmdSeg::PROT_NONE;
  int maxProt = CodegenMac64CmdSeg::PROT_NONE;
  std::string segName;
  std::vector<CodegenMac64Sec> secs;
  unsigned long long vmAddr = 0;
  unsigned long long vmSize = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdSourceVersion {
 public:
  unsigned long long version = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdSymTab {
 public:
  unsigned int strTabOffset = 0;
  unsigned int strTabSize = 0;
  unsigned int symTabOffset = 0;
  unsigned int symTabCount = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64CmdVersionMin {
 public:
  unsigned int version = 0;
  unsigned int versionSDK = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64Cmd {
 public:
  static const unsigned int REQ_DYLD = 0x80000000;
  static const unsigned int UNKNOWN = 0x0;
  static const unsigned int SEG = 0x1;
  static const unsigned int SYMTAB = 0x2;
  static const unsigned int SYMSEG = 0x3;
  static const unsigned int THREAD = 0x4;
  static const unsigned int UNIXTHREAD = 0x5;
  static const unsigned int LOADFVMLIB = 0x6;
  static const unsigned int IDFVMLIB = 0x7;
  static const unsigned int IDENT = 0x8;
  static const unsigned int FVMFILE = 0x9;
  static const unsigned int PREPAGE = 0xA;
  static const unsigned int DYSYMTAB = 0xB;
  static const unsigned int LOAD_DYLIB = 0xC;
  static const unsigned int ID_DYLIB = 0xD;
  static const unsigned int LOAD_DYLINKER = 0xE;
  static const unsigned int ID_DYLINKER = 0xF;
  static const unsigned int PREBOUND_DYLIB = 0x10;
  static const unsigned int ROUTINES = 0x11;
  static const unsigned int SUB_FRAMEWORK = 0x12;
  static const unsigned int SUB_UMBRELLA = 0x13;
  static const unsigned int SUB_CLIENT = 0x14;
  static const unsigned int SUB_LIBRARY = 0x15;
  static const unsigned int TWOLEVEL_HINTS = 0x16;
  static const unsigned int PREBIND_CKSUM = 0x17;
  static const unsigned int LOAD_WEAK_DYLIB = 0x18 | CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int SEG_64 = 0x19;
  static const unsigned int ROUTINES_64 = 0x1A;
  static const unsigned int UUID = 0x1B;
  static const unsigned int RPATH = 0x1C | CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int CODE_SIGNATURE = 0x1D;
  static const unsigned int SEG_SPLIT_INFO = 0x1E;
  static const unsigned int REEXPORT_DYLIB = 0x1F | CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int LAZY_LOAD_DYLIB = 0x20;
  static const unsigned int ENCRYPTION_INFO = 0x21;
  static const unsigned int DYLD_INFO = 0x22;
  static const unsigned int DYLD_INFO_ONLY = 0x22 | CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int LOAD_UPWARD_DYLIB = 0x23 |
    CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int VERSION_MIN_MACOSX = 0x24;
  static const unsigned int VERSION_MIN_IPHONEOS = 0x25;
  static const unsigned int FUNCTION_STARTS = 0x26;
  static const unsigned int DYLD_ENVIRONMENT = 0x27;
  static const unsigned int MAIN = 0x28 | CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int DATA_IN_CODE = 0x29;
  static const unsigned int SOURCE_VERSION = 0x2A;
  static const unsigned int DYLIB_CODE_SIGN_DRS = 0x2B;
  static const unsigned int ENCRYPTION_INFO_64 = 0x2C;
  static const unsigned int LINKER_OPTION = 0x2D;
  static const unsigned int LINKER_OPTIMIZATION_HINT = 0x2E;
  static const unsigned int VERSION_MIN_TVOS = 0x2F;
  static const unsigned int VERSION_MIN_WATCHOS = 0x30;
  static const unsigned int NOTE = 0x31;
  static const unsigned int BUILD_VERSION = 0x32;
  static const unsigned int DYLD_EXPORTS_PAYLOAD = 0x33 |
    CodegenMac64Cmd::REQ_DYLD;
  static const unsigned int DYLD_CHAINED_FIXUPS = 0x34 |
    CodegenMac64Cmd::REQ_DYLD;

  unsigned int cmd = CodegenMac64Cmd::UNKNOWN;
  CodegenMac64CmdDyLdInfo dyLdInfo;
  CodegenMac64CmdDyLib dyLib;
  CodegenMac64CmdDyLinker dyLinker;
  CodegenMac64CmdDySymTab dySymTab;
  CodegenMac64CmdEntryPoint entryPoint;
  CodegenMac64CmdLinkEdit linkEdit;
  CodegenMac64CmdSeg seg;
  CodegenMac64CmdSourceVersion sourceVersion;
  CodegenMac64CmdSymTab symTab;
  CodegenMac64CmdVersionMin versionMin;

  explicit CodegenMac64Cmd(unsigned int);

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64Header {
 public:
  static const unsigned int UNKNOWN = 0x0;
  static const unsigned int CIGAM = 0xCFFAEDFE;
  static const unsigned int MAGIC = 0xFEEDFACF;

  static const int CPU_ARCH_MASK = 0xFF000000;
  static const int CPU_ARCH_ABI64 = 0x1000000;
  static const int CPU_ARCH_ABI64_32 = 0x2000000;

  static const int CPU_TYPE_ANY = -1;
  static const int CPU_TYPE_UNKNOWN = 0;
  static const int CPU_TYPE_VAX = 1;
  static const int CPU_TYPE_MC680X0 = 6;
  static const int CPU_TYPE_X86 = 7;
  static const int CPU_TYPE_I386 = CodegenMac64Header::CPU_TYPE_X86;
  static const int CPU_TYPE_X86_64 = CodegenMac64Header::CPU_TYPE_X86 |
    CodegenMac64Header::CPU_ARCH_ABI64;
  static const int CPU_TYPE_MC98000 = 10;
  static const int CPU_TYPE_HPPA = 11;
  static const int CPU_TYPE_ARM = 12;
  static const int CPU_TYPE_ARM64 = CodegenMac64Header::CPU_TYPE_ARM |
    CodegenMac64Header::CPU_ARCH_ABI64;
  static const int CPU_TYPE_ARM64_32 = CodegenMac64Header::CPU_TYPE_ARM |
    CodegenMac64Header::CPU_ARCH_ABI64_32;
  static const int CPU_TYPE_MC88000 = 13;
  static const int CPU_TYPE_SPARC = 14;
  static const int CPU_TYPE_I860 = 15;
  static const int CPU_TYPE_POWERPC = 18;
  static const int CPU_TYPE_POWERPC64 = CodegenMac64Header::CPU_TYPE_POWERPC |
    CodegenMac64Header::CPU_ARCH_ABI64;

  static const int CPU_SUBTYPE_MASK = 0xFF000000;
  static const int CPU_SUBTYPE_LIB64 = 0x80000000;
  static const int CPU_SUBTYPE_MULTIPLE = -1;
  static const int CPU_SUBTYPE_LITTLE_ENDIAN = 0;
  static const int CPU_SUBTYPE_BIG_ENDIAN = 1;
  static const int CPU_SUBTYPE_VAX_ALL = 0;
  static const int CPU_SUBTYPE_VAX780 = 1;
  static const int CPU_SUBTYPE_VAX785 = 2;
  static const int CPU_SUBTYPE_VAX750 = 3;
  static const int CPU_SUBTYPE_VAX730 = 4;
  static const int CPU_SUBTYPE_UVAXI = 5;
  static const int CPU_SUBTYPE_UVAXII = 6;
  static const int CPU_SUBTYPE_VAX8200 = 7;
  static const int CPU_SUBTYPE_VAX8500 = 8;
  static const int CPU_SUBTYPE_VAX8600 = 9;
  static const int CPU_SUBTYPE_VAX8650 = 10;
  static const int CPU_SUBTYPE_VAX8800 = 11;
  static const int CPU_SUBTYPE_UVAXIII = 12;
  static const int CPU_SUBTYPE_MC680X0_ALL = 1;
  static const int CPU_SUBTYPE_MC68030 = 1;
  static const int CPU_SUBTYPE_MC68040 = 2;
  static const int CPU_SUBTYPE_MC68030_ONLY = 3;
  static const int CPU_SUBTYPE_I386_ALL = 3;
  static const int CPU_SUBTYPE_386 = 3;
  static const int CPU_SUBTYPE_486 = 4;
  static const int CPU_SUBTYPE_486SX = 132;
  static const int CPU_SUBTYPE_586 = 5;
  static const int CPU_SUBTYPE_PENT = 5;
  static const int CPU_SUBTYPE_PENTPRO = 22;
  static const int CPU_SUBTYPE_PENTII_M3 = 54;
  static const int CPU_SUBTYPE_PENTII_M5 = 86;
  static const int CPU_SUBTYPE_CELERON = 103;
  static const int CPU_SUBTYPE_CELERON_MOBILE = 119;
  static const int CPU_SUBTYPE_PENTIUM_3 = 8;
  static const int CPU_SUBTYPE_PENTIUM_3_M = 24;
  static const int CPU_SUBTYPE_PENTIUM_3_XEON = 40;
  static const int CPU_SUBTYPE_PENTIUM_M = 9;
  static const int CPU_SUBTYPE_PENTIUM_4 = 10;
  static const int CPU_SUBTYPE_PENTIUM_4_M = 26;
  static const int CPU_SUBTYPE_ITANIUM = 11;
  static const int CPU_SUBTYPE_ITANIUM_2 = 27;
  static const int CPU_SUBTYPE_XEON = 12;
  static const int CPU_SUBTYPE_XEON_MP = 28;
  static const int CPU_SUBTYPE_X86_ALL = 3;
  static const int CPU_SUBTYPE_X86_64_ALL = 3;
  static const int CPU_SUBTYPE_X86_ARCH1 = 4;
  static const int CPU_SUBTYPE_X86_64_H = 8;
  static const int CPU_SUBTYPE_MIPS_ALL = 0;
  static const int CPU_SUBTYPE_MIPS_R2300 = 1;
  static const int CPU_SUBTYPE_MIPS_R2600 = 2;
  static const int CPU_SUBTYPE_MIPS_R2800 = 3;
  static const int CPU_SUBTYPE_MIPS_R2000_A = 4;
  static const int CPU_SUBTYPE_MIPS_R2000 = 5;
  static const int CPU_SUBTYPE_MIPS_R3000_A = 6;
  static const int CPU_SUBTYPE_MIPS_R3000 = 7;
  static const int CPU_SUBTYPE_MC98000_ALL = 0;
  static const int CPU_SUBTYPE_MC98601 = 1;
  static const int CPU_SUBTYPE_HPPA_ALL = 0;
  static const int CPU_SUBTYPE_HPPA_7100 = 0;
  static const int CPU_SUBTYPE_HPPA_7100LC = 1;
  static const int CPU_SUBTYPE_MC88000_ALL = 0;
  static const int CPU_SUBTYPE_MC88100 = 1;
  static const int CPU_SUBTYPE_MC88110 = 2;
  static const int CPU_SUBTYPE_SPARC_ALL = 0;
  static const int CPU_SUBTYPE_I860_ALL = 0;
  static const int CPU_SUBTYPE_I860_860 = 1;
  static const int CPU_SUBTYPE_POWERPC_ALL = 0;
  static const int CPU_SUBTYPE_POWERPC_601 = 1;
  static const int CPU_SUBTYPE_POWERPC_602 = 2;
  static const int CPU_SUBTYPE_POWERPC_603 = 3;
  static const int CPU_SUBTYPE_POWERPC_603_E = 4;
  static const int CPU_SUBTYPE_POWERPC_603_EV = 5;
  static const int CPU_SUBTYPE_POWERPC_604 = 6;
  static const int CPU_SUBTYPE_POWERPC_604_E = 7;
  static const int CPU_SUBTYPE_POWERPC_620 = 8;
  static const int CPU_SUBTYPE_POWERPC_750 = 9;
  static const int CPU_SUBTYPE_POWERPC_7400 = 10;
  static const int CPU_SUBTYPE_POWERPC_7450 = 11;
  static const int CPU_SUBTYPE_POWERPC_970 = 100;
  static const int CPU_SUBTYPE_ARM_ALL = 0;
  static const int CPU_SUBTYPE_ARM_V4T = 5;
  static const int CPU_SUBTYPE_ARM_V6 = 6;
  static const int CPU_SUBTYPE_ARM_V5TEJ = 7;
  static const int CPU_SUBTYPE_ARM_XSCALE = 8;
  static const int CPU_SUBTYPE_ARM_V7 = 9;
  static const int CPU_SUBTYPE_ARM_V7F = 10;
  static const int CPU_SUBTYPE_ARM_V7S = 11;
  static const int CPU_SUBTYPE_ARM_V7K = 12;
  static const int CPU_SUBTYPE_ARM_V6M = 14;
  static const int CPU_SUBTYPE_ARM_V7M = 15;
  static const int CPU_SUBTYPE_ARM_V7EM = 16;
  static const int CPU_SUBTYPE_ARM_V8 = 13;
  static const int CPU_SUBTYPE_ARM64_ALL = 0;
  static const int CPU_SUBTYPE_ARM64_V8 = 1;
  static const int CPU_SUBTYPE_ARM64E = 2;
  static const int CPU_SUBTYPE_ARM64_32_ALL = 0;
  static const int CPU_SUBTYPE_ARM64_32_V8 = 1;

  static const unsigned int FILE_TYPE_UNKNOWN = 0x0;
  static const unsigned int FILE_TYPE_OBJECT = 0x1;
  static const unsigned int FILE_TYPE_EXECUTE = 0x2;
  static const unsigned int FILE_TYPE_FVMLIB = 0x3;
  static const unsigned int FILE_TYPE_CORE = 0x4;
  static const unsigned int FILE_TYPE_PRELOAD = 0x5;
  static const unsigned int FILE_TYPE_DYLIB = 0x6;
  static const unsigned int FILE_TYPE_DYLINKER = 0x7;
  static const unsigned int FILE_TYPE_BUNDLE = 0x8;
  static const unsigned int FILE_TYPE_DYLIB_STUB = 0x9;
  static const unsigned int FILE_TYPE_DSYM = 0xA;
  static const unsigned int FILE_TYPE_KEXT_BUNDLE = 0xB;

  static const unsigned int FLAG_UNKNOWN = 0x0;
  static const unsigned int FLAG_NOUNDEFS = 0x1;
  static const unsigned int FLAG_INCRLINK = 0x2;
  static const unsigned int FLAG_DYLDLINK = 0x4;
  static const unsigned int FLAG_BINDATLOAD = 0x8;
  static const unsigned int FLAG_PREBOUND = 0x10;
  static const unsigned int FLAG_SPLIT_SEGS = 0x20;
  static const unsigned int FLAG_LAZY_INIT = 0x40;
  static const unsigned int FLAG_TWOLEVEL = 0x80;
  static const unsigned int FLAG_FORCE_FLAT = 0x100;
  static const unsigned int FLAG_NOMULTIDEFS = 0x200;
  static const unsigned int FLAG_NOFIXPREBINDING = 0x400;
  static const unsigned int FLAG_PREBINDABLE = 0x800;
  static const unsigned int FLAG_ALLMODSBOUND = 0x1000;
  static const unsigned int FLAG_SUBSECS_VIA_SYMBOLS = 0x2000;
  static const unsigned int FLAG_CANONICAL = 0x4000;
  static const unsigned int FLAG_WEAK_DEFINES = 0x8000;
  static const unsigned int FLAG_BINDS_TO_WEAK = 0x10000;
  static const unsigned int FLAG_ALLOW_STACK_EXECUTION = 0x20000;
  static const unsigned int FLAG_ROOT_SAFE = 0x40000;
  static const unsigned int FLAG_SETUID_SAFE = 0x80000;
  static const unsigned int FLAG_NO_REEXPORTED_DYLIBS = 0x100000;
  static const unsigned int FLAG_PIE = 0x200000;
  static const unsigned int FLAG_DEAD_STRIPPABLE_DYLIB = 0x400000;
  static const unsigned int FLAG_HAS_TLV_DESCRIPTORS = 0x800000;
  static const unsigned int FLAG_NO_HEAP_EXECUTION = 0x1000000;
  static const unsigned int FLAG_APP_EXTENSION_SAFE = 0x2000000;
  static const unsigned int FLAG_NLIST_OUTOFSYNC_WITH_DYLDINFO = 0x4000000;
  static const unsigned int FLAG_SIM_SUPPORT = 0x8000000;

  unsigned int cmdsCount = 0;
  unsigned int cmdsSize = 0;
  int cpuType = CodegenMac64Header::CPU_TYPE_UNKNOWN;
  int cpuSubType = CodegenMac64Header::CPU_SUBTYPE_MULTIPLE;
  unsigned int fileType = CodegenMac64Header::FILE_TYPE_UNKNOWN;
  unsigned int flags = CodegenMac64Header::FLAG_UNKNOWN;
  unsigned int magic = CodegenMac64Header::UNKNOWN;
  unsigned int reserved = 0;

  unsigned int getSize() const;
  Binary toBinary() const;
};

class CodegenMac64 {
 public:
  Binary binary;

  explicit CodegenMac64(const AST &);

  void addCmdDataInCode();
  void addCmdDyLdInfoOnly();
  void addCmdDySymTab();
  void addCmdLoadDyLib();
  void addCmdLoadDyLinker();
  void addCmdMain();
  void addCmdSegData();
  void addCmdSegLinkEdit();
  void addCmdSegPagezero();
  void addCmdSegText();
  void addCmdSymTab();
  void addCmdSourceVersion();
  void addCmdVersionMinMacOSX();
  void addHeader();
  void generateBinary();
  void processAST(const AST &);

 private:
  std::vector<CodegenMac64Cmd> _cmds;
  Binary _dyLdInfo;
  CodegenMac64Header _header;
  Binary _secData;
  unsigned long long _secDataAddress = 0;
  unsigned int _secDataOffset = 0;
  unsigned long long _secDataSize = 0;
  Binary _secText;
  unsigned long long _secTextAddress = 0;
  unsigned int _secTextOffset = 0;
  unsigned long long _secTextSize = 0;
  Binary _strTab;
  Binary _symTab;
};

#endif
