# C++20 and C++17 Examples

Examples of C++17 and C++20 syntax, for testing of compilers and build system

## Modules

C++20 modules require the latest C++ compilers, at least:

* GCC 10 (has to have been compiled with Modules support--probably have to compile GCC yourself)
* Clang 8

### Clang

This works with Clang 8.

[Clang](https://stackoverflow.com/a/49322001):

With Clang 9, the `-fmodules-ts` is not used.
Clang 8 does need `-fmodules-ts`.

```sh
# creates math.pcm
clang++ -std=c++2a -fmodules-ts --precompile math.cppm

# creates math.o
clang++ -std=c++2a -fmodules-ts -c  math.pcm

# creates a.exe or a.out
clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. math.o math.cpp
```

## C++17 filesystem

C++17 filesystem requires recent compiler, at least:

* Visual Studio 16.8.5
