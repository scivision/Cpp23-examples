set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MODULES)
  add_subdirectory(module)
endif()

check_cxx_symbol_exists(__cpp_lib_coroutine coroutine HAVE_COROUTINE)
if(HAVE_COROUTINE)
  add_executable(coroutine coroutine.cpp)
  add_test(NAME coroutine COMMAND coroutine)
endif()

check_cxx_symbol_exists(__cpp_lib_math_constants numbers HAVE_NUMBERS)
if(HAVE_NUMBERS)
  add_executable(numbers numbers.cpp)
  add_test(NAME numbers COMMAND numbers)
endif()

# --- likely
check_source_compiles(CXX
[=[
#if !__has_cpp_attribute(likely)
#error "no likely attribute"
#endif

int main(){
if (0) [[likely]]
return 0;
else [[unlikely]]
return 1;
}
]=]
HAVE_LIKELY
)

if(HAVE_LIKELY)
  add_executable(likely likely.cpp)
  add_test(NAME likely COMMAND likely)
endif()
