/**
 * @created_at: 2019-07-09 13:05:53
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

#ifndef TESTS_UNIT_READERMOCK_H
#define TESTS_UNIT_READERMOCK_H

#include "../../src/Reader.h"

namespace let {
  class ReaderMock : public Reader {
   public:
    MOCK_METHOD0(nextToken, uint8());
    MOCK_METHOD0(prevToken, uint8());
    MOCK_METHOD1(restoreCursor, void(ReaderCursorToken));
    MOCK_METHOD1(saveCursor, void(ReaderCursorToken));
  };
}

#endif
