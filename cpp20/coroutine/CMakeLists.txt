set_property(DIRECTORY PROPERTY LABELS "coroutine")

set(cpp20coroutine coroutine_handle handle co_return generator promise return yield)

foreach(t IN LISTS cpp20coroutine)
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
