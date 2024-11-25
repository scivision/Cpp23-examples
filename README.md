# C++23 and C++20 Examples

[![ci](https://github.com/scivision/Cpp23-examples/actions/workflows/cmake.yml/badge.svg)](https://github.com/scivision/Cpp23-examples/actions/workflows/cmake.yml)

Examples of using CMake with
[C++26](https://en.cppreference.com/w/cpp/26),
C++23, and C++20 standard syntax.
This is useful for testing of compilers and build systems--already several bugs have been so detected.

We typically use
[feature testing macros](https://en.cppreference.com/w/cpp/feature_test)
to detect a feature, but some features require a small compile and link test.

## C++ execution policy

The
[execution_policy.cpp](./cpp20/execution_policy.cpp)
example shows how to use the C++20 execution policy feature.
Many platforms don't yet implemenet this feature.
Performance seen with NVHPC 24.11:

```
Serial    Time: 0.0605221 ms
Parallel  Time: 0.023676 ms
Par_Unseq Time: 0.00729935 ms
Unseq     Time: 0.0599898 ms
```

## Related projects

* [C23 examples](https://github.com/scivision/C23-examples)
* [C++17 filesystem application](https://github.com/scivision/fortran-filesystem)
* [C++ modules](https://github.com/scivision/CppModules)

## References

* [Each new C++20 feature with example in one page](https://oleksandrkvl.github.io/2021/04/02/cpp-20-overview.html)
