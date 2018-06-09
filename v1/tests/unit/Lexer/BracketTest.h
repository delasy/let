/**
 * @created_at: 2019-07-06 12:36:46
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

#ifndef TESTS_LEXER_BRACKETTEST_H
#define TESTS_LEXER_BRACKETTEST_H

#include "../../../src/Lexer/Bracket.h"

namespace let {
  TEST(LexerBracketTest, LeftBrace) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('{'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_LBRACE);
    EXPECT_EQ(lexer.rawValue, "{");
    EXPECT_EQ(lexer.value, "{");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, RightBrace) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('}'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_RBRACE);
    EXPECT_EQ(lexer.rawValue, "}");
    EXPECT_EQ(lexer.value, "}");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, LeftParenthesis) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('('));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_LPAR);
    EXPECT_EQ(lexer.rawValue, "(");
    EXPECT_EQ(lexer.value, "(");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, RightParenthesis) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return(')'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_RPAR);
    EXPECT_EQ(lexer.rawValue, ")");
    EXPECT_EQ(lexer.value, ")");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, LeftBracket) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('['));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_LBRACK);
    EXPECT_EQ(lexer.rawValue, "[");
    EXPECT_EQ(lexer.value, "[");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, RightBracket) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return(']'));

    EXPECT_CALL(lexer, epilogue(testing::Ref(reader)))
      .WillOnce(
        testing::DoAll(
          testing::Assign(&lexer.locationRange.end.charIdx, 2),
          testing::Assign(&lexer.locationRange.end.lineNum, 2)
        )
      );

    ASSERT_TRUE(LexerBracket::is(&lexer, reader));
    EXPECT_EQ(lexer.token, LEXER_RBRACK);
    EXPECT_EQ(lexer.rawValue, "]");
    EXPECT_EQ(lexer.value, "]");
    EXPECT_EQ(lexer.locationRange.start.charIdx, 1);
    EXPECT_EQ(lexer.locationRange.start.lineNum, 1);
    EXPECT_EQ(lexer.locationRange.end.charIdx, 2);
    EXPECT_EQ(lexer.locationRange.end.lineNum, 2);
  }

  TEST(LexerBracketTest, Mismatch) {
    testing::StrictMock<LexerMock> lexer;
    testing::StrictMock<ReaderMock> reader;

    EXPECT_CALL(reader, nextToken())
      .WillOnce(testing::Return('\0'));

    EXPECT_CALL(reader, restoreCursor(READER_CURSOR_SECONDARY));

    ASSERT_FALSE(LexerBracket::is(&lexer, reader));
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
