/**
 * @created_at: 2019-07-06 12:37:32
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

#ifndef TESTS_LEXER_IDENTIFIERTEST_H
#define TESTS_LEXER_IDENTIFIERTEST_H

#include "../../../src/Lexer/Identifier.h"

namespace let {
  TEST(LexerIdentifierTest, Single) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, prevToken());

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerIdentifier::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_ID);
    EXPECT_EQ(lexer.rawValue, "a");
    EXPECT_EQ(lexer.value, "a");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerIdentifierTest, SingleWithEOF) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('a')
        )
      );

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerIdentifier::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_ID);
    EXPECT_EQ(lexer.rawValue, "a");
    EXPECT_EQ(lexer.value, "a");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerIdentifierTest, Multiple) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('$'))
      .WillOnce(testing::Return('v'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('r'))
      .WillOnce(testing::Return('_'))
      .WillOnce(testing::Return('0'))
      .WillOnce(testing::Return('1'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, prevToken());

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 9),
          testing::Assign(&lexer.locationRange.end.lineNum, 9)
        )
      );

    ASSERT_TRUE(LexerIdentifier::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_ID);
    EXPECT_EQ(lexer.rawValue, "$var_01");
    EXPECT_EQ(lexer.value, "$var_01");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 9);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 9);
  }

  TEST(LexerIdentifierTest, MultipleWithEOF) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('$'))
      .WillOnce(testing::Return('v'))
      .WillOnce(testing::Return('a'))
      .WillOnce(testing::Return('r'))
      .WillOnce(testing::Return('_'))
      .WillOnce(testing::Return('0'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('1')
        )
      );

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 9),
          testing::Assign(&lexer.locationRange.end.lineNum, 9)
        )
      );

    ASSERT_TRUE(LexerIdentifier::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_ID);
    EXPECT_EQ(lexer.rawValue, "$var_01");
    EXPECT_EQ(lexer.value, "$var_01");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 9);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 9);
  }

  TEST(LexerIdentifierTest, Mismatch) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerIdentifier::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerIdentifierTest, MismatchLeadingNumber) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('1'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerIdentifier::is(&lexer, reader));
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
