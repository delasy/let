/**
 * @created_at: 2019-06-26 13:13:42
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

#include "CallExpr.h"
#include "Skippable.h"

namespace let {
  ParserCallExpr::ParserCallExpr(Reader &reader) {
    ParserId parserId(reader);

    if (!parserId.isInitialized()) {
      return;
    }

    ParserSkippable parserSkippable1(reader);
    Lexer lexerLPar(reader);

    if (lexerLPar.token != LEXER_LPAR) {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return;
    }

    reader.saveCursor(READER_CURSOR_PRIMARY);

    ParserSkippable parserSkippable2(reader);
    ParserArgList parserArgList(reader);

    if (!parserArgList.isInitialized()) {
      return;
    }

    ParserSkippable parserSkippable3(reader);
    Lexer lexerRPar(reader);

    if (lexerRPar.token != LEXER_RPAR) {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      return;
    }

    reader.saveCursor(READER_CURSOR_PRIMARY);

    this->id = parserId;
    this->argList = parserArgList;

    this->initialize_();
  }
}
