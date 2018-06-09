/**
 * @created_at: 2019-07-06 11:41:44
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

#include "Identifier.h"

namespace let {
  bool LexerIdentifier::is(Lexer *lexer, Reader &reader) {
    uint8 ch = reader.nextToken();

    if (Lexer::isCharIdentifierStart(ch)) {
      lexer->token = LEXER_ID;
    } else {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    lexer->rawValue += ch;

    while (!reader.cursor3.isEOF) {
      ch = reader.nextToken();

      if (!Lexer::isCharIdentifier(ch)) {
        reader.prevToken();

        break;
      }

      lexer->rawValue += ch;
    }

    lexer->value = lexer->rawValue;

    lexer->epilogue(reader);

    return true;
  }
}
