# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com), and this project adheres to [Semantic Versioning](https://semver.org).

## [Unreleased]

## [0.1.1] - 2019-06-17

### Fixed
- Repository field in package.json

## [0.1.0] - 2019-06-17

### Added

#### Grammar
- Assignment

   ```let
   PascalCase = 0
   kebabCase = 1
   MACRO_CASE = 'string'
   snake_case = "string"

   var = 1
   ref = var
   refOfRef = ref
   ```

- Strings

   ```let
   a = 'Single-quoted string'
   b = "Double quoted string"
   c = 'Single-quoted
   multiline string'
   d = "Double-quoted
   multiline string"
   ```

- Numbers

   ```let
   a = 0
   b = 1
   c = 100
   d = 9223372036854775807
   ```

- Comments

   ```let
   // Line comment
   /* Block comment */
   ```

- Function call

   ```let
   sum = 1

   print(1, 2, sum, 'string', "string")
   ```

- Print functions

   ```let
   print('Hello,', 'World!\n')
   puts('Hello,', 'World!')
   ```

#### Snippets

- Notice block comment. Snippet `/*!` will expand to:

   ```let
   /*!
    * ${0}
    */
   ```

- Documentation block comment. Snippet `/**` will expand to:

   ```let
   /**
    * ${0}
    */
   ```

- Block comment. Snippet `/*` will expand to:

   ```let
   /* ${0} */
   ```

- Print built-in function. Snippet `print` will expand to:

   ```let
   print(${0})
   ```

- Puts built-in function. Snippet `puts` will expand to:

   ```let
   puts(${0})
   ```
