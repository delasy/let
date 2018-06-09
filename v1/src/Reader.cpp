/**
 * @created_at: 2019-06-19 12:47:22
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

#include "Reader.h"
#include "Utils.h"

namespace let {
  Reader::Reader(const String &filePath) {
    this->_file.open(filePath.c_str());

    this->filePath = filePath;

    String line = Utils::fileLineRead(this->_file, 1);

    this->cursor1.token = READER_CURSOR_MAIN;
    this->cursor2.token = READER_CURSOR_PRIMARY;
    this->cursor3.token = READER_CURSOR_SECONDARY;

    this->cursor1.isEOF = line.empty();
    this->cursor2.isEOF = line.empty();
    this->cursor3.isEOF = line.empty();

    this->cursor1.line = line;
    this->cursor2.line = line;
    this->cursor3.line = line;

    this->cursor1.lineLen = line.length();
    this->cursor2.lineLen = line.length();
    this->cursor3.lineLen = line.length();
  }

  uint8 Reader::nextToken() {
    uint8 ch = this->cursor3.getChar();

    if (ch == ReaderCursor::ERR_CHAR) {
      return ch;
    }

    if (this->cursor3.location.charIdx >= this->cursor3.lineLen) {
      String line = Utils::fileLineRead(
        this->_file, this->cursor3.location.lineNum + 1
      );

      if (line.empty()) {
        this->cursor3.isEOF = true;

        if (ch == '\n') {
          this->cursor3.line = "";
          this->cursor3.lineLen = 0;
          this->cursor3.location.charIdx = 1;
          this->cursor3.location.lineNum++;
        }

        return ch;
      }

      this->cursor3.line = line;
      this->cursor3.lineLen = this->cursor3.line.length();
      this->cursor3.location.charIdx = 1;
      this->cursor3.location.lineNum++;
    } else {
      this->cursor3.location.charIdx++;
    }

    return ch;
  }

  uint8 Reader::prevToken() {
    uint8 ch = this->cursor3.getChar();

    if (this->cursor3.location.charIdx <= 1) {
      if (this->cursor3.location.lineNum - 1 <= 0) {
        return -1;
      }

      String line = Utils::fileLineRead(
        this->_file, this->cursor3.location.lineNum - 1
      );

      this->cursor3.line = line;
      this->cursor3.lineLen = this->cursor3.line.length();
      this->cursor3.location.charIdx = this->cursor3.lineLen;
      this->cursor3.location.lineNum--;
    } else {
      this->cursor3.location.charIdx--;
    }

    return ch;
  }

  void Reader::restoreCursor(ReaderCursorToken token) {
    ReaderCursor *targetCursor;
    ReaderCursor copyCursor;

    switch (token) {
      case READER_CURSOR_PRIMARY: {
        targetCursor = &this->cursor2;
        copyCursor = this->cursor1;

        break;
      }
      case READER_CURSOR_SECONDARY: {
        targetCursor = &this->cursor3;
        copyCursor = this->cursor2;

        break;
      }
      default: {
        return;
      }
    }

    targetCursor->isEOF = copyCursor.isEOF;
    targetCursor->line = copyCursor.line;
    targetCursor->lineLen = copyCursor.lineLen;
    targetCursor->location.charIdx = copyCursor.location.charIdx;
    targetCursor->location.lineNum = copyCursor.location.lineNum;

    if (token == READER_CURSOR_PRIMARY) {
      this->restoreCursor(READER_CURSOR_SECONDARY);
    }
  }

  void Reader::saveCursor(ReaderCursorToken token) {
    if (token == READER_CURSOR_MAIN) {
      this->saveCursor(READER_CURSOR_PRIMARY);
    }

    ReaderCursor *targetCursor;
    ReaderCursor saveCursor;

    switch (token) {
      case READER_CURSOR_MAIN: {
        targetCursor = &this->cursor1;
        saveCursor = this->cursor2;

        break;
      }
      case READER_CURSOR_PRIMARY: {
        targetCursor = &this->cursor2;
        saveCursor = this->cursor3;

        break;
      }
      default: {
        return;
      }
    }

    targetCursor->isEOF = saveCursor.isEOF;
    targetCursor->line = saveCursor.line;
    targetCursor->lineLen = saveCursor.lineLen;
    targetCursor->location.charIdx = saveCursor.location.charIdx;
    targetCursor->location.lineNum = saveCursor.location.lineNum;
  }
}
