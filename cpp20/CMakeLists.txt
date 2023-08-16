set_property(DIRECTORY PROPERTY LABELS 20)

if(HAVE_MODULES)
  add_subdirectory(module)
endif()

# https://en.cppreference.com/w/cpp/header/version
check_cxx_symbol_exists(__cpp_lib_coroutine "version" cpp20_coroutine)
check_cxx_symbol_exists(__cpp_lib_math_constants "version" cpp20_numbers)
check_cxx_symbol_exists(__cpp_lib_source_location "version" cpp20_source_location)
check_cxx_symbol_exists(__cpp_lib_smart_ptr_for_overwrite "version" cpp20_smart_ptr_for_overwrite)
check_cxx_symbol_exists(__cpp_lib_int_pow2 "version" cpp20_bit_width)

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
    const int n = 3;
    const auto v = {4, 1, 3, 2};

    std::ranges::find(v, n);
    return 0;
}"
cpp20_ranges_find
)

foreach(t IN ITEMS bit_width likely numbers ranges_find source_location smart_ptr_for_overwrite)
  if(cpp20_${t})
    add_executable(${t} ${t}.cpp)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(cpp20_coroutine)
  add_subdirectory(coroutine)
endif()
