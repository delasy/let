cmake_minimum_required(VERSION 3.0)

file(STRINGS src/Version.cpp VERSION_STRING LIMIT_COUNT 1 REGEX "^const std::string Version::NUMBER = ")

if(VERSION_STRING MATCHES "\"([0-9]+)\\.([0-9]+)\\.([0-9]+)\"")
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH ${CMAKE_MATCH_3})
elseif(VERSION_STRING MATCHES "\"([0-9]+)\\.([0-9]+)\"")
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH "0")
else()
    message(FATAL_ERROR "Couldn't parse version from src/Version.cpp")
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

add_compiler_argument("-Wall")
add_compiler_argument("-Wextra")
add_compiler_argument("-std=c++17")

set(
    SRC_FILES

    src/AST.cpp src/AST.hpp
    src/Binary.cpp src/Binary.hpp
    src/Codegen.cpp src/Codegen.hpp
    src/CodegenMac64.cpp src/CodegenMac64.hpp
    src/Exception.cpp src/Exception.hpp
    src/Lexer.cpp src/Lexer.hpp
    src/Parser.cpp src/Parser.hpp
    src/Reader.cpp src/Reader.hpp
    src/VariableMap.cpp src/VariableMap.hpp
    src/Version.cpp src/Version.hpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES} src/main.cpp)
