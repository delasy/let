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

#include "Utils.h"

namespace let {
  String Utils::fileLineRead(File &file, uint32 lineNum) {
    file.seekg(0, file.end);

    uint32 fileLen = file.tellg();

    file.seekg(0, file.beg);

    uint32 currFileLen = 0;
    uint32 currLineNum = 1;
    String line;

    for (String currLine; getline(file, currLine); currLineNum++) {
      currFileLen += currLine.length();

      if (currLineNum == lineNum) {
        line = currLine;

        if (currFileLen + 1 <= fileLen) {
          line += OS_EOL;
        }

        break;
      }

      currFileLen += 1;
    }

    return line;
  }

  String Utils::fileResolve(const String &initialPath) {
    String workingDir = Utils::workingDirResolve();
    String path = workingDir + '/' + initialPath;
    String absolutePath = Utils::pathCanonize(path);

    if (!absolutePath.empty() && Utils::isFileExists(absolutePath)) {
      return absolutePath;
    }

    absolutePath = Utils::pathCanonize(path + ".let");

    if (!absolutePath.empty() && Utils::isFileExists(absolutePath)) {
      return absolutePath;
    }

    return "";
  }

  bool Utils::isFileExists(const String &fileName) {
    Stat buffer;

    return stat(fileName.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode);
  }

  String Utils::pathCanonize(const String &initialPath) {
    int8 *path = realpath(initialPath.c_str(), nullptr);
    String strPath;

    if (path != nullptr) {
      strPath = path;

      free(path);
    }

    return strPath;
  }

  uint32 Utils::versionA16B8C8(const String &version) {
    std::vector<uint32> versionVector = Utils::versionToVector(version);
    uint32 versionVectorSize = versionVector.size();
    uint32 versionNum = 0;

    for (uint32 i = 0; i < versionVectorSize; i++) {
      uint8 shiftValue = 16 - (i * 8) <= 0 ? 0 : 16 - (i * 8);
      uint32 versionValue = versionVector[i];

      versionNum += versionValue << shiftValue;
    }

    return versionNum;
  }

  uint64 Utils::versionA24B10C10D10E10(const String &version) {
    std::vector<uint32> versionVector = Utils::versionToVector(version);
    uint32 versionVectorSize = versionVector.size();
    uint64 versionNum = 0;

    for (uint32 i = 0; i < versionVectorSize; i++) {
      uint8 shiftValue = 40 - (i * 10) <= 0 ? 0 : 40 - (i * 10);
      uint64 versionValue = versionVector[i];

      versionNum += versionValue << shiftValue;
    }

    return versionNum;
  }

  std::vector<uint32> Utils::versionToVector(const String &version) {
    std::vector<uint32> versionVector;
    uint32 idx = 0;

    versionVector.push_back(0);

    for (int8 ch : version) {
      if (ch == '.') {
        idx += 1;

        versionVector.push_back(0);

        continue;
      }

      versionVector[idx] = versionVector[idx] * 10 + (ch - '0');
    }

    return versionVector;
  }

  String Utils::workingDirResolve() {
    int8 buffer[PATH_MAX];
    int8 *workingDir = CWD_GET(buffer, sizeof(buffer));
    String workingDirStr;

    if (workingDir != nullptr) {
      workingDirStr = workingDir;
    }

    return Utils::pathCanonize(workingDirStr);
  }
}
