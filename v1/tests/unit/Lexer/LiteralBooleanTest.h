/**
 * @created_at: 2019-07-06 12:38:38
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

#ifndef TESTS_LEXER_LITERALBOOLEANTEST_H
#define TESTS_LEXER_LITERALBOOLEANTEST_H

#include "../../../src/Lexer/LiteralBoolean.h"

namespace let {
  TEST(LexerLiteralBooleanTest, False) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('f'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('l'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, prevToken());

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 6),
          testing::Assign(&lexer.locationRange.end.lineNum, 6)
        )
      );

    ASSERT_TRUE(LexerLiteralBoolean::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BOOLEAN_LITERAL);
    EXPECT_EQ(lexer.rawValue, "false");
    EXPECT_EQ(lexer.value, "false");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 6);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 6);
  }

  TEST(LexerLiteralBooleanTest, True) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('r'))
      .WillOnce(testing::Return('u'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, prevToken());

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 5),
          testing::Assign(&lexer.locationRange.end.lineNum, 5)
        )
      );

    ASSERT_TRUE(LexerLiteralBoolean::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BOOLEAN_LITERAL);
    EXPECT_EQ(lexer.rawValue, "true");
    EXPECT_EQ(lexer.value, "true");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 5);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 5);
  }

  TEST(LexerLiteralBooleanTest, MismatchFalse) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('f'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('l'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerLiteralBoolean::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerLiteralBooleanTest, MismatchTrue) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('r'))
      .WillOnce(testing::Return('u'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerLiteralBoolean::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerLiteralBooleanTest, MismatchFalseTrailingIdentifier) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('f'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('l'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('a'));

    EXPECT_CALL(reader, prevToken());
    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerLiteralBoolean::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerLiteralBooleanTest, MismatchTrueTrailingIdentifier) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('r'))
      .WillOnce(testing::Return('u'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('a'));

    EXPECT_CALL(reader, prevToken());
    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerLiteralBoolean::is(&lexer, reader));
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
