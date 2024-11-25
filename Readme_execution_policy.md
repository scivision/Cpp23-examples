# Parallel STL std::execution policy

The
[execution_policy.cpp](./cpp20/execution_policy.cpp)
example shows how to use the C++20 execution policy feature.

* GCC requires TBB library (`dnf install tbb-devel` or `apt install libtbb-dev`)
* oneAPI uses oneTBB library

Performance seen with:

GCC 14.2 (Windows, TBB)

```
Method        Speed Ratio (vs. sequential)
Sequential     1.00
Parallel       2.90
Par_Unseq      3.05
Unseq          0.97
```

NVHPC 24.11 (-stdpar=multicore):

```
Method        Speed Ratio (vs. sequential)
Sequential     1.00
Parallel       3.69
Par_Unseq      8.43
Unseq          0.98
```

Linux oneAPI 2025.0 (TBB):

```
Method        Speed Ratio (vs. sequential)
Sequential     1.00
Parallel       8.43
Par_Unseq      29.50
Unseq          0.98
```

Windows oneAPI 2025.0 (TBB):

```
Method        Speed Ratio (vs. sequential)
Sequential     1.00
Parallel       3.19
Par_Unseq      3.00
Unseq          1.05
```
