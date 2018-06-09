/**
 * @created_at: 2019-07-06 12:19:20
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

#include "LiteralString.h"
#include "../Error.h"

namespace let {
  bool LexerLiteralString::is(Lexer *lexer, Reader &reader) {
    uint8 ch = reader.nextToken();

    if (ch != '\'' && ch != '"') {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    if (ch == '"') {
      lexer->token = LEXER_STRING_LITERAL_DQ;
    } else {
      lexer->token = LEXER_STRING_LITERAL_SQ;
    }

    lexer->rawValue += ch;

    String errmsg = "Unexpected end of file, expected end of string";

    if (reader.cursor3.isEOF) {
      throw Error::syntax(errmsg, reader);
    }

    while (true) {
      ch = reader.nextToken();

      bool isEndOfDQ = lexer->token == LEXER_STRING_LITERAL_DQ && ch == '"';
      bool isEndOfSQ = lexer->token == LEXER_STRING_LITERAL_SQ && ch == '\'';

      lexer->rawValue += ch;

      if (isEndOfDQ || isEndOfSQ) {
        break;
      } else if (reader.cursor3.isEOF) {
        throw Error::syntax(errmsg, reader);
      }
    }

    lexer->value = lexer->rawValue.substr(1, lexer->rawValue.length() - 2);

    lexer->epilogue(reader);

    return true;
  }
}
