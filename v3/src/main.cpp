#include <iostream>
#include "Error.hpp"
#include "Lexer.hpp"
#include "Version.hpp"

int help() {
  std::cout << std::endl;
  std::cout << "  " "\x1B[1m" "Usage:" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "    " "\x1B[1m" "let" "\x1B[0m" " [options] ";
  std::cout << "\x1B[4m" "file" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "  " "\x1B[1m" "Options:" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "    " "\x1B[1m" "-h," "\x1B[0m";
  std::cout << "               Print help information." << std::endl;
  std::cout << "    " "\x1B[1m" "-help" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "    " "\x1B[1m" "-v," "\x1B[0m";
  std::cout << "               Print version." << std::endl;
  std::cout << "    " "\x1B[1m" "-V," "\x1B[0m" << std::endl;
  std::cout << "    " "\x1B[1m" "--version" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "  " "\x1B[1m" "Examples:" "\x1B[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "    " "\x1B[1m" "$" "\x1B[0m" " let ";
  std::cout << "\x1B[4m" "file" "\x1B[0m" << std::endl;
  std::cout << "    " "\x1B[1m" "$" "\x1B[0m" " let ";
  std::cout << "\x1B[4m" "file.let" "\x1B[0m" << std::endl;
  std::cout << std::endl;

  return EXIT_SUCCESS;
}

int version() {
  std::cout << std::endl;
  std::cout << "The Let Programming Language" << std::endl;
  std::cout << "Version " << Version::NUMBER << " (" << Version::NAME << ")";
  std::cout << std::endl;
  std::cout << "Copyright (c) 2020  Aaron Delasy";
  std::cout << std::endl << std::endl;

  return EXIT_SUCCESS;
}

int main(int argc, const char **argv) {
  try {
    if (argc == 1) {
      throw Error("REPL is not implemented");
    }

    std::filesystem::path sourcePath;

    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];

      if (arg == "-h" || arg == "--help") {
        return help();
      } else if (arg == "-v" || arg == "-V" || arg == "--version") {
        return version();
      }

      try {
        sourcePath = std::filesystem::canonical(arg);
      } catch (std::filesystem::filesystem_error &err) {
        try {
          sourcePath = std::filesystem::canonical(arg + ".let");
        } catch (std::filesystem::filesystem_error &err) {
          if (arg[0] == '-') {
            throw Error("Invalid argument '" + arg + "'");
          } else {
            throw Error("File '" + arg + "' not found");
          }
        }
      }
    }

    if (sourcePath.empty()) {
      throw Error("File is not specified");
    }

    Reader reader(sourcePath);

    while (!reader.isEOF()) {
      Lexer lexer(reader);

      if (lexer.isSkippable()) {
        continue;
      }

      std::cout << lexer.token << " " << lexer.rawValue << std::endl;
    }
  } catch (Error &err) {
    std::cerr << err.message << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
