# C++20 and C++17 Examples

Examples of C++17 and C++20 syntax, for testing of compilers and build system

## Modules

C++20 modules require recent C++ compilers, at least:

* GCC 11
* Clang 9

CMake &ge; 3.21 supports C++20 modules.

### Clang

[Clang](https://stackoverflow.com/a/49322001):

```sh
# creates math.pcm
clang++ -std=c++2a --precompile math.cppm

# creates math.o
clang++ -std=c++2a -c math.pcm

# creates a.exe or a.out
clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. math.o math.cpp
```

## C++17 filesystem

C++17 filesystem requires recent compiler, at least:

* Visual Studio 16.8.5
