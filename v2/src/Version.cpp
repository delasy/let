#include "Version.hpp"

const std::string Version::NAME = "Alpha";
const std::string Version::NUMBER = "0.0.1";

unsigned int Version::a16b8c8(const std::string &version) {
  std::vector<unsigned int> versionVector = Version::toVector(version);
  unsigned int versionVectorSize = versionVector.size();
  unsigned int versionNum = 0;

  for (unsigned int i = 0; i < versionVectorSize; i++) {
    unsigned char shiftValue = 16 - (i * 8) <= 0 ? 0 : 16 - (i * 8);
    unsigned int versionValue = versionVector[i];

    versionNum += versionValue << shiftValue;
  }

  return versionNum;
}

unsigned long long Version::a24b10c10d10e10(const std::string &version) {
  std::vector<unsigned int> versionVector = Version::toVector(version);
  unsigned int versionVectorSize = versionVector.size();
  unsigned long long versionNum = 0;

  for (unsigned int i = 0; i < versionVectorSize; i++) {
    unsigned char shiftValue = 40 - (i * 10) <= 0 ? 0 : 40 - (i * 10);
    unsigned long long versionValue = versionVector[i];

    versionNum += versionValue << shiftValue;
  }

  return versionNum;
}

std::vector<unsigned int> Version::toVector(const std::string &version) {
  std::vector<unsigned int> versionVector;
  unsigned int idx = 0;

  versionVector.push_back(0);

  for (char ch : version) {
    if (ch == '.') {
      idx += 1;

      versionVector.push_back(0);
      continue;
    }

    versionVector[idx] = versionVector[idx] * 10 + (ch - '0');
  }

  return versionVector;
}
