set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MODULES)
  add_subdirectory(module)
endif()

check_cxx_symbol_exists(__cpp_lib_coroutine coroutine cpp20_coroutine)
check_cxx_symbol_exists(__cpp_lib_math_constants numbers cpp20_numbers)
check_source_compiles(CXX
"#if !__has_cpp_attribute(likely)
#error \"no likely attribute\"
#endif
int main(){ return 0; }"
cpp20_likely
)
check_source_compiles(CXX
"#include <algorithm>
int main(){
    std::ranges::find({4, 3}, 3);
    return 0;
}"
cpp20_ranges_find
)

foreach(t IN ITEMS coroutine likely numbers ranges_find)
  if(cpp20_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
