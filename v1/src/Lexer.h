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

#ifndef SRC_LEXER_H
#define SRC_LEXER_H

#include "Reader.h"
#include "Reader/LocationRange.h"

namespace let {
  typedef enum LexerToken {
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
  } LexerToken;

  class Lexer {
   public:
    ReaderLocationRange locationRange;
    String rawValue;
    LexerToken token = LEXER_UNKNOWN;
    String value;

    explicit Lexer() = default;
    explicit Lexer(Reader &);

    virtual ~Lexer() = default;

    static bool isCharIdentifier(uint8);
    static bool isCharIdentifierStart(uint8);
    static bool isCharLiteralNumber(uint8);
    static bool isCharLiteralNumberStart(uint8);
    static bool isCharWhitespace(uint8);

    virtual void epilogue(const Reader &);
    virtual bool isLiteral() const;
    virtual bool isSkippable() const;
  };
}

#endif
