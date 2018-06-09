/**
 * @created_at: 2019-07-06 12:39:19
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

#ifndef TESTS_LEXER_SIGNTEST_H
#define TESTS_LEXER_SIGNTEST_H

#include "../../../src/Lexer/Sign.h"

namespace let {
  TEST(LexerSignTest, Equal) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('='));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerSign::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_EQUAL);
    EXPECT_EQ(lexer.rawValue, "=");
    EXPECT_EQ(lexer.value, "=");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerSignTest, Minus) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('-'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerSign::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_MINUS);
    EXPECT_EQ(lexer.rawValue, "-");
    EXPECT_EQ(lexer.value, "-");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerSignTest, Plus) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('+'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerSign::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_PLUS);
    EXPECT_EQ(lexer.rawValue, "+");
    EXPECT_EQ(lexer.value, "+");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerSignTest, Tilde) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('~'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerSign::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_TILDE);
    EXPECT_EQ(lexer.rawValue, "~");
    EXPECT_EQ(lexer.value, "~");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerSignTest, Mismatch) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerSign::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }
}

#endif
