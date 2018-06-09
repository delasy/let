/**
 * @created_at: 2019-06-25 20:35:47
 * @author: Aaron Delasy
 * @license_start
 *
 * Copyright (c) 2018-2019  Aaron Delasy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @license_end
 */

#include "Lexer/Bracket.h"
#include "Lexer/CommentBlock.h"
#include "Lexer/CommentLine.h"
#include "Lexer/Identifier.h"
#include "Lexer/KeywordReturn.h"
#include "Lexer/LiteralBoolean.h"
#include "Lexer/LiteralNil.h"
#include "Lexer/LiteralNumber.h"
#include "Lexer/LiteralString.h"
#include "Lexer/Mark.h"
#include "Lexer/Sign.h"
#include "Lexer/Whitespace.h"
#include "Error.h"
#include "Lexer.h"

namespace let {
  Lexer::Lexer(Reader &reader) {
    if (LexerWhitespace::is(this, reader)) {
      return;
    } else if (LexerBracket::is(this, reader)) {
      return;
    } else if (LexerCommentBlock::is(this, reader)) {
      return;
    } else if (LexerCommentLine::is(this, reader)) {
      return;
    } else if (LexerKeywordReturn::is(this, reader)) {
      return;
    } else if (LexerLiteralBoolean::is(this, reader)) {
      return;
    } else if (LexerLiteralNil::is(this, reader)) {
      return;
    } else if (LexerLiteralNumber::is(this, reader)) {
      return;
    } else if (LexerLiteralString::is(this, reader)) {
      return;
    } else if (LexerMark::is(this, reader)) {
      return;
    } else if (LexerSign::is(this, reader)) {
      return;
    } else if (LexerIdentifier::is(this, reader)) {
      return;
    }

    uint8 lineChar = reader.cursor3.getChar();
    String message = "Unexpected token '";

    message += lineChar;
    message += "'";

    throw Error::syntax(message, reader);
  }

  bool Lexer::isCharIdentifier(uint8 ch) {
    String possibleIdentifierCharacters = "abcdefghijklmnopqrstuvwxyz";

    possibleIdentifierCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ_$";
    possibleIdentifierCharacters += "0123456789";

    return possibleIdentifierCharacters.find(ch) != String::npos;
  }

  bool Lexer::isCharIdentifierStart(uint8 ch) {
    String possibleIdentifierCharacters = "abcdefghijklmnopqrstuvwxyz";

    possibleIdentifierCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ_$";

    return possibleIdentifierCharacters.find(ch) != String::npos;
  }

  bool Lexer::isCharLiteralNumber(uint8 ch) {
    String possibleLiteralCharacters = "0123456789";

    return possibleLiteralCharacters.find(ch) != String::npos;
  }

  bool Lexer::isCharLiteralNumberStart(uint8 ch) {
    String possibleLiteralCharacters = "123456789";

    return possibleLiteralCharacters.find(ch) != String::npos;
  }

  bool Lexer::isCharWhitespace(uint8 ch) {
    return ch == ' ' ||
      ch == '\r' ||
      ch == '\n' ||
      ch == '\f' ||
      ch == '\t' ||
      ch == '\v' ||
      ch == '\b';
  }

  void Lexer::epilogue(const Reader &reader) {
    this->locationRange.end = reader.cursor3.location;
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
}
