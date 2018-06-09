/**
 * @created_at: 2019-06-19 12:47:23
 * @author: Aaron Delasy
 * @license_start
 *
 * Copyright (c) 2018  Aaron Delasy
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

#ifndef SRC_READER_H
#define SRC_READER_H

#include "Reader/Cursor.h"

namespace let {
  class Reader {
   public:
    ReaderCursor cursor1;
    ReaderCursor cursor2;
    ReaderCursor cursor3;
    String filePath;

    explicit Reader() = default;
    explicit Reader(const String &);

    virtual ~Reader() = default;

    virtual uint8 nextToken();
    virtual uint8 prevToken();
    virtual void restoreCursor(ReaderCursorToken);
    virtual void saveCursor(ReaderCursorToken);

   private:
    File _file;
  };
}

#endif
