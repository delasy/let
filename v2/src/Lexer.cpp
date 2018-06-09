#include "Lexer.hpp"
#include "Exception.hpp"

Lexer::Lexer(Reader &reader) {
  if (
    this->_isWhitespace(reader) ||
    this->_isBracket(reader) ||
    this->_isCommentBlock(reader) ||
    this->_isCommentLine(reader) ||
    this->_isKeywordReturn(reader) ||
    this->_isLiteralBoolean(reader) ||
    this->_isLiteralNil(reader) ||
    this->_isLiteralNumber(reader) ||
    this->_isLiteralString(reader) ||
    this->_isMark(reader) ||
    this->_isSign(reader) ||
    this->_isIdentifier(reader)
  ) {
    return;
  }

  std::string message;

  message += "Unexpected token '";
  message += reader.cursor3.getChar();
  message += "'";

  throw Exception(message, reader);
}

bool Lexer::isCharIdentifier(unsigned char ch) {
  std::string possibleChars;

  possibleChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  possibleChars += "abcdefghijklmnopqrstuvwxyz";
  possibleChars += "0123456789_$";

  return possibleChars.find(ch) != std::string::npos;
}

bool Lexer::isCharIdentifierStart(unsigned char ch) {
  std::string possibleChars;

  possibleChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  possibleChars += "abcdefghijklmnopqrstuvwxyz";
  possibleChars += "_$";

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
  unsigned char ch = reader.nextToken();

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
      reader.restoreCursor(READER_CURSOR_SECONDARY);
      return false;
    }
  }

  this->rawValue = ch;
  this->value = this->rawValue;

  return true;
}

bool Lexer::_isCommentBlock(Reader &reader) {
  unsigned char ch1 = reader.nextToken();

  if (ch1 != '/') {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  unsigned char ch2 = reader.nextToken();

  if (ch2 != '*') {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  this->rawValue += ch1;
  this->rawValue += ch2;

  std::string errorMessage;

  errorMessage = "Unexpected end of file, expected end of block comment";

  if (reader.cursor3.isEOF) {
    throw Exception(errorMessage, reader);
  }

  unsigned char ch3 = reader.nextToken();

  this->rawValue += ch3;

  if (reader.cursor3.isEOF) {
    throw Exception(errorMessage, reader);
  }

  while (true) {
    unsigned char ch4 = reader.nextToken();

    this->rawValue += ch4;

    if (ch3 == '*' && ch4 == '/') {
      break;
    } else if (reader.cursor3.isEOF) {
      throw Exception(errorMessage, reader);
    }

    ch3 = ch4;
  }

  this->token = LEXER_BLOCK_COMMENT;
  this->value = this->rawValue.substr(2, this->rawValue.length() - 4);

  return true;
}

bool Lexer::_isCommentLine(Reader &reader) {
  unsigned char ch1 = reader.nextToken();

  if (ch1 != '/') {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  unsigned char ch2 = reader.nextToken();

  if (ch2 != '/') {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  this->rawValue += ch1;
  this->rawValue += ch2;

  while (!reader.cursor3.isEOF) {
    unsigned char ch3 = reader.nextToken();

    if (ch3 == '\n') {
      reader.prevToken();
      break;
    }

    this->rawValue += ch3;
  }

  this->token = LEXER_LINE_COMMENT;
  this->value = this->rawValue.substr(2, this->rawValue.length() - 2);

  return true;
}

bool Lexer::_isIdentifier(Reader &reader) {
  unsigned char ch = reader.nextToken();

  if (Lexer::isCharIdentifierStart(ch)) {
    this->token = LEXER_ID;
  } else {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  this->rawValue += ch;

  while (!reader.cursor3.isEOF) {
    ch = reader.nextToken();

    if (!Lexer::isCharIdentifier(ch)) {
      reader.prevToken();
      break;
    }

    this->rawValue += ch;
  }

  this->value = this->rawValue;
  return true;
}

bool Lexer::_isKeywordReturn(Reader &reader) {
  unsigned char ch1 = reader.nextToken();

  if (ch1 == 'r') {
    unsigned char ch2 = reader.nextToken();

    if (ch2 == 'e') {
      unsigned char ch3 = reader.nextToken();

      if (ch3 == 't') {
        unsigned char ch4 = reader.nextToken();

        if (ch4 == 'u') {
          unsigned char ch5 = reader.nextToken();

          if (ch5 == 'r') {
            unsigned char ch6 = reader.nextToken();

            if (ch6 == 'n') {
              unsigned char ch7 = reader.nextToken();

              reader.prevToken();

              if (!Lexer::isCharIdentifier(ch7)) {
                this->token = LEXER_RETURN;
                this->rawValue += ch1;
                this->rawValue += ch2;
                this->rawValue += ch3;
                this->rawValue += ch4;
                this->rawValue += ch5;
                this->rawValue += ch6;
                this->value = this->rawValue;

                return true;
              }
            }
          }
        }
      }
    }
  }

  reader.restoreCursor(READER_CURSOR_SECONDARY);
  return false;
}

bool Lexer::_isLiteralBoolean(Reader &reader) {
  unsigned char ch1 = reader.nextToken();

  if (ch1 == 't') {
    unsigned char ch2 = reader.nextToken();

    if (ch2 == 'r') {
      unsigned char ch3 = reader.nextToken();

      if (ch3 == 'u') {
        unsigned char ch4 = reader.nextToken();

        if (ch4 == 'e') {
          unsigned char ch5 = reader.nextToken();

          reader.prevToken();

          if (!Lexer::isCharIdentifier(ch5)) {
            this->token = LEXER_BOOLEAN_LITERAL;
            this->rawValue += ch1;
            this->rawValue += ch2;
            this->rawValue += ch3;
            this->rawValue += ch4;
            this->value = this->rawValue;

            return true;
          }
        }
      }
    }
  } else if (ch1 == 'f') {
    unsigned char ch2 = reader.nextToken();

    if (ch2 == 'a') {
      unsigned char ch3 = reader.nextToken();

      if (ch3 == 'l') {
        unsigned char ch4 = reader.nextToken();

        if (ch4 == 's') {
          unsigned char ch5 = reader.nextToken();

          if (ch5 == 'e') {
            unsigned char ch6 = reader.nextToken();

            reader.prevToken();

            if (!Lexer::isCharIdentifier(ch6)) {
              this->token = LEXER_BOOLEAN_LITERAL;
              this->rawValue += ch1;
              this->rawValue += ch2;
              this->rawValue += ch3;
              this->rawValue += ch4;
              this->rawValue += ch5;
              this->value = this->rawValue;

              return true;
            }
          }
        }
      }
    }
  }

  reader.restoreCursor(READER_CURSOR_SECONDARY);
  return false;
}

bool Lexer::_isLiteralNil(Reader &reader) {
  unsigned char ch1 = reader.nextToken();

  if (ch1 == 'n') {
    unsigned char ch2 = reader.nextToken();

    if (ch2 == 'i') {
      unsigned char ch3 = reader.nextToken();

      if (ch3 == 'l') {
        unsigned char ch4 = reader.nextToken();

        reader.prevToken();

        if (!Lexer::isCharIdentifier(ch4)) {
          this->token = LEXER_NIL_LITERAL;
          this->rawValue += ch1;
          this->rawValue += ch2;
          this->rawValue += ch3;
          this->value = this->rawValue;

          return true;
        }
      }
    }
  }

  reader.restoreCursor(READER_CURSOR_SECONDARY);
  return false;
}

bool Lexer::_isLiteralNumber(Reader &reader) {
  unsigned char ch = reader.nextToken();

  if (Lexer::isCharLiteralNumberStart(ch)) {
    this->token = LEXER_NUMBER_LITERAL;
  } else if (ch == '0') {
    if (!reader.cursor3.isEOF) {
      ch = reader.nextToken();

      if (Lexer::isCharLiteralNumber(ch)) {
        reader.restoreCursor(READER_CURSOR_SECONDARY);
        return false;
      }

      reader.prevToken();
    }

    this->token = LEXER_NUMBER_LITERAL;
    this->rawValue = '0';
    this->value = this->rawValue;

    return true;
  } else {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  this->rawValue += ch;

  while (!reader.cursor3.isEOF) {
    ch = reader.nextToken();

    if (!Lexer::isCharLiteralNumber(ch)) {
      reader.prevToken();
      break;
    }

    this->rawValue += ch;
  }

  this->value = this->rawValue;
  return true;
}

bool Lexer::_isLiteralString(Reader &reader) {
  unsigned char ch = reader.nextToken();

  if (ch != '\'' && ch != '"') {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  if (ch == '"') {
    this->token = LEXER_STRING_LITERAL_DQ;
  } else {
    this->token = LEXER_STRING_LITERAL_SQ;
  }

  this->rawValue += ch;

  std::string errorMessage = "Unexpected end of file, expected end of string";

  if (reader.cursor3.isEOF) {
    throw Exception(errorMessage, reader);
  }

  while (true) {
    ch = reader.nextToken();

    bool isEndOfDQ = this->token == LEXER_STRING_LITERAL_DQ && ch == '"';
    bool isEndOfSQ = this->token == LEXER_STRING_LITERAL_SQ && ch == '\'';

    this->rawValue += ch;

    if (isEndOfDQ || isEndOfSQ) {
      break;
    } else if (reader.cursor3.isEOF) {
      throw Exception(errorMessage, reader);
    }
  }

  this->value = this->rawValue.substr(1, this->rawValue.length() - 2);
  return true;
}

bool Lexer::_isMark(Reader &reader) {
  unsigned char ch = reader.nextToken();

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
      reader.restoreCursor(READER_CURSOR_SECONDARY);
      return false;
    }
  }

  this->rawValue = ch;
  this->value = this->rawValue;

  return true;
}

bool Lexer::_isSign(Reader &reader) {
  unsigned char ch = reader.nextToken();

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
      reader.restoreCursor(READER_CURSOR_SECONDARY);
      return false;
    }
  }

  this->rawValue = ch;
  this->value = this->rawValue;

  return true;
}

bool Lexer::_isWhitespace(Reader &reader) {
  unsigned char ch = reader.nextToken();

  if (Lexer::isCharWhitespace(ch)) {
    this->token = LEXER_WS;
  } else {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return false;
  }

  this->rawValue += ch;

  while (!reader.cursor3.isEOF) {
    ch = reader.nextToken();

    if (!Lexer::isCharWhitespace(ch)) {
      reader.prevToken();
      break;
    }

    this->rawValue += ch;
  }

  this->value = this->rawValue;
  return true;
}
