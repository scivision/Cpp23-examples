set_property(DIRECTORY PROPERTY LABELS 20)

set(CMAKE_CXX_STANDARD 20)

# https://en.cppreference.com/w/cpp/header/version

check_cxx_symbol_exists(__cpp_impl_coroutine "version" cpp_impl_coroutine)
if(cpp_impl_coroutine)
  check_cxx_symbol_exists(__cpp_lib_coroutine "version" have_coroutine)
endif()

check_cxx_symbol_exists(__cpp_structured_bindings "" have_structured_bindings)

foreach(t IN ITEMS format int_pow2
  hardware_interference_size jthread ssize
  latch lerp math_constants midpoint
  semaphore source_location smart_ptr_for_overwrite)
  check_cxx_symbol_exists(__cpp_lib_${t} "version" have_${t})
endforeach()

if(have_int_pow2)
  file(READ bit_width.cpp _src)
  check_source_compiles(CXX "${_src}" have_bit_width)
endif()

check_include_file_cxx(syncstream have_syncstream)
# example requires jthread, syncstream, ssize
if(have_jthread AND have_syncstream AND have_ssize)
  check_cxx_symbol_exists(__cpp_lib_barrier "version" have_barrier)
endif()

set(have_stop_callback ${have_jthread})
set(have_stop_source ${have_jthread})

if(has_cpp_attribute)

check_source_compiles(CXX
"#if !__has_cpp_attribute(likely)
#error \"no likely attribute\"
#endif
int main(){ return 0; }"
have_likely
)

endif()

check_source_compiles(CXX
"#include <algorithm>
int main(){
    const int n = 3;
    const auto v = {4, 1, 3, 2};

    std::ranges::find(v, n);
    return 0;
}"
have_ranges_find
)

# C++17 execution policy with C++20 enhancements
check_include_file_cxx(execution have_execution_policy)
if(have_execution_policy)
  file(READ execution_policy.cpp _src)
  check_source_compiles(CXX "${_src}" execution_policy_parallel)
  if(NOT execution_policy_parallel)
    set_property(CACHE have_execution_policy PROPERTY VALUE false)
  endif()
endif()

set(f20
semaphore barrier
bit_width execution_policy
hardware_interference_size
format jthread latch lerp midpoint
likely math_constants ranges_find
source_location smart_ptr_for_overwrite
stop_callback stop_source
structured_bindings
)

foreach(t IN LISTS f20)
  if(have_${t})
    add_executable(${t} ${t}.cpp)

    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

set(fcoroutine coroutine_handle handle co_return generator promise return yield)
if(have_coroutine)
  add_subdirectory(coroutine)
endif()

# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f20 Nf)
list(LENGTH t Ne)
message(STATUS "C++20 features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()

# --- count features enabled
if(have_coroutine)
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/coroutine PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH fcoroutine Nf)
list(LENGTH t Ne)
message(STATUS "C++ coroutine features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()
endif()
