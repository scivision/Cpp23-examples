# C++20 and C++17 Examples

Examples of C++17 and C++20 syntax, for testing of compilers and build system

## Modules

In my experience, C++20 modules aren't working yet with CMake 3.15 and GCC 9, Clang 8 or Intel 19.0.

### Manual way

[Clang](https://stackoverflow.com/a/49322001):

With Clang 9, the `-fmodules-ts` is not used.
Clang 8 does need `-fmodules-ts`.

This works with Clang 8 on Linux and Windows at least

```sh
# creates math.pcm
clang++ -std=c++2a -fmodules-ts --precompile math.cppm

# creates math.o
clang++ -std=c++2a -fmodules-ts -c  math.pcm

# creates a.exe or a.out
clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. math.o math.cpp
```
