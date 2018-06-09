/**
 * @created_at: 2019-07-06 11:47:36
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

#include "LiteralNil.h"

namespace let {
  bool LexerLiteralNil::is(Lexer *lexer, Reader &reader) {
    uint8 ch1 = reader.nextToken();

    if (ch1 == 'n') {
      uint8 ch2 = reader.nextToken();

      if (ch2 == 'i') {
        uint8 ch3 = reader.nextToken();

        if (ch3 == 'l') {
          uint8 ch4 = reader.nextToken();

          reader.prevToken();

          if (!Lexer::isCharIdentifier(ch4)) {
            lexer->token = LEXER_NIL_LITERAL;
            lexer->rawValue += ch1;
            lexer->rawValue += ch2;
            lexer->rawValue += ch3;
            lexer->value = lexer->rawValue;

            lexer->epilogue(reader);

            return true;
          }
        }
      }
    }

    reader.restoreCursor(READER_CURSOR_SECONDARY);

    return false;
  }
}
