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

#include "Arguments.h"
#include "Error.h"
#include "Utils.h"

namespace let {
  Arguments::Arguments(int32 argc, const int8 **&argv) {
    this->count = argc;

    for (int32 i = 1; i < argc; i++) {
      String arg = argv[i];

      if (arg.substr(0, 9) == "--output=") {
        this->outputPath = arg.substr(9);

        continue;
      } if (arg.substr(0, 5) == "--os=") {
        String OS = arg.substr(5);

        if (OS == "mac" || OS == "mac64") {
          this->OSType = ARGUMENTS_OS_TYPE_MAC;
          this->OSWordSize = ARGUMENTS_OS_WORD_SIZE_64;

          continue;
        }
      } else if (arg == "-h" || arg == "--help") {
        this->isHelp = true;

        return;
      } else if (arg == "-v" || arg == "-V" || arg == "--version") {
        this->isVersion = true;

        return;
      }

      String resolvedSourcePath = Utils::fileResolve(arg);

      if (!resolvedSourcePath.empty()) {
        this->sourcePath = resolvedSourcePath;

        continue;
      }

      if (arg[0] == '-') {
        throw Error::plain("Passed unknown argument '" + arg + "'");
      } else {
        throw Error::plain("File or directory '" + arg + "' not found");
      }
    }

    if (this->count == 1 || this->sourcePath.empty()) {
      this->isREPL = true;

      throw Error::plain("REPL is not implemented");
    }
  }
}
