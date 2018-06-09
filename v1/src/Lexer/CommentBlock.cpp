/**
 * @created_at: 2019-07-06 11:19:29
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

#include "CommentBlock.h"
#include "../Error.h"

namespace let {
  bool LexerCommentBlock::is(Lexer *lexer, Reader &reader) {
    uint8 ch1 = reader.nextToken();

    if (ch1 != '/') {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    uint8 ch2 = reader.nextToken();

    if (ch2 != '*') {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return false;
    }

    lexer->rawValue += ch1;
    lexer->rawValue += ch2;

    String errmsg = "Unexpected end of file, expected end of block comment";

    if (reader.cursor3.isEOF) {
      throw Error::syntax(errmsg, reader);
    }

    uint8 ch3 = reader.nextToken();

    lexer->rawValue += ch3;

    if (reader.cursor3.isEOF) {
      throw Error::syntax(errmsg, reader);
    }

    while (true) {
      uint8 ch4 = reader.nextToken();

      lexer->rawValue += ch4;

      if (ch3 == '*' && ch4 == '/') {
        break;
      } else if (reader.cursor3.isEOF) {
        throw Error::syntax(errmsg, reader);
      }

      ch3 = ch4;
    }

    lexer->token = LEXER_BLOCK_COMMENT;
    lexer->value = lexer->rawValue.substr(2, lexer->rawValue.length() - 4);

    lexer->epilogue(reader);

    return true;
  }
}
