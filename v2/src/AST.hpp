#ifndef SRC_AST_HPP
#define SRC_AST_HPP

#include "Parser.hpp"

class AST {
 public:
  std::vector<Parser> parsers;

  explicit AST(Reader &);
};

#endif
