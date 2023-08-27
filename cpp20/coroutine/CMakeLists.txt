set_property(DIRECTORY PROPERTY LABELS "coroutine")

foreach(t IN ITEMS coroutine_handle handle co_return generator promise return yield
    )
  add_executable(coroutine_${t} ${t}.cpp)
  add_test(NAME coroutine_${t} COMMAND coroutine_${t})
endforeach()

set_property(TEST coroutine_co_return coroutine_handle coroutine_promise coroutine_return coroutine_yield
PROPERTY PASS_REGULAR_EXPRESSION "counter: 2"
)
