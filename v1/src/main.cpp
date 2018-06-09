/**
 * @created_at: 2018-05-08 09:55:02
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

#include <iostream>

#include "AST.h"
#include "Arguments.h"
#include "Codegen.h"
#include "Console.h"
#include "ErrorException.h"
#include "Reader.h"

#include "version.h"

namespace let {
  void printHelp() {
    std::cout << OS_EOL;
    std::cout << "  " << Console::BRIGHT << "Usage:" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "let" << Console::RESET;
    std::cout << " [options] ";
    std::cout << Console::UNDERSCORE << "file" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "  " << Console::BRIGHT << "Options:" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "-h," << Console::RESET;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "-help" << Console::RESET;
    std::cout << "             Print help information.";
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "--os=..." << Console::RESET;
    std::cout << "          Set OS of output executable.";
    std::cout << OS_EOL;
    std::cout << "                      Valid values: mac64 (or mac).";
    std::cout << OS_EOL;
    std::cout << "                      Default value: mac64.";
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "--output=..." << Console::RESET;
    std::cout << "      Set name of output executable.";
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "-v," << Console::RESET;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "-V," << Console::RESET;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "--version" << Console::RESET;
    std::cout << "         Print version.";
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "  " << Console::BRIGHT << "Examples:" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "$" << Console::RESET;
    std::cout << " let ";
    std::cout << Console::UNDERSCORE << "file" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << "    " << Console::BRIGHT << "$" << Console::RESET;
    std::cout << " let ";
    std::cout << Console::UNDERSCORE << "file.let" << Console::RESET;
    std::cout << OS_EOL;
    std::cout << OS_EOL;
  }

  void printVersion() {
    std::cout << "The Let Programming Language" << OS_EOL;
    std::cout << "Version " VERSION " (" VERSION_NAME ")" << OS_EOL;
    std::cout << "Copyright (c) 2018-2019  Aaron Delasy" << OS_EOL;
  }

  void processFile(Arguments &arguments) {
    Reader reader(arguments.sourcePath);
    AST ast(reader);
    Codegen codegen(arguments, ast);

    File file(arguments.outputPath, std::ios::out | std::ios::binary);

    file.write(
      reinterpret_cast<int8 *>(codegen.binary.getData()),
      codegen.binary.getSize()
    );

    file.close();
  }
}

int32 main(int32 argc, const int8 **argv) {
  let::Arguments arguments;

  try {
    arguments = let::Arguments(argc, argv);
  } catch (let::ErrorException& e) {
    std::cerr << e.what() << OS_EOL;

    return EXIT_FAILURE;
  }

  if (arguments.isHelp) {
    let::printHelp();
  } else if (arguments.isVersion) {
    let::printVersion();
  } else {
    try {
      let::processFile(arguments);
    } catch (let::ErrorException& e) {
      std::cerr << e.what() << OS_EOL;

      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
