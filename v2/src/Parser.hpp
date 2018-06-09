#ifndef SRC_PARSER_HPP
#define SRC_PARSER_HPP

#include <vector>
#include "Lexer.hpp"

class ParserBase {
 public:
  bool isInitialized() const;

 protected:
  void _initialize();

 private:
  bool _isInitialized = false;
};

class ParserId : public ParserBase {
 public:
  Lexer l;

  explicit ParserId() = default;
  explicit ParserId(Reader &);
};

class ParserLiteral : public ParserBase {
 public:
  Lexer l;

  explicit ParserLiteral() = default;
  explicit ParserLiteral(Reader &);
};

enum ParserExprToken {
  PARSER_EXPR_UNKNOWN,
  PARSER_EXPR_ID,
  PARSER_EXPR_LITERAL
};

class ParserExpr : public ParserBase {
 public:
  ParserId id;
  ParserLiteral literal;
  ParserExprToken token = PARSER_EXPR_UNKNOWN;

  explicit ParserExpr() = default;
  explicit ParserExpr(Reader &reader);
};

class ParserArgList : public ParserBase {
 public:
  std::vector<ParserExpr> exprs;

  explicit ParserArgList() = default;
  explicit ParserArgList(Reader &);
};

class ParserAssignExpr : public ParserBase {
 public:
  ParserExpr expr;
  ParserId id;

  explicit ParserAssignExpr() = default;
  explicit ParserAssignExpr(Reader &);
};

class ParserCallExpr : public ParserBase {
 public:
  ParserArgList argList;
  ParserId id;

  explicit ParserCallExpr() = default;
  explicit ParserCallExpr(Reader &);
};

class ParserSkippable : public ParserBase {
 public:
  std::vector<Lexer> lexers;

  explicit ParserSkippable() = default;
  explicit ParserSkippable(Reader &);
};

enum ParserToken {
  PARSER_UNKNOWN,
  PARSER_SKIPPABLE,
  PARSER_ASSIGN_EXPR,
  PARSER_CALL_EXPR
};

class Parser {
 public:
  ParserAssignExpr assignExpr;
  ParserCallExpr callExpr;
  ParserSkippable skippable;
  ParserToken token = PARSER_UNKNOWN;

  explicit Parser(Reader &);
};

#endif
