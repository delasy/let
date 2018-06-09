/**
 * @created_at: 2019-06-19 22:52:25
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

#ifndef SRC_UTILS_H
#define SRC_UTILS_H

#include <vector>

#include "types.h"

#if OS_FAMILY == OS_FAMILY_LINUX || OS_FAMILY == OS_FAMILY_MACOS
  #include <climits>
  #include <unistd.h>

  #define CWD_GET getcwd
#endif

namespace let {
  class Utils {
   public:
    static String fileLineRead(File &, uint32);
    static String fileResolve(const String &);
    static bool isFileExists(const String &);
    static String pathCanonize(const String &);
    static uint32 versionA16B8C8(const String &);
    static uint64 versionA24B10C10D10E10(const String &);
    static std::vector<uint32> versionToVector(const String &);
    static String workingDirResolve();
  };
}

#endif
