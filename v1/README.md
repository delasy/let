[![Build status](https://img.shields.io/travis/com/delasy/let.svg?style=for-the-badge)](https://travis-ci.com/delasy/let)
[![Forks](https://img.shields.io/github/forks/delasy/let.svg?color=EA80FC&style=for-the-badge)](https://github.com/delasy/let/network/members)
[![Issues](https://img.shields.io/github/issues/delasy/let.svg?color=6600ED&style=for-the-badge)](https://github.com/delasy/let/issues)
[![License](https://img.shields.io/github/license/delasy/let.svg?color=EA80FC&style=for-the-badge)](LICENSE)
[![Stars](https://img.shields.io/github/stars/delasy/let.svg?color=6600ED&style=for-the-badge&)](https://github.com/delasy/let/stargazers)

# The Let Programming Language
This is the official repository of The Let Programming Language source code.

Let is a rapid, minimalistic, perfectionistic, elegant, high-performance, high-level programming language.

- **Unique:** The syntax for Let was produced by a combination of best features of all known programming languages in the world
- **Fast:** Let is so fast that comparable with writing code directly in machine code
- **Helpful:** Let takes care of everything, for you so that you can focus on writing code
- **Independent:** To compile your code Let is not using any dependencies
- **Portable:** Let works on a large number of operating systems
- **Shareable:** Multiple versions of Let can be installed on the same operating system

## General information
- Website: https://let-lang.org
- Source code: https://github.com/delasy/let
- Bugs & Issues tracker: https://github.com/delasy/let/issues
- Git clone URL: `git clone git@github.com:delasy/let.git`

## Examples
We have several examples [on the website](https://let-lang.org/examples). Here is the first one to get you started:

```let
import Window

window = new Window(
  name: 'Let',
  size: [800, 600],
  position: [0, 0]
)

textNode = new Window.Text(
  'Hello, World!'
)

window.append(textNode)
window.open()
```

This example will create a window of 800x600 size and render "Hello, World!" text into it.

## Installation
To run Let from source, clone this repository to your machine and compile it:

```bash
$ git clone git@github.com:delasy/let.git
$ cd let
$ scripts/init.sh
$ scripts/build.sh
```

## Uninstallation
Let doesn't install anything outside the directory it was cloned into. It can be completely uninstalled by deleting this directory. \
Packages are installed in `~/.let` by default and can be uninstalled by deleting `~/.let`.

## Coding with Let
Currently editing mode support is not available for any editor. \
Expected plugins for Atom, Atom IDE, Sublime Text, VS Code, JetBrains IDEs, Emacs, Vim.

## Supported Operating Systems
Since the compiler is written in Let, it must be built by a precompiled previous version of itself. \
Let is built and tested on the following operating systems:

| Operating System | Version  | Architecture     | Support       |
|:---------------- |:--------:|:----------------:|:-------------:|
| MacOS            | 10.14    | x86-64 (64-bit)  | Official      |
|                  | 10.13    | x86-64 (64-bit)  | Official      |
|                  | 10.12    | x86-64 (64-bit)  | Official      |
|                  | 10.11    | x86-64 (64-bit)  | Official      |
|                  | 10.10    | x86-64 (64-bit)  | Official      |
| Linux            | 4.15     | x86_64 (64-bit)  | Official      |
|                  | 4.4      | x86_64 (64-bit)  | Official      |
|                  | 3.13     | x86_64 (64-bit)  | Official      |
| Windows          | -        | -                | Not supported |

You may find that other operating systems work too, but they are not officially supported.

## How to contribute
To contribute, please send us a [pull request](https://github.com/delasy/let/compare) from your fork of this repository. \
New developers may find notes in [CONTRIBUTING.md](CONTRIBUTING.md) file helpful to start contributing.

## Testing
To run Let tests, clone this repository to your machine, compile it and execute test script:

```bash
$ git clone git@github.com:delasy/let.git
$ cd let
$ scripts/init.sh
$ scripts/test.sh unit
```

### Running specific tests

```bash
$ scripts/test.sh unit --filter=*
$ scripts/test.sh unit --filter=FooTest.*
$ scripts/test.sh unit --filter=*Test.*
$ scripts/test.sh unit --filter=FooTest.*-FooTest.Bar
```

## Bug reports
For reporting bugs, visit [bugs & issues tracker](https://github.com/delasy/let/issues) and follow the steps for reporting a new issue. \
Please disclose security vulnerabilities privately at `security at let-lang dot org`.

## Proposing new features
If you have a proposal, you may want to open [a feature request](https://github.com/delasy/let/issues/new?template=FEATURE_REQUEST.md) (remember to follow our [Code of Conduct](CODE_OF_CONDUCT.md)).

Features and bug fixes that have already been merged and will be included in the next release are marked as "closed" in the [bugs & issues tracker](https://github.com/delasy/let/issues) and are added to the [CHANGELOG.md](CHANGELOG.md).

## The Author
Let was designed and developed by [Aaron Delasy](https://github.com/delasy). \
`aaron at delasy dot com`

## License
Let is distributed under the terms of Apache License (Version 2.0). \
See [LICENSE](LICENSE) for details.
