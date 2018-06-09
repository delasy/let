/**
 * @created_at: 2019-06-19 22:55:15
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

#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <sys/stat.h>
#include <exception>
#include <fstream>
#include <string>

#define OS_FAMILY_LINUX 1u
#define OS_FAMILY_MACOS 2u

#if defined(__linux__)
  #define OS_FAMILY OS_FAMILY_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
  #define OS_FAMILY OS_FAMILY_MACOS
#else
  #include "error/fatal.h";
#endif

typedef std::exception Exception;
typedef std::fstream File;
typedef std::string String;
typedef struct stat Stat;

#if OS_FAMILY == OS_FAMILY_LINUX || OS_FAMILY == OS_FAMILY_MACOS
  #define OS_EOL "\n"
#else
  #include "error/fatal.h";
#endif

typedef char int8;
typedef short int int16;
typedef int int32;
typedef long int48;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long uint48;
typedef unsigned long long uint64;

#endif
