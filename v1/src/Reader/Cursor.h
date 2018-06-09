/**
 * @created_at: 2019-06-26 13:02:08
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

#ifndef SRC_READER_CURSOR_H
#define SRC_READER_CURSOR_H

#include "Location.h"

namespace let {
  typedef enum ReaderCursorToken {
    READER_CURSOR_UNKNOWN,
    READER_CURSOR_MAIN,
    READER_CURSOR_PRIMARY,
    READER_CURSOR_SECONDARY
  } ReaderCursorToken;

  class ReaderCursor {
   public:
    static const uint8 ERR_CHAR = -1;

    bool isEOF = false;
    String line;
    uint32 lineLen = 0;
    ReaderLocation location;
    ReaderCursorToken token = READER_CURSOR_UNKNOWN;

    uint8 getChar();
  };
}

#endif
