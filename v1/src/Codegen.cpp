/**
 * @created_at: 2019-06-29 20:18:47
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

#include "Codegen/Mac64.h"
#include "Codegen.h"

namespace let {
  Codegen::Codegen(const Arguments &arguments, const AST &ast) {
    bool isCodegenMac64 = arguments.OSType == ARGUMENTS_OS_TYPE_MAC &&
      arguments.OSWordSize == ARGUMENTS_OS_WORD_SIZE_64;

    if (isCodegenMac64) {
      CodegenMac64 mac64(ast);

      this->binary = mac64.binary;
    }
  }
}
