/**
 * @created_at: 2019-07-06 11:15:24
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

#include "CommentLine.h"

namespace let {
  bool LexerCommentLine::is(Lexer *lexer, Reader &reader) {
    uint8 ch1 = reader.nextToken();

    if (ch1 != '/') {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    uint8 ch2 = reader.nextToken();

    if (ch2 != '/') {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    lexer->rawValue += ch1;
    lexer->rawValue += ch2;

    while (!reader.cursor3.isEOF) {
      uint8 ch3 = reader.nextToken();

      if (ch3 == '\n') {
        reader.prevToken();

        break;
      }

      lexer->rawValue += ch3;
    }

    lexer->token = LEXER_LINE_COMMENT;
    lexer->value = lexer->rawValue.substr(2, lexer->rawValue.length() - 2);

    lexer->epilogue(reader);

    return true;
  }
}
