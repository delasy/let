#ifndef SRC_CODEGEN_HPP
#define SRC_CODEGEN_HPP

#include "AST.hpp"
#include "Binary.hpp"

enum CodegenToken {
  CODEGEN_UNKNOWN,
  CODEGEN_MAC64
};

class Codegen {
 public:
  static Binary init(CodegenToken, const AST &);
};

#endif
