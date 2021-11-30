# C++20 and C++17 Examples

[![ci](https://github.com/scivision/cxx20-examples/actions/workflows/ci.yml/badge.svg)](https://github.com/scivision/cxx20-examples/actions/workflows/ci.yml)

Examples of C++17 filesystem and C++20 modules syntax, for testing of compilers and build systems.

## C++20 modules

C++20 modules require recent C++ compilers such as:

* Visual Studio [16.8](https://devblogs.microsoft.com/cppblog/standard-c20-modules-support-with-msvc-in-visual-studio-2019-version-16-8/)

CMake &ge; 3.21 supports C++20 modules.

NOTE: At this time, C++20 modules and CMake only work with Visual Studio compiler AND Visual Studio generator. For example:

```sh
cmake -B build -G "Visual Studio 16 2019"
```

This might be a CMake / compiler / build system (make/ninja) limitation.

A fully working
[ball pit simulation](https://github.com/cdacamar/ball_pit)
shows more advanced use of C++20 modules.
