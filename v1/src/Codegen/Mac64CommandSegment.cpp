/**
 * @created_at: 2019-06-30 14:26:32
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

#include "Mac64CommandSegment.h"

namespace let {
  CodegenMac64CommandSegment::CodegenMac64CommandSegment(
    const String &segName
  ) {
    this->segName = segName;
  }

  void CodegenMac64CommandSegment::addSec(const CodegenMac64Section &sec) {
    this->secsCount += 1;

    this->secs.push_back(sec);
  }

  uint32 CodegenMac64CommandSegment::getSize() {
    uint32 size = 0;

    for (CodegenMac64Section sec : this->secs) {
      size += sec.getSize();
    }

    return this->segNameSize +
      sizeof(this->vmAddr) +
      sizeof(this->vmSize) +
      sizeof(this->fileOffset) +
      sizeof(this->fileSize) +
      sizeof(this->maxProt) +
      sizeof(this->initProt) +
      sizeof(this->secsCount) +
      sizeof(this->flags) +
      size;
  }

  Binary CodegenMac64CommandSegment::toBinary() {
    Binary binary;

    binary.appendString(this->segName, this->segNameSize);

    binary += this->vmAddr;
    binary += this->vmSize;
    binary += this->fileOffset;
    binary += this->fileSize;
    binary += this->maxProt;
    binary += this->initProt;
    binary += this->secsCount;
    binary += this->flags;

    for (CodegenMac64Section sec : this->secs) {
      binary += sec.toBinary();
    }

    return binary;
  }
}
