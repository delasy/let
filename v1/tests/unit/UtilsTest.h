/**
 * @created_at: 2019-06-21 17:37:37
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

#ifndef TESTS_UTILSTEST_H
#define TESTS_UTILSTEST_H

#include "../../src/Utils.h"

namespace let {
  class UtilsFileLineReadTest : public testing::Test {
   protected:
    File file_;
    File fileEofNl_;
    File fileEofNoNl_;

    void SetUp() override {
      this->file_.open("tests/fixtures/file.let");
      this->fileEofNl_.open("tests/fixtures/file_eof_nl.let");
      this->fileEofNoNl_.open("tests/fixtures/file_eof_no_nl.let");
    }
  };

  TEST_F(UtilsFileLineReadTest, FirstLine) {
    String line = Utils::fileLineRead(this->file_, 1);
    String lineTest = "a = 1" OS_EOL;

    EXPECT_EQ(line, lineTest);
  }

  TEST_F(UtilsFileLineReadTest, LastLineEofNl) {
    String line = Utils::fileLineRead(this->fileEofNl_, 1);
    String lineTest = "a = 1" OS_EOL;

    EXPECT_EQ(line, lineTest);
  }

  TEST_F(UtilsFileLineReadTest, LastLineEofNoNl) {
    String line = Utils::fileLineRead(this->fileEofNoNl_, 1);

    EXPECT_EQ(line, "a = 1");
  }

  TEST_F(UtilsFileLineReadTest, MultipleLines) {
    String line = Utils::fileLineRead(this->file_, 2);
    String lineTest = "b = 'sq string'" OS_EOL;

    EXPECT_EQ(line, lineTest);

    line = Utils::fileLineRead(this->file_, 4);
    lineTest = "d = false" OS_EOL;

    EXPECT_EQ(line, lineTest);

    line = Utils::fileLineRead(this->file_, 3);
    lineTest = "c = \"dq string\"" OS_EOL;

    EXPECT_EQ(line, lineTest);

    line = Utils::fileLineRead(this->file_, 5);
    lineTest = "e = true" OS_EOL;

    EXPECT_EQ(line, lineTest);
  }

  TEST_F(UtilsFileLineReadTest, NotExistingZeroLine) {
    String line = Utils::fileLineRead(this->file_, 0);

    EXPECT_TRUE(line.empty());
  }

  TEST_F(UtilsFileLineReadTest, NotExistingLargeLine) {
    String line = Utils::fileLineRead(this->file_, 9999999);

    EXPECT_TRUE(line.empty());
  }

  TEST(UtilsFileResolveTest, File) {
    String path = Utils::fileResolve("tests/fixtures/file.let");
    uint32 pathTailLen = path.length() - 23;

    ASSERT_GT(pathTailLen, 0);
    EXPECT_EQ(path.substr(pathTailLen), "tests/fixtures/file.let");
  }

  TEST(UtilsFileResolveTest, FileWithoutExtension) {
    String path = Utils::fileResolve("tests/fixtures/file");
    uint32 pathTailLen = path.length() - 23;

    ASSERT_GT(pathTailLen, 0);
    EXPECT_EQ(path.substr(pathTailLen), "tests/fixtures/file.let");
  }

  TEST(UtilsFileResolveTest, NotExistingFile) {
    String path = Utils::fileResolve("tests/fixtures/_file.let");

    EXPECT_TRUE(path.empty());
  }

  TEST(UtilsFileResolveTest, Directory) {
    String path = Utils::fileResolve("tests/fixtures");

    EXPECT_TRUE(path.empty());
  }

  TEST(UtilsIsFileExistsTest, File) {
    EXPECT_TRUE(Utils::isFileExists("tests/fixtures/file.let"));
  }

  TEST(UtilsIsFileExistsTest, SymlinkFile) {
    EXPECT_TRUE(Utils::isFileExists("tests/fixtures/file_.let"));
  }

  TEST(UtilsIsFileExistsTest, NotExistingFile) {
    EXPECT_FALSE(Utils::isFileExists("tests/fixtures/file__.let"));
  }

  TEST(UtilsIsFileExistsTest, Directory) {
    EXPECT_FALSE(Utils::isFileExists("tests/fixtures"));
  }

  class UtilsPathCanonizeTest : public testing::Test {
   protected:
    String workingDir_;

    void SetUp() override {
      this->workingDir_ = Utils::workingDirResolve();
    }
  };

  TEST_F(UtilsPathCanonizeTest, DotPath) {
    String path = Utils::pathCanonize(this->workingDir_ + "/.");

    EXPECT_EQ(path, this->workingDir_);
  }

  TEST_F(UtilsPathCanonizeTest, DoubleDotPath) {
    String path = Utils::pathCanonize(this->workingDir_ + "/src/..");

    EXPECT_EQ(path, this->workingDir_);
  }

  TEST_F(UtilsPathCanonizeTest, SlashPath) {
    String path = Utils::pathCanonize(this->workingDir_ + "/");

    EXPECT_EQ(path, this->workingDir_);
  }

  TEST_F(UtilsPathCanonizeTest, SymlinkFile) {
    String path = Utils::pathCanonize(
      this->workingDir_ + "/tests/fixtures/file_.let"
    );

    EXPECT_EQ(path, this->workingDir_ + "/tests/fixtures/file.let");
  }

  TEST(UtilsVersionA16B8C8, Empty) {
    uint32 version = Utils::versionA16B8C8("");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA16B8C8, Single) {
    uint32 version = Utils::versionA16B8C8("1");

    EXPECT_EQ(version, 0x10000);
  }

  TEST(UtilsVersionA16B8C8, SingleMinimum) {
    uint32 version = Utils::versionA16B8C8("0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA16B8C8, SingleMaximum) {
    uint32 version = Utils::versionA16B8C8("65535");

    EXPECT_EQ(version, 0xFFFF0000);
  }

  TEST(UtilsVersionA16B8C8, Double) {
    uint32 version = Utils::versionA16B8C8("1.2");

    EXPECT_EQ(version, 0x10200);
  }

  TEST(UtilsVersionA16B8C8, DoubleMinimum) {
    uint32 version = Utils::versionA16B8C8("0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA16B8C8, DoubleMaximum) {
    uint32 version = Utils::versionA16B8C8("65535.255");

    EXPECT_EQ(version, 0xFFFFFF00);
  }

  TEST(UtilsVersionA16B8C8, Triple) {
    uint32 version = Utils::versionA16B8C8("1.2.3");

    EXPECT_EQ(version, 0x10203);
  }

  TEST(UtilsVersionA16B8C8, TripleMinimum) {
    uint32 version = Utils::versionA16B8C8("0.0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA16B8C8, TripleMaximum) {
    uint32 version = Utils::versionA16B8C8("65535.255.255");

    EXPECT_EQ(version, 0xFFFFFFFF);
  }

  TEST(UtilsVersionA24B10C10D10E10, Empty) {
    uint64 version = Utils::versionA24B10C10D10E10("");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, Single) {
    uint64 version = Utils::versionA24B10C10D10E10("1");

    EXPECT_EQ(version, 0x10000000000);
  }

  TEST(UtilsVersionA24B10C10D10E10, SingleMinimum) {
    uint64 version = Utils::versionA24B10C10D10E10("0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, SingleMaximum) {
    uint64 version = Utils::versionA24B10C10D10E10("16777215");

    EXPECT_EQ(version, 0xFFFFFF0000000000);
  }

  TEST(UtilsVersionA24B10C10D10E10, Double) {
    uint64 version = Utils::versionA24B10C10D10E10("1.2");

    EXPECT_EQ(version, 0x10080000000);
  }

  TEST(UtilsVersionA24B10C10D10E10, DoubleMinimum) {
    uint64 version = Utils::versionA24B10C10D10E10("0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, DoubleMaximum) {
    uint64 version = Utils::versionA24B10C10D10E10("16777215.1023");

    EXPECT_EQ(version, 0xFFFFFFFFC0000000);
  }

  TEST(UtilsVersionA24B10C10D10E10, Triple) {
    uint64 version = Utils::versionA24B10C10D10E10("1.2.3");

    EXPECT_EQ(version, 0x10080300000);
  }

  TEST(UtilsVersionA24B10C10D10E10, TripleMinimum) {
    uint64 version = Utils::versionA24B10C10D10E10("0.0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, TripleMaximum) {
    uint64 version = Utils::versionA24B10C10D10E10("16777215.1023.1023");

    EXPECT_EQ(version, 0xFFFFFFFFFFF00000);
  }

  TEST(UtilsVersionA24B10C10D10E10, Quadruple) {
    uint64 version = Utils::versionA24B10C10D10E10("1.2.3.4");

    EXPECT_EQ(version, 0x10080301000);
  }

  TEST(UtilsVersionA24B10C10D10E10, QuadrupleMinimum) {
    uint64 version = Utils::versionA24B10C10D10E10("0.0.0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, QuadrupleMaximum) {
    uint64 version = Utils::versionA24B10C10D10E10("16777215.1023.1023.1023");

    EXPECT_EQ(version, 0xFFFFFFFFFFFFFC00);
  }

  TEST(UtilsVersionA24B10C10D10E10, Quintuple) {
    uint64 version = Utils::versionA24B10C10D10E10("1.2.3.4.5");

    EXPECT_EQ(version, 0x10080301005);
  }

  TEST(UtilsVersionA24B10C10D10E10, QuintupleMinimum) {
    uint64 version = Utils::versionA24B10C10D10E10("0.0.0.0.0");

    EXPECT_EQ(version, 0);
  }

  TEST(UtilsVersionA24B10C10D10E10, QuintupleMaximum) {
    uint64 version = Utils::versionA24B10C10D10E10(
      "16777215.1023.1023.1023.1023"
    );

    EXPECT_EQ(version, 0xFFFFFFFFFFFFFFFF);
  }

  TEST(UtilsVersionToVector, Empty) {
    std::vector<uint32> versionVector = Utils::versionToVector("");

    ASSERT_EQ(versionVector.size(), 1);
    EXPECT_EQ(versionVector[0], 0);
  }

  TEST(UtilsVersionToVector, Single) {
    std::vector<uint32> versionVector = Utils::versionToVector("1");

    ASSERT_EQ(versionVector.size(), 1);
    EXPECT_EQ(versionVector[0], 1);
  }

  TEST(UtilsVersionToVector, SingleMinimum) {
    std::vector<uint32> versionVector = Utils::versionToVector("0");

    ASSERT_EQ(versionVector.size(), 1);
    EXPECT_EQ(versionVector[0], 0);
  }

  TEST(UtilsVersionToVector, SingleMaximum) {
    std::vector<uint32> versionVector = Utils::versionToVector("4294967295");

    ASSERT_EQ(versionVector.size(), 1);
    EXPECT_EQ(versionVector[0], 0xFFFFFFFF);
  }

  TEST(UtilsVersionToVector, Double) {
    std::vector<uint32> versionVector = Utils::versionToVector("1.2");

    ASSERT_EQ(versionVector.size(), 2);
    EXPECT_EQ(versionVector[0], 1);
    EXPECT_EQ(versionVector[1], 2);
  }

  TEST(UtilsVersionToVector, DoubleMinimum) {
    std::vector<uint32> versionVector = Utils::versionToVector("0.0");

    ASSERT_EQ(versionVector.size(), 2);
    EXPECT_EQ(versionVector[0], 0);
    EXPECT_EQ(versionVector[1], 0);
  }

  TEST(UtilsVersionToVector, DoubleMaximum) {
    std::vector<uint32> versionVector = Utils::versionToVector(
      "4294967295.4294967295"
    );

    ASSERT_EQ(versionVector.size(), 2);
    EXPECT_EQ(versionVector[0], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[1], 0xFFFFFFFF);
  }

  TEST(UtilsVersionToVector, Triple) {
    std::vector<uint32> versionVector = Utils::versionToVector("1.2.3");

    ASSERT_EQ(versionVector.size(), 3);
    EXPECT_EQ(versionVector[0], 1);
    EXPECT_EQ(versionVector[1], 2);
    EXPECT_EQ(versionVector[2], 3);
  }

  TEST(UtilsVersionToVector, TripleMinimum) {
    std::vector<uint32> versionVector = Utils::versionToVector("0.0.0");

    ASSERT_EQ(versionVector.size(), 3);
    EXPECT_EQ(versionVector[0], 0);
    EXPECT_EQ(versionVector[1], 0);
    EXPECT_EQ(versionVector[2], 0);
  }

  TEST(UtilsVersionToVector, TripleMaximum) {
    std::vector<uint32> versionVector = Utils::versionToVector(
      "4294967295.4294967295.4294967295"
    );

    ASSERT_EQ(versionVector.size(), 3);
    EXPECT_EQ(versionVector[0], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[1], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[2], 0xFFFFFFFF);
  }

  TEST(UtilsVersionToVector, Quadruple) {
    std::vector<uint32> versionVector = Utils::versionToVector("1.2.3.4");

    ASSERT_EQ(versionVector.size(), 4);
    EXPECT_EQ(versionVector[0], 1);
    EXPECT_EQ(versionVector[1], 2);
    EXPECT_EQ(versionVector[2], 3);
    EXPECT_EQ(versionVector[3], 4);
  }

  TEST(UtilsVersionToVector, QuadrupleMinimum) {
    std::vector<uint32> versionVector = Utils::versionToVector("0.0.0.0");

    ASSERT_EQ(versionVector.size(), 4);
    EXPECT_EQ(versionVector[0], 0);
    EXPECT_EQ(versionVector[1], 0);
    EXPECT_EQ(versionVector[2], 0);
    EXPECT_EQ(versionVector[3], 0);
  }

  TEST(UtilsVersionToVector, QuadrupleMaximum) {
    std::vector<uint32> versionVector = Utils::versionToVector(
      "4294967295.4294967295.4294967295.4294967295"
    );

    ASSERT_EQ(versionVector.size(), 4);
    EXPECT_EQ(versionVector[0], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[1], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[2], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[3], 0xFFFFFFFF);
  }

  TEST(UtilsVersionToVector, Quintuple) {
    std::vector<uint32> versionVector = Utils::versionToVector("1.2.3.4.5");

    ASSERT_EQ(versionVector.size(), 5);
    EXPECT_EQ(versionVector[0], 1);
    EXPECT_EQ(versionVector[1], 2);
    EXPECT_EQ(versionVector[2], 3);
    EXPECT_EQ(versionVector[3], 4);
    EXPECT_EQ(versionVector[4], 5);
  }

  TEST(UtilsVersionToVector, QuintupleMinimum) {
    std::vector<uint32> versionVector = Utils::versionToVector("0.0.0.0.0");

    ASSERT_EQ(versionVector.size(), 5);
    EXPECT_EQ(versionVector[0], 0);
    EXPECT_EQ(versionVector[1], 0);
    EXPECT_EQ(versionVector[2], 0);
    EXPECT_EQ(versionVector[3], 0);
    EXPECT_EQ(versionVector[4], 0);
  }

  TEST(UtilsVersionToVector, QuintupleMaximum) {
    std::vector<uint32> versionVector = Utils::versionToVector(
      "4294967295.4294967295.4294967295.4294967295.4294967295"
    );

    ASSERT_EQ(versionVector.size(), 5);
    EXPECT_EQ(versionVector[0], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[1], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[2], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[3], 0xFFFFFFFF);
    EXPECT_EQ(versionVector[4], 0xFFFFFFFF);
  }

  TEST(UtilsWorkingDirResolveTest, NotEmpty) {
    String path = Utils::workingDirResolve();

    EXPECT_FALSE(path.empty());
  }
}

#endif
