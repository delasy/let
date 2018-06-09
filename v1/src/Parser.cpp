/**
 * @created_at: 2019-06-26 00:07:56
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

#include "Error.h"
#include "Parser.h"

namespace let {
  Parser::Parser(Reader &reader) {
    ParserSkippable parserSkippable(reader);

    if (parserSkippable.isInitialized()) {
      this->skippable = parserSkippable;
      this->token = PARSER_SKIPPABLE;

      reader.saveCursor(READER_CURSOR_MAIN);

      return;
    }

    reader.restoreCursor(READER_CURSOR_PRIMARY);

    ParserAssignExpr parserAssignExpr(reader);

    if (parserAssignExpr.isInitialized()) {
      this->assignExpr = parserAssignExpr;
      this->token = PARSER_ASSIGN_EXPR;

      reader.saveCursor(READER_CURSOR_MAIN);

      return;
    }

    reader.restoreCursor(READER_CURSOR_PRIMARY);

    ParserCallExpr parserCallExpr(reader);

    if (parserCallExpr.isInitialized()) {
      this->callExpr = parserCallExpr;
      this->token = PARSER_CALL_EXPR;

      reader.saveCursor(READER_CURSOR_MAIN);

      return;
    }

    reader.restoreCursor(READER_CURSOR_PRIMARY);

    String message = "Unexpected statement '";

    message += reader.cursor3.getChar();
    message += "'";

    throw Error::syntax(message, reader);
  }
}
