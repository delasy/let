#include "AST.hpp"

AST::AST(Reader &reader) {
  while (!reader.cursor1.isEOF) {
    Parser parser(reader);

    if (parser.token == PARSER_SKIPPABLE) {
      continue;
    }

    this->parsers.push_back(parser);
  }
}
