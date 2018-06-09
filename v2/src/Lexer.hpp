#ifndef SRC_LEXER_HPP
#define SRC_LEXER_HPP

#include "Reader.hpp"

enum LexerToken {
  LEXER_UNKNOWN,
  LEXER_WS,

  LEXER_LBRACE,
  LEXER_RBRACE,
  LEXER_LPAR,
  LEXER_RPAR,
  LEXER_LBRACK,
  LEXER_RBRACK,

  LEXER_BLOCK_COMMENT,
  LEXER_LINE_COMMENT,

  LEXER_ID,

  LEXER_RETURN,

  LEXER_BOOLEAN_LITERAL,
  LEXER_NIL_LITERAL,
  LEXER_NUMBER_LITERAL,
  LEXER_STRING_LITERAL_DQ,
  LEXER_STRING_LITERAL_SQ,

  LEXER_COMMA,
  LEXER_EXCL,

  LEXER_EQUAL,
  LEXER_MINUS,
  LEXER_PLUS,
  LEXER_TILDE
};

class Lexer {
 public:
  std::string rawValue;
  LexerToken token = LEXER_UNKNOWN;
  std::string value;

  explicit Lexer() = default;
  explicit Lexer(Reader &);

  static bool isCharIdentifier(unsigned char);
  static bool isCharIdentifierStart(unsigned char);
  static bool isCharLiteralNumber(unsigned char);
  static bool isCharLiteralNumberStart(unsigned char);
  static bool isCharWhitespace(unsigned char);

  bool isLiteral() const;
  bool isSkippable() const;

 private:
  bool _isBracket(Reader &);
  bool _isCommentBlock(Reader &);
  bool _isCommentLine(Reader &);
  bool _isIdentifier(Reader &);
  bool _isKeywordReturn(Reader &);
  bool _isLiteralBoolean(Reader &);
  bool _isLiteralNil(Reader &);
  bool _isLiteralNumber(Reader &);
  bool _isLiteralString(Reader &);
  bool _isMark(Reader &);
  bool _isSign(Reader &);
  bool _isWhitespace(Reader &);
};

#endif
