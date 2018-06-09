/**
 * @created_at: 2019-06-23 18:36:43
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

#ifndef SRC_ARGUMENTS_H
#define SRC_ARGUMENTS_H

#include "types.h"

namespace let {
  typedef enum ArgumentsOSType {
    ARGUMENTS_OS_TYPE_ALL,
    ARGUMENTS_OS_TYPE_LINUX,
    ARGUMENTS_OS_TYPE_MAC,
    ARGUMENTS_OS_TYPE_WIN,
  } ArgumentsOSType;

  typedef enum ArgumentsOSWordSize {
    ARGUMENTS_OS_WORD_SIZE_ALL,
    ARGUMENTS_OS_WORD_SIZE_32,
    ARGUMENTS_OS_WORD_SIZE_64
  } ArgumentsOSWordSize;

  class Arguments {
   public:
    ArgumentsOSType OSType = ARGUMENTS_OS_TYPE_ALL;
    ArgumentsOSWordSize OSWordSize = ARGUMENTS_OS_WORD_SIZE_ALL;
    uint32 count = 0;
    bool isREPL = false;
    bool isHelp = false;
    bool isVersion = false;
    String outputPath = "a.out";
    String sourcePath;

    explicit Arguments() = default;
    explicit Arguments(int32, const int8 **&);
  };
}

#endif
