cmake_minimum_required(VERSION 3.0)

file(
    STRINGS src/version.h VERSION_STRING
    LIMIT_COUNT 1
    REGEX "^#define VERSION "
)

if(VERSION_STRING MATCHES "\"([0-9]+)\\.([0-9]+)\\.([0-9]+)\"")
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH ${CMAKE_MATCH_3})
elseif(VERSION_STRING MATCHES "\"([0-9]+)\\.([0-9]+)\"")
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH "0")
else()
    message(FATAL_ERROR "Couldn't parse version from src/version.h")
endif()

if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)

    if(VERSION_PATCH STREQUAL "0")
        project(let VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
    else()
        project(let VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
    endif()
else()
    project(let)

    set(PROJECT_VERSION_MAJOR ${VERSION_MAJOR})
    set(PROJECT_VERSION_MINOR ${VERSION_MINOR})
    set(PROJECT_VERSION_PATCH ${VERSION_PATCH})
endif()

function(add_compiler_argument ARGUMENT)
    if(CMAKE_CXX_FLAGS AND NOT CMAKE_CXX_FLAGS STREQUAL "")
        set(FLAGS "${CMAKE_CXX_FLAGS} ")
    else()
        set(FLAGS "")
    endif()

    string(FIND "${FLAGS}" "${ARGUMENT}" MATCH_RESULT)

    if(${MATCH_RESULT} EQUAL -1)
        set(CMAKE_CXX_FLAGS "${FLAGS}${ARGUMENT}" CACHE STRING "" FORCE)
    endif()
endfunction()

add_compiler_argument("-std=c++11")
add_compiler_argument("-Wall")

set(
    SRC_FILES

    src/Codegen/Mac64.cpp
    src/Codegen/Mac64.h
    src/Codegen/Mac64Command.cpp
    src/Codegen/Mac64Command.h
    src/Codegen/Mac64CommandDyLdInfo.cpp
    src/Codegen/Mac64CommandDyLdInfo.h
    src/Codegen/Mac64CommandDyLib.cpp
    src/Codegen/Mac64CommandDyLib.h
    src/Codegen/Mac64CommandDyLinker.cpp
    src/Codegen/Mac64CommandDyLinker.h
    src/Codegen/Mac64CommandDySymTab.cpp
    src/Codegen/Mac64CommandDySymTab.h
    src/Codegen/Mac64CommandEntryPoint.cpp
    src/Codegen/Mac64CommandEntryPoint.h
    src/Codegen/Mac64CommandLinkEdit.cpp
    src/Codegen/Mac64CommandLinkEdit.h
    src/Codegen/Mac64CommandSegment.cpp
    src/Codegen/Mac64CommandSegment.h
    src/Codegen/Mac64CommandSourceVersion.cpp
    src/Codegen/Mac64CommandSourceVersion.h
    src/Codegen/Mac64CommandSymTab.cpp
    src/Codegen/Mac64CommandSymTab.h
    src/Codegen/Mac64CommandVersionMin.cpp
    src/Codegen/Mac64CommandVersionMin.h
    src/Codegen/Mac64DyLib.cpp
    src/Codegen/Mac64DyLib.h
    src/Codegen/Mac64Header.cpp
    src/Codegen/Mac64Header.h
    src/Codegen/Mac64Section.cpp
    src/Codegen/Mac64Section.h
    src/Codegen/Mac64String.cpp
    src/Codegen/Mac64String.h
    src/Lexer/Bracket.cpp
    src/Lexer/Bracket.h
    src/Lexer/CommentBlock.cpp
    src/Lexer/CommentBlock.h
    src/Lexer/CommentLine.cpp
    src/Lexer/CommentLine.h
    src/Lexer/Identifier.cpp
    src/Lexer/Identifier.h
    src/Lexer/KeywordReturn.cpp
    src/Lexer/KeywordReturn.h
    src/Lexer/LiteralNil.cpp
    src/Lexer/LiteralNil.h
    src/Lexer/LiteralBoolean.cpp
    src/Lexer/LiteralBoolean.h
    src/Lexer/LiteralNumber.cpp
    src/Lexer/LiteralNumber.h
    src/Lexer/LiteralString.cpp
    src/Lexer/LiteralString.h
    src/Lexer/Mark.cpp
    src/Lexer/Mark.h
    src/Lexer/Sign.cpp
    src/Lexer/Sign.h
    src/Lexer/Whitespace.cpp
    src/Lexer/Whitespace.h
    src/Parser/ArgList.cpp
    src/Parser/ArgList.h
    src/Parser/AssignExpr.cpp
    src/Parser/AssignExpr.h
    src/Parser/Base.cpp
    src/Parser/Base.h
    src/Parser/CallExpr.cpp
    src/Parser/CallExpr.h
    src/Parser/Expr.cpp
    src/Parser/Expr.h
    src/Parser/Id.cpp
    src/Parser/Id.h
    src/Parser/Literal.cpp
    src/Parser/Literal.h
    src/Parser/Skippable.cpp
    src/Parser/Skippable.h
    src/Reader/Cursor.cpp
    src/Reader/Cursor.h
    src/Reader/Location.cpp
    src/Reader/Location.h
    src/Reader/LocationRange.cpp
    src/Reader/LocationRange.h
    src/VariableMap/Item.cpp
    src/VariableMap/Item.h
    src/AST.cpp
    src/AST.h
    src/Arguments.cpp
    src/Arguments.h
    src/Binary.cpp
    src/Binary.h
    src/Codegen.cpp
    src/Codegen.h
    src/Console.cpp
    src/Console.h
    src/Error.cpp
    src/Error.h
    src/ErrorException.cpp
    src/ErrorException.h
    src/Lexer.cpp
    src/Lexer.h
    src/Parser.cpp
    src/Parser.h
    src/Reader.cpp
    src/Reader.h
    src/Utils.cpp
    src/Utils.h
    src/VariableMap.cpp
    src/VariableMap.h

    src/types.h
    src/version.h
)

add_executable(${PROJECT_NAME} ${SRC_FILES} src/main.cpp)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GTestDownload.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/gtest-download/CMakeLists.txt"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/gtest-download"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest-download
)

add_subdirectory(
    "${CMAKE_CURRENT_BINARY_DIR}/gtest"
    "${CMAKE_CURRENT_BINARY_DIR}/gtest-build"
    EXCLUDE_FROM_ALL
)

set(
    TESTS_UNIT_FILES

    tests/unit/Codegen/Mac64CommandDyLdInfoTest.h
    tests/unit/Codegen/Mac64CommandDyLibTest.h
    tests/unit/Codegen/Mac64CommandDyLinkerTest.h
    tests/unit/Codegen/Mac64CommandDySymTabTest.h
    tests/unit/Codegen/Mac64CommandEntryPointTest.h
    tests/unit/Codegen/Mac64CommandLinkEditTest.h
    tests/unit/Codegen/Mac64CommandSegmentTest.h
    tests/unit/Codegen/Mac64CommandSourceVersionTest.h
    tests/unit/Codegen/Mac64CommandSymTabTest.h
    tests/unit/Codegen/Mac64CommandTest.h
    tests/unit/Codegen/Mac64CommandVersionMinTest.h
    tests/unit/Codegen/Mac64DyLibTest.h
    tests/unit/Codegen/Mac64HeaderTest.h
    tests/unit/Codegen/Mac64SectionTest.h
    tests/unit/Codegen/Mac64StringTest.h
    tests/unit/Codegen/Mac64Test.h
    tests/unit/Lexer/BracketTest.h
    tests/unit/Lexer/CommentBlockTest.h
    tests/unit/Lexer/CommentLineTest.h
    tests/unit/Lexer/IdentifierTest.h
    tests/unit/Lexer/KeywordReturnTest.h
    tests/unit/Lexer/LiteralBooleanTest.h
    tests/unit/Lexer/LiteralNilTest.h
    tests/unit/Lexer/LiteralNumberTest.h
    tests/unit/Lexer/LiteralStringTest.h
    tests/unit/Lexer/MarkTest.h
    tests/unit/Lexer/SignTest.h
    tests/unit/Lexer/WhitespaceTest.h
    tests/unit/Parser/ArgListTest.h
    tests/unit/Parser/AssignExprTest.h
    tests/unit/Parser/BaseTest.h
    tests/unit/Parser/CallExprTest.h
    tests/unit/Parser/ExprTest.h
    tests/unit/Parser/IdTest.h
    tests/unit/Parser/LiteralTest.h
    tests/unit/Parser/SkippableTest.h
    tests/unit/Reader/CursorTest.h
    tests/unit/Reader/LocationRangeTest.h
    tests/unit/Reader/LocationTest.h
    tests/unit/VariableMap/ItemTest.h
    tests/unit/ASTTest.h
    tests/unit/ArgumentsTest.h
    tests/unit/BinaryTest.h
    tests/unit/CodegenTest.h
    tests/unit/ConsoleTest.h
    tests/unit/ErrorExceptionTest.h
    tests/unit/ErrorTest.h
    tests/unit/LexerMock.h
    tests/unit/LexerTest.h
    tests/unit/ParserTest.h
    tests/unit/ReaderMock.h
    tests/unit/ReaderTest.h
    tests/unit/UtilsTest.h
    tests/unit/VariableMapTest.h
)

add_executable(
    ${PROJECT_NAME}_tests_unit
    ${SRC_FILES} ${TESTS_UNIT_FILES} tests/unit/main.cpp
)

target_link_libraries(${PROJECT_NAME}_tests_unit gmock_main)
