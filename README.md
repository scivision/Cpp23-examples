# C++20 and C++17 Examples

[![ci](https://github.com/scivision/cxx20-examples/actions/workflows/cmake.yml/badge.svg)](https://github.com/scivision/cxx20-examples/actions/workflows/cmake.yml)

Examples of C++17 and C++20 syntax, for testing of compilers and build systems.
While this repo focuses on CMake C++20 support, xmake also exists.

## C++20 modules

C++20 modules require recent C++ compilers such as:

* Visual Studio &ge; [16.8](https://devblogs.microsoft.com/cppblog/standard-c20-modules-support-with-msvc-in-visual-studio-2019-version-16-8/) with C++ module option installed.

CMake &ge; 3.25 continue to upgrade support for C++20 modules.
At this time, Visual Studio works best with C++ modules, but additional compiler support (e.g. GCC, Clang) is emerging.

A fully working
[ball pit simulation](https://github.com/cdacamar/ball_pit)
shows more advanced use of C++20 modules.
