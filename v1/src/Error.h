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

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include "ErrorException.h"
#include "Reader.h"

namespace let {
  class Error {
   public:
    static ErrorException plain(const String &);
    static ErrorException syntax(const String &, const Reader &);
  };
}

#endif
