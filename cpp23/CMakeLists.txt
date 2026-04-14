set_property(DIRECTORY PROPERTY LABELS 23)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 23)

if(has_cpp_attribute)

block()
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

check_source_compiles(CXX
"#if !__has_cpp_attribute(assume)
#error \"no assume attribute\"
#endif"
have_assume
)
endblock()

endif()

# https://en.cppreference.com/w/cpp/header/version
foreach(t IN ITEMS
    expected flat_map flat_set
    format_ranges
    mdspan print
    ranges_cartesian_product ranges_enumerate ranges_iota
    stacktrace unreachable)
  check_cxx_symbol_exists(__cpp_lib_${t} "version" have_${t})
endforeach()

check_include_file_cxx(stdfloat have_stdfloat)

block()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_REQUIRED_LIBRARIES stdc++exp)
  check_source_compiles(CXX "int main() { return 0; }"
  can_link_stdcxxexp
  )

  set(CMAKE_REQUIRED_LIBRARIES stdc++_libbacktrace)
  check_source_compiles(CXX "int main() { return 0; }"
  can_link_stdcxx_libbacktrace
  )
endif()
endblock()

block()
if(have_stacktrace)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14 AND can_link_stdcxxexp)
      set(CMAKE_REQUIRED_LIBRARIES stdc++exp)
    elseif(can_link_stdcxx_libbacktrace)
      set(CMAKE_REQUIRED_LIBRARIES stdc++_libbacktrace)
    endif()
  endif()

  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_REQUIRED_FLAGS -fsized-deallocation)
    if(can_link_stdcxxexp)
      set(CMAKE_REQUIRED_LIBRARIES stdc++exp)
    endif()
  endif()

  check_source_compiles(CXX
  "#include <stacktrace>
  int main()  {
      auto x = std::stacktrace::current() ;
      return 0;
  }"
  stacktrace_links
  )
  if(NOT stacktrace_links)
    set_property(CACHE have_stacktrace PROPERTY VALUE false)
  endif()
endif()
endblock()


foreach(t IN LISTS cpp23features)
  if(have_${t})
    add_executable(${t} ${t}.cpp)
    target_link_libraries(${t} PRIVATE Threads::Threads)

    if(${t} STREQUAL "unreachable")
      add_test(NAME unreachable
      COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/will_fail.cmake)
    else()
      add_test(NAME ${t} COMMAND ${t})
    endif()
  endif()
endforeach()

if(TARGET assume AND cppcheck)
  set_property(TARGET assume PROPERTY CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK};--suppress=redundantInitialization")
endif()

if(WIN32)
# https://gcc.gnu.org/gcc-14/changes.html
if(can_link_stdcxxexp)
    if(TARGET print)
      target_link_libraries(print PRIVATE stdc++exp)
    endif()
endif()
endif()

# stacktrace
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14 AND can_link_stdcxxexp)
    if(TARGET stacktrace)
      target_link_libraries(stacktrace PRIVATE stdc++exp)
    endif()
  elseif(can_link_stdcxx_libbacktrace)
    if(TARGET stacktrace)
      target_link_libraries(stacktrace PRIVATE stdc++_libbacktrace)
    endif()
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(TARGET stacktrace)
    target_compile_options(stacktrace PRIVATE -fsized-deallocation)
    if(can_link_stdcxxexp)
      target_link_libraries(stacktrace PRIVATE stdc++exp)
    endif()
  endif()
endif()
# end stacktrace

if(TEST unreachable)
  set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()

if(TEST expected)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()

if(TEST mdspan)
  set_property(TEST mdspan PROPERTY PASS_REGULAR_EXPRESSION "1004 1005")
endif()
