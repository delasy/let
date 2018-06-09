#include "Error.hpp"
#include "Lexer.hpp"

#define LEX(name) \
  reader.store(READER_STORE_LEXER); \
  if (this->_is##name(reader)) { \
    reader.save(READER_STORE_LEXER); \
    return; \
  } \
  reader.restore(READER_STORE_LEXER)

bool Lexer::isCharIdentifier(unsigned char ch) {
  std::string possibleChars;

  possibleChars += "_$ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  possibleChars += "abcdefghijklmnopqrstuvwxyz";
  possibleChars += "0123456789";

  return possibleChars.find(ch) != std::string::npos;
}

bool Lexer::isCharIdentifierStart(unsigned char ch) {
  std::string possibleChars;

  possibleChars += "_$ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  possibleChars += "abcdefghijklmnopqrstuvwxyz";

  return possibleChars.find(ch) != std::string::npos;
}

bool Lexer::isCharLiteralNumber(unsigned char ch) {
  std::string possibleChars = "0123456789";
  return possibleChars.find(ch) != std::string::npos;
}

bool Lexer::isCharLiteralNumberStart(unsigned char ch) {
  std::string possibleChars = "123456789";
  return possibleChars.find(ch) != std::string::npos;
}

bool Lexer::isCharWhitespace(unsigned char ch) {
  return ch == ' ' ||
    ch == '\r' ||
    ch == '\n' ||
    ch == '\f' ||
    ch == '\t' ||
    ch == '\v' ||
    ch == '\b';
}

Lexer::Lexer(Reader &reader) {
  LEX(Whitespace);
  LEX(Bracket);
  LEX(CommentBlock);
  LEX(CommentLine);
  LEX(KeywordReturn);
  LEX(LiteralBoolean);
  LEX(LiteralNil);
  LEX(LiteralNumber);
  LEX(LiteralString);
  LEX(Mark);
  LEX(Sign);
  LEX(Identifier);

  std::string message;

  message += "Unexpected token '";
  message += reader.getChar();
  message += "'";

  throw Error(message);
}

bool Lexer::isLiteral() const {
  return this->token == LEXER_BOOLEAN_LITERAL ||
    this->token == LEXER_NIL_LITERAL ||
    this->token == LEXER_NUMBER_LITERAL ||
    this->token == LEXER_STRING_LITERAL_DQ ||
    this->token == LEXER_STRING_LITERAL_SQ;
}

bool Lexer::isSkippable() const {
  return this->token == LEXER_WS ||
    this->token == LEXER_BLOCK_COMMENT ||
    this->token == LEXER_LINE_COMMENT;
}

bool Lexer::_isBracket(Reader &reader) {
  unsigned char ch = reader.next();

  switch (ch) {
    case '{': {
      this->token = LEXER_LBRACE;
      break;
    }
    case '}': {
      this->token = LEXER_RBRACE;
      break;
    }
    case '(': {
      this->token = LEXER_LPAR;
      break;
    }
    case ')': {
      this->token = LEXER_RPAR;
      break;
    }
    case '[': {
      this->token = LEXER_LBRACK;
      break;
    }
    case ']': {
      this->token = LEXER_RBRACK;
      break;
    }
    default: {
      return false;
    }
  }

  this->value = this->rawValue = ch;
  return true;
}

bool Lexer::_isCommentBlock(Reader &reader) {
  unsigned char ch1 = reader.next();

  if (ch1 != '/') {
    return false;
  }

  unsigned char ch2 = reader.next();

  if (ch2 != '*') {
    return false;
  } else if (reader.isEOF()) {
    throw Error("Unexpected end of file, expected end of block comment");
  }

  this->rawValue += ch1;
  this->rawValue += ch2;

  unsigned char ch3 = reader.next();

  if (reader.isEOF()) {
    throw Error("Unexpected end of file, expected end of block comment");
  }

  this->rawValue += ch3;

  while (true) {
    unsigned char ch4 = reader.next();
    this->rawValue += ch4;

    if (ch3 == '*' && ch4 == '/') {
      break;
    } else if (reader.isEOF()) {
      throw Error("Unexpected end of file, expected end of block comment");
    }

    ch3 = ch4;
  }

  this->token = LEXER_BLOCK_COMMENT;
  this->value = this->rawValue.substr(2, this->rawValue.length() - 4);

  return true;
}

bool Lexer::_isCommentLine(Reader &reader) {
  unsigned char ch1 = reader.next();

  if (ch1 != '/') {
    return false;
  }

  unsigned char ch2 = reader.next();

  if (ch2 != '/') {
    return false;
  }

  this->rawValue += ch1;
  this->rawValue += ch2;

  while (!reader.isEOF()) {
    unsigned char ch3 = reader.next();

    if (ch3 == '\n') {
      reader.prev();
      break;
    }

    this->rawValue += ch3;
  }

  this->token = LEXER_LINE_COMMENT;
  this->value = this->rawValue.substr(2, this->rawValue.length() - 2);

  return true;
}

bool Lexer::_isIdentifier(Reader &reader) {
  unsigned char ch = reader.next();

  if (!Lexer::isCharIdentifierStart(ch)) {
    return false;
  }

  this->rawValue += ch;

  while (!reader.isEOF()) {
    ch = reader.next();

    if (!Lexer::isCharIdentifier(ch)) {
      reader.prev();
      break;
    }

    this->rawValue += ch;
  }

  this->token = LEXER_ID;
  this->value = this->rawValue;

  return true;
}

bool Lexer::_isKeywordReturn(Reader &reader) {
  unsigned char ch1 = reader.next();

  if (ch1 == 'r') {
    unsigned char ch2 = reader.next();

    if (ch2 == 'e') {
      unsigned char ch3 = reader.next();

      if (ch3 == 't') {
        unsigned char ch4 = reader.next();

        if (ch4 == 'u') {
          unsigned char ch5 = reader.next();

          if (ch5 == 'r') {
            unsigned char ch6 = reader.next();

            if (ch6 == 'n') {
              unsigned char ch7 = reader.next();
              reader.prev();

              if (!Lexer::isCharIdentifier(ch7)) {
                this->rawValue += ch1;
                this->rawValue += ch2;
                this->rawValue += ch3;
                this->rawValue += ch4;
                this->rawValue += ch5;
                this->rawValue += ch6;

                this->token = LEXER_RETURN;
                this->value = this->rawValue;

                return true;
              }
            }
          }
        }
      }
    }
  }

  return false;
}

bool Lexer::_isLiteralBoolean(Reader &reader) {
  unsigned char ch1 = reader.next();

  if (ch1 == 't') {
    unsigned char ch2 = reader.next();

    if (ch2 == 'r') {
      unsigned char ch3 = reader.next();

      if (ch3 == 'u') {
        unsigned char ch4 = reader.next();

        if (ch4 == 'e') {
          unsigned char ch5 = reader.next();
          reader.prev();

          if (!Lexer::isCharIdentifier(ch5)) {
            this->rawValue += ch1;
            this->rawValue += ch2;
            this->rawValue += ch3;
            this->rawValue += ch4;

            this->token = LEXER_BOOLEAN_LITERAL;
            this->value = this->rawValue;

            return true;
          }
        }
      }
    }
  } else if (ch1 == 'f') {
    unsigned char ch2 = reader.next();

    if (ch2 == 'a') {
      unsigned char ch3 = reader.next();

      if (ch3 == 'l') {
        unsigned char ch4 = reader.next();

        if (ch4 == 's') {
          unsigned char ch5 = reader.next();

          if (ch5 == 'e') {
            unsigned char ch6 = reader.next();
            reader.prev();

            if (!Lexer::isCharIdentifier(ch6)) {
              this->rawValue += ch1;
              this->rawValue += ch2;
              this->rawValue += ch3;
              this->rawValue += ch4;
              this->rawValue += ch5;

              this->token = LEXER_BOOLEAN_LITERAL;
              this->value = this->rawValue;

              return true;
            }
          }
        }
      }
    }
  }

  return false;
}

bool Lexer::_isLiteralNil(Reader &reader) {
  unsigned char ch1 = reader.next();

  if (ch1 == 'n') {
    unsigned char ch2 = reader.next();

    if (ch2 == 'i') {
      unsigned char ch3 = reader.next();

      if (ch3 == 'l') {
        unsigned char ch4 = reader.next();
        reader.prev();

        if (!Lexer::isCharIdentifier(ch4)) {
          this->rawValue += ch1;
          this->rawValue += ch2;
          this->rawValue += ch3;

          this->token = LEXER_NIL_LITERAL;
          this->value = this->rawValue;

          return true;
        }
      }
    }
  }

  return false;
}

bool Lexer::_isLiteralNumber(Reader &reader) {
  unsigned char ch = reader.next();

  if (ch == '0') {
    if (!reader.isEOF()) {
      ch = reader.next();

      if (Lexer::isCharLiteralNumber(ch)) {
        return false;
      }

      reader.prev();
    }

    this->token = LEXER_NUMBER_LITERAL;
    this->value = this->rawValue = '0';

    return true;
  } else if (!Lexer::isCharLiteralNumberStart(ch)) {
    return false;
  }

  this->rawValue += ch;

  while (!reader.isEOF()) {
    ch = reader.next();

    if (!Lexer::isCharLiteralNumber(ch)) {
      reader.prev();
      break;
    }

    this->rawValue += ch;
  }

  this->token = LEXER_NUMBER_LITERAL;
  this->value = this->rawValue;

  return true;
}

bool Lexer::_isLiteralString(Reader &reader) {
  unsigned char ch = reader.next();

  if (ch != '\'' && ch != '"') {
    return false;
  }

  if (ch == '"') {
    this->token = LEXER_STRING_LITERAL_DQ;
  } else {
    this->token = LEXER_STRING_LITERAL_SQ;
  }

  this->rawValue += ch;

  if (reader.isEOF()) {
    throw Error("Unexpected end of file, expected end of string");
  }

  while (true) {
    ch = reader.next();

    bool isEndOfDQ = this->token == LEXER_STRING_LITERAL_DQ && ch == '"';
    bool isEndOfSQ = this->token == LEXER_STRING_LITERAL_SQ && ch == '\'';

    this->rawValue += ch;

    if (isEndOfDQ || isEndOfSQ) {
      break;
    } else if (reader.isEOF()) {
      throw Error("Unexpected end of file, expected end of string");
    }
  }

  this->value = this->rawValue.substr(1, this->rawValue.length() - 2);
  return true;
}

bool Lexer::_isMark(Reader &reader) {
  unsigned char ch = reader.next();

  switch (ch) {
    case ',': {
      this->token = LEXER_COMMA;
      break;
    }
    case '!': {
      this->token = LEXER_EXCL;
      break;
    }
    default: {
      return false;
    }
  }

  this->value = this->rawValue = ch;
  return true;
}

bool Lexer::_isSign(Reader &reader) {
  unsigned char ch = reader.next();

  switch (ch) {
    case '=': {
      this->token = LEXER_EQUAL;
      break;
    }
    case '-': {
      this->token = LEXER_MINUS;
      break;
    }
    case '+': {
      this->token = LEXER_PLUS;
      break;
    }
    case '~': {
      this->token = LEXER_TILDE;
      break;
    }
    default: {
      return false;
    }
  }

  this->value = this->rawValue = ch;
  return true;
}

bool Lexer::_isWhitespace(Reader &reader) {
  unsigned char ch = reader.next();

  if (!Lexer::isCharWhitespace(ch)) {
    return false;
  }

  this->rawValue += ch;

  while (!reader.isEOF()) {
    ch = reader.next();

    if (!Lexer::isCharWhitespace(ch)) {
      reader.prev();
      break;
    }

    this->rawValue += ch;
  }

  this->token = LEXER_WS;
  this->value = this->rawValue;

  return true;
}
