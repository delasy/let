# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com), and this project adheres to [Semantic Versioning](https://semver.org).

## [Unreleased]

## [0.1.0](https://github.com/delasy/let/releases/tag/v0.1.0) - 2019-06-18

### Added

#### Syntax
- [LET-6](https://github.com/delasy/let/issues/6): Assignment

   ```let
   PascalCase = 0
   kebabCase = 1
   MACRO_CASE = 'string'
   snake_case = "string"

   var = 1
   ref = var
   refOfRef = ref
   ```

- [LET-6](https://github.com/delasy/let/issues/6): Strings

   ```let
   a = 'Single-quoted string'
   b = "Double quoted string"

   c = 'Single-quoted
   multiline string'

   d = "Double-quoted
   multiline string"
   ```

- [LET-6](https://github.com/delasy/let/issues/6): Numbers

   ```let
   a = 0
   b = 1
   c = 100
   d = 9223372036854775807
   ```

- [LET-6](https://github.com/delasy/let/issues/6): Comments

   ```let
   // Line comment
   /* Block comment */
   ```

- [LET-6](https://github.com/delasy/let/issues/6): Function call

   ```let
   sum = 1

   print(1, 2, sum, 'string', "string")
   ```

- [LET-6](https://github.com/delasy/let/issues/6): Print functions

   ```let
   print('Hello,', 'World!')
   puts('Hello,', 'World!')
   ```

#### Core
- [LET-26](https://github.com/delasy/let/issues/26): Distribution functionality (MacOS, Linux, Source code)
- [LET-23](https://github.com/delasy/let/issues/23): Support for MacOS, Linux
- [LET-20](https://github.com/delasy/let/issues/20): Help, OS, output, version options
- [LET-9](https://github.com/delasy/let/issues/9): Apache-2.0 License
- [LET-5](https://github.com/delasy/let/issues/5): Codegen functionality
- [LET-5](https://github.com/delasy/let/issues/5): Variable Map functionality
- [LET-3](https://github.com/delasy/let/issues/3): Abstract Syntax Tree functionality
- [LET-2](https://github.com/delasy/let/issues/2): Parser functionality
- [LET-1](https://github.com/delasy/let/issues/1): Lexer functionality
- [LET-1](https://github.com/delasy/let/issues/1): Reader functionality
