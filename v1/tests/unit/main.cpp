/**
 * @created_at: 2019-06-20 13:28:49
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LexerMock.h"
#include "ReaderMock.h"

#include "ASTTest.h"
#include "ArgumentsTest.h"
#include "BinaryTest.h"
#include "CodegenTest.h"
#include "Codegen/Mac64Test.h"
#include "Codegen/Mac64CommandTest.h"
#include "Codegen/Mac64CommandDyLdInfoTest.h"
#include "Codegen/Mac64CommandDyLibTest.h"
#include "Codegen/Mac64CommandDyLinkerTest.h"
#include "Codegen/Mac64CommandDySymTabTest.h"
#include "Codegen/Mac64CommandEntryPointTest.h"
#include "Codegen/Mac64CommandLinkEditTest.h"
#include "Codegen/Mac64CommandSegmentTest.h"
#include "Codegen/Mac64CommandSourceVersionTest.h"
#include "Codegen/Mac64CommandSymTabTest.h"
#include "Codegen/Mac64CommandVersionMinTest.h"
#include "Codegen/Mac64DyLibTest.h"
#include "Codegen/Mac64HeaderTest.h"
#include "Codegen/Mac64SectionTest.h"
#include "Codegen/Mac64StringTest.h"
#include "ConsoleTest.h"
#include "ErrorTest.h"
#include "ErrorExceptionTest.h"
#include "LexerTest.h"
#include "Lexer/BracketTest.h"
#include "Lexer/CommentBlockTest.h"
#include "Lexer/CommentLineTest.h"
#include "Lexer/IdentifierTest.h"
#include "Lexer/KeywordReturnTest.h"
#include "Lexer/LiteralBooleanTest.h"
#include "Lexer/LiteralNilTest.h"
#include "Lexer/LiteralNumberTest.h"
#include "Lexer/LiteralStringTest.h"
#include "Lexer/MarkTest.h"
#include "Lexer/SignTest.h"
#include "Lexer/WhitespaceTest.h"
#include "ParserTest.h"
#include "Parser/BaseTest.h"
#include "Parser/ArgListTest.h"
#include "Parser/AssignExprTest.h"
#include "Parser/CallExprTest.h"
#include "Parser/ExprTest.h"
#include "Parser/IdTest.h"
#include "Parser/LiteralTest.h"
#include "Parser/SkippableTest.h"
#include "ReaderTest.h"
#include "Reader/CursorTest.h"
#include "Reader/LocationTest.h"
#include "Reader/LocationRangeTest.h"
#include "UtilsTest.h"
#include "VariableMapTest.h"
#include "VariableMap/ItemTest.h"
