set_property(DIRECTORY PROPERTY LABELS "coroutine")

set(CMAKE_CXX_STANDARD 20)

# https://en.cppreference.com/w/cpp/header/version

check_cxx_symbol_exists(__cpp_impl_coroutine "version" cpp_impl_coroutine)
if(cpp_impl_coroutine)
  check_cxx_symbol_exists(__cpp_lib_coroutine "version" have_coroutine)
endif()

if(NOT have_coroutine)
  return()
endif()


foreach(t IN ITEMS coroutine_handle handle co_return generator promise return yield)
  add_executable(coroutine_${t} ${t}.cpp)

  add_test(NAME coroutine_${t} COMMAND coroutine_${t})
endforeach()

set_property(TEST coroutine_co_return coroutine_handle coroutine_promise coroutine_return coroutine_yield
PROPERTY PASS_REGULAR_EXPRESSION "counter: 2"
)

# bug fixed in upstream LLVM
foreach(t IN ITEMS coroutine_coroutine_handle coroutine_handle)
  target_compile_options(${t} PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unsequenced>)
endforeach()
