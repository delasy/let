/**
 * @created_at: 2019-07-06 12:39:00
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

#ifndef TESTS_LEXER_LITERALSTRINGTEST_H
#define TESTS_LEXER_LITERALSTRINGTEST_H

#include "../../../src/Lexer/LiteralString.h"
#include "../../../src/ErrorException.h"

namespace let {
  TEST(LexerLiteralStringTest, DQEmpty) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(testing::Return('"'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 3),
          testing::Assign(&lexer.locationRange.end.lineNum, 3)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_DQ);
    EXPECT_EQ(lexer.rawValue, "\"\"");
    EXPECT_EQ(lexer.value, "");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 3);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 3);
  }

  TEST(LexerLiteralStringTest, SQEmpty) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(testing::Return('\''));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 3),
          testing::Assign(&lexer.locationRange.end.lineNum, 3)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_SQ);
    EXPECT_EQ(lexer.rawValue, "''");
    EXPECT_EQ(lexer.value, "");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 3);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 3);
  }

  TEST(LexerLiteralStringTest, DQOneLineOneChar) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('"'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 4),
          testing::Assign(&lexer.locationRange.end.lineNum, 4)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_DQ);
    EXPECT_EQ(lexer.rawValue, "\"a\"");
    EXPECT_EQ(lexer.value, "a");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 4);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 4);
  }

  TEST(LexerLiteralStringTest, SQOneLineOneChar) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('\''));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 4),
          testing::Assign(&lexer.locationRange.end.lineNum, 4)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_SQ);
    EXPECT_EQ(lexer.rawValue, "'a'");
    EXPECT_EQ(lexer.value, "a");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 4);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 4);
  }

  TEST(LexerLiteralStringTest, DQOneLineMultipleChars) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('"'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 7),
          testing::Assign(&lexer.locationRange.end.lineNum, 7)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_DQ);
    EXPECT_EQ(lexer.rawValue, "\"test\"");
    EXPECT_EQ(lexer.value, "test");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 7);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 7);
  }

  TEST(LexerLiteralStringTest, SQOneLineMultipleChars) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('\''));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 7),
          testing::Assign(&lexer.locationRange.end.lineNum, 7)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_SQ);
    EXPECT_EQ(lexer.rawValue, "'test'");
    EXPECT_EQ(lexer.value, "test");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 7);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 7);
  }

  TEST(LexerLiteralStringTest, DQMultipleLines) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('\n'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('"'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 8),
          testing::Assign(&lexer.locationRange.end.lineNum, 8)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_DQ);
    EXPECT_EQ(lexer.rawValue, "\"te\nst\"");
    EXPECT_EQ(lexer.value, "te\nst");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 8);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 8);
  }

  TEST(LexerLiteralStringTest, SQMultipleLines) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('\n'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('\''));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 8),
          testing::Assign(&lexer.locationRange.end.lineNum, 8)
        )
      );

    ASSERT_TRUE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_STRING_LITERAL_SQ);
    EXPECT_EQ(lexer.rawValue, "'te\nst'");
    EXPECT_EQ(lexer.value, "te\nst");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 8);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 8);
  }

  TEST(LexerLiteralStringTest, Mismatch) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerLiteralString::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerLiteralStringTest, ExceptionDQEndedWithSQ) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(testing::Return('\''))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('\0')
        )
      );

    EXPECT_THROW(LexerLiteralString::is(&lexer, reader), ErrorException);
  }

  TEST(LexerLiteralStringTest, ExceptionSQEndedWithDQ) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(testing::Return('"'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('\0')
        )
      );

    EXPECT_THROW(LexerLiteralString::is(&lexer, reader), ErrorException);
  }

  TEST(LexerLiteralStringTest, ExceptionDQNotEnded) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('"'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('\0')
        )
      );

    EXPECT_THROW(LexerLiteralString::is(&lexer, reader), ErrorException);
  }

  TEST(LexerLiteralStringTest, ExceptionSQNotEnded) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\''))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('\0')
        )
      );

    EXPECT_THROW(LexerLiteralString::is(&lexer, reader), ErrorException);
  }
}

#endif
