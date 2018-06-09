/**
 * @created_at: 2019-07-01 13:10:32
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

#ifndef SRC_CONSOLE_H
#define SRC_CONSOLE_H

#include "types.h"

namespace let {
  class Console {
   public:
    static constexpr int8 RESET[5] = "\x1B[0m";
    static constexpr int8 BRIGHT[5] = "\x1B[1m";
    static constexpr int8 DIM[5] = "\x1B[2m";
    static constexpr int8 UNDERSCORE[5] = "\x1B[4m";
    static constexpr int8 BLICK[5] = "\x1B[5m";
    static constexpr int8 REVERSE[5] = "\x1B[7m";
    static constexpr int8 HIDDEN[5] = "\x1B[8m";
    static constexpr int8 TEXT_BLACK[6] = "\x1B[30m";
    static constexpr int8 TEXT_RED[6] = "\x1B[31m";
    static constexpr int8 TEXT_GREEN[6] = "\x1B[32m";
    static constexpr int8 TEXT_YELLOW[6] = "\x1B[33m";
    static constexpr int8 TEXT_BLUE[6] = "\x1B[34m";
    static constexpr int8 TEXT_MAGENTA[6] = "\x1B[35m";
    static constexpr int8 TEXT_CYAN[6] = "\x1B[36m";
    static constexpr int8 TEXT_WHITE[6] = "\x1B[37m";
    static constexpr int8 BG_BLACK[6] = "\x1B[40m";
    static constexpr int8 BG_RED[6] = "\x1B[41m";
    static constexpr int8 BG_GREEN[6] = "\x1B[42m";
    static constexpr int8 BG_YELLOW[6] = "\x1B[43m";
    static constexpr int8 BG_BLUE[6] = "\x1B[44m";
    static constexpr int8 BG_MAGENTA[6] = "\x1B[45m";
    static constexpr int8 BG_CYAN[6] = "\x1B[46m";
    static constexpr int8 BG_WHITE[6] = "\x1B[47m";
  };
}

#endif
