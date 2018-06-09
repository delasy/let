/**
 * @created_at: 2019-06-27 13:53:44
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

#include "ArgList.h"
#include "Skippable.h"
#include "../Error.h"

namespace let {
  ParserArgList::ParserArgList(Reader &reader) {
    Lexer lexer(reader);

    reader.restoreCursor(READER_CURSOR_SECONDARY);

    while (lexer.token != LEXER_RPAR) {
      ParserExpr parserExpr(reader);

      if (!parserExpr.isInitialized()) {
        String message = "Unexpected token '";

        message += reader.cursor3.getChar();
        message += "', expected expression";

        throw Error::syntax(message, reader);
      }

      this->exprs.push_back(parserExpr);

      ParserSkippable parserSkippable1(reader);

      lexer = Lexer(reader);

      if (lexer.token == LEXER_COMMA) {
        reader.saveCursor(READER_CURSOR_PRIMARY);

        ParserSkippable parserSkippable2(reader);

        continue;
      }

      reader.restoreCursor(READER_CURSOR_SECONDARY);

      if (lexer.token != LEXER_RPAR) {
        String message = "Unexpected token '";

        message += reader.cursor3.getChar();
        message += "', expected comma or right parenthesis";

        throw Error::syntax(message, reader);
      }
    }

    this->initialize_();
  }
}
