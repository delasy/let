/**
 * @created_at: 2019-07-06 12:37:02
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

#ifndef TESTS_LEXER_COMMENTBLOCKTEST_H
#define TESTS_LEXER_COMMENTBLOCKTEST_H

#include "../../../src/Lexer/CommentBlock.h"
#include "../../../src/ErrorException.h"

namespace let {
  TEST(LexerCommentBlockTest, Empty) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('/'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 5),
          testing::Assign(&lexer.locationRange.end.lineNum, 5)
        )
      );

    ASSERT_TRUE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BLOCK_COMMENT);
    EXPECT_EQ(lexer.rawValue, "/**/");
    EXPECT_EQ(lexer.value, "");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 5);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 5);
  }

  TEST(LexerCommentBlockTest, OneLineOneChar) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('/'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 6),
          testing::Assign(&lexer.locationRange.end.lineNum, 6)
        )
      );

    ASSERT_TRUE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BLOCK_COMMENT);
    EXPECT_EQ(lexer.rawValue, "/*t*/");
    EXPECT_EQ(lexer.value, "t");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 6);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 6);
  }

  TEST(LexerCommentBlockTest, OneLineMultipleChars) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('/'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 9),
          testing::Assign(&lexer.locationRange.end.lineNum, 9)
        )
      );

    ASSERT_TRUE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BLOCK_COMMENT);
    EXPECT_EQ(lexer.rawValue, "/*test*/");
    EXPECT_EQ(lexer.value, "test");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 9);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 9);
  }

  TEST(LexerCommentBlockTest, MultipleLines) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('\n'))
      .WillOnce(testing::Return('s'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('/'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 10),
          testing::Assign(&lexer.locationRange.end.lineNum, 10)
        )
      );

    ASSERT_TRUE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_BLOCK_COMMENT);
    EXPECT_EQ(lexer.rawValue, "/*te\nst*/");
    EXPECT_EQ(lexer.value, "te\nst");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 10);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 10);
  }

  TEST(LexerCommentBlockTest, MismatchStartSingle) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerCommentBlockTest, MismatchStartDouble) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerCommentBlock::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_UNKNOWN);
    EXPECT_TRUE(lexer.rawValue.empty());
    EXPECT_TRUE(lexer.value.empty());
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 1);
  }

  TEST(LexerCommentBlockTest, ExceptionEOFAfterOpened) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('*')
        )
      );

    ASSERT_THROW(LexerCommentBlock::is(&lexer, reader), ErrorException);
  }

  TEST(LexerCommentBlockTest, ExceptionEOFAfterFirstChar) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('t')
        )
      );

    ASSERT_THROW(LexerCommentBlock::is(&lexer, reader), ErrorException);
  }

  TEST(LexerCommentBlockTest, ExceptionEOFInMiddle) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('/'))
      .WillOnce(testing::Return('*'))
      .WillOnce(testing::Return('t'))
      .WillOnce(testing::Return('e'))
      .WillOnce(testing::Return('s'))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&reader.cursor3.isEOF, true),
          testing::Return('t')
        )
      );

    ASSERT_THROW(LexerCommentBlock::is(&lexer, reader), ErrorException);
  }
}

#endif
