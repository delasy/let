#include <iostream>
#include "Codegen.hpp"
#include "Exception.hpp"
#include "Version.hpp"

int main(int argc, const char **argv) {
  try {
    if (argc == 1) {
      throw Exception("REPL is not implemented");
    }

    CodegenToken codegenToken = CODEGEN_UNKNOWN;
    bool runAfterCompile = false;
    std::filesystem::path outputPath = "./a.out";
    std::filesystem::path sourcePath;

    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];

      if (arg.substr(0, 9) == "--output=") {
        outputPath = arg.substr(9);
        continue;
      } else if (arg.substr(0, 5) == "--os=") {
        std::string OS = arg.substr(5);

        if (OS == "mac" || OS == "mac64") {
          codegenToken = CODEGEN_MAC64;
          continue;
        }
      } else if (arg == "-h" || arg == "--help") {
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
        std::cout << "    " "\x1B[1m" "--os=..." "\x1B[0m";
        std::cout << "          Set OS of output executable." << std::endl;
        std::cout << "                      Valid values: mac64 (alias mac).";
        std::cout << std::endl;
        std::cout << "                      Default value: mac64.";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "    " "\x1B[1m" "--output=..." "\x1B[0m";
        std::cout << "      Set name of output executable." << std::endl;
        std::cout << std::endl;
        std::cout << "    " "\x1B[1m" "-r," "\x1B[0m";
        std::cout << "               Run application after compilation.";
        std::cout << std::endl;
        std::cout << "    " "\x1B[1m" "--run" "\x1B[0m" << std::endl;
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
        std::cout << "\x1B[4m" "file.let" "\x1B[0m" << std::endl;;
        std::cout << std::endl;

        return EXIT_SUCCESS;
      } else if (arg == "-r" || arg == "--run") {
        runAfterCompile = true;
        continue;
      } else if (arg == "-v" || arg == "-V" || arg == "--version") {
        std::cout << std::endl;
        std::cout << "The Let Programming Language" << std::endl;
        std::cout << "Version " << Version::NUMBER;
        std::cout << " (" << Version::NAME << ")" << std::endl;
        std::cout << "Copyright (c) 2020  Aaron Delasy";
        std::cout << std::endl << std::endl;

        return EXIT_SUCCESS;
      }

      try {
        sourcePath = std::filesystem::canonical(arg);
      } catch (std::filesystem::filesystem_error &e) {
        try {
          sourcePath = std::filesystem::canonical(arg + ".let");
        } catch (std::filesystem::filesystem_error &e) {
          if (arg[0] == '-') {
            throw Exception("Invalid argument '" + arg + "'");
          } else {
            throw Exception("File or directory '" + arg + "' not found");
          }
        }
      }
    }

    if (codegenToken == CODEGEN_UNKNOWN) {
      #ifdef __APPLE__
        codegenToken = CODEGEN_MAC64;
      #endif
    }

    Reader reader(sourcePath);
    AST ast(reader);
    Binary binary = Codegen::init(codegenToken, ast);

    binary += Version::a16b8c8(Version::NUMBER);
    binary += Version::a24b10c10d10e10(Version::NUMBER);

    if (binary.empty()) {
      throw Exception("Unable to compile for selected operating system.");
    }

    binary.writeToFile(outputPath);

    std::filesystem::permissions(
      outputPath,
      std::filesystem::perms::owner_all |
        std::filesystem::perms::group_read |
        std::filesystem::perms::group_exec |
        std::filesystem::perms::others_read |
        std::filesystem::perms::others_exec
    );

    if (runAfterCompile) {
      std::string cmd = std::string(outputPath) + " 2>&1";

      std::unique_ptr<FILE, decltype(&pclose)> pipe(
        popen(cmd.c_str(), "r"),
        pclose
      );

      if (!pipe) {
        throw Exception("Failed to run program after compile");
      }

      char buffer[128];

      while (fgets(buffer, sizeof buffer, pipe.get()) != nullptr) {
        std::cout << buffer;
      }
    }
  } catch (Exception &e) {
    std::cerr << e.message << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
