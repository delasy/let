/**
 * @created_at: 2019-06-23 18:14:48
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
#include "Console.h"

namespace let {
  ErrorException Error::plain(const String &message) {
    String errorMessage;

    errorMessage += Console::TEXT_RED;
    errorMessage += "Error: " + message;
    errorMessage += Console::RESET;

    return ErrorException(errorMessage);
  }

  ErrorException Error::syntax(const String &message, const Reader &reader) {
    String errorMessage;

    errorMessage += Console::TEXT_RED;
    errorMessage += "SyntaxError: " + message + " at ";
    errorMessage += Console::RESET;
    errorMessage += OS_EOL;
    errorMessage += Console::TEXT_RED;
    errorMessage += "  " + reader.filePath;
    errorMessage += ":";
    errorMessage += std::to_string(reader.cursor3.location.lineNum);
    errorMessage += ":";
    errorMessage += std::to_string(reader.cursor3.location.charIdx);
    errorMessage += Console::RESET;

    return ErrorException(errorMessage);
  }
}
