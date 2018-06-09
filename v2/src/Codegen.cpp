#include "Codegen.hpp"
#include "CodegenMac64.hpp"

Binary Codegen::init(CodegenToken token, const AST &ast) {
  Binary binary;

  switch (token) {
    case CODEGEN_MAC64: {
      binary = CodegenMac64(ast).binary;
    }
    default: {
    }
  }

  return binary;
}
