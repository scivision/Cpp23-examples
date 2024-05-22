set_property(DIRECTORY PROPERTY LABELS 23)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_VERSION VERSION_LESS 3.30 AND CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
  if(WIN32)
    set(CMAKE_REQUIRED_FLAGS "/Qstd:c++23")
  else()
    set(CMAKE_REQUIRED_FLAGS "-std=c++23")
  endif()
endif()

if(has_cpp_attribute)

check_source_compiles(CXX
"#if !__has_cpp_attribute(assume)
#error \"no assume attribute\"
#endif
int main(){ return 0; }"
have_assume
)

endif()

# https://en.cppreference.com/w/cpp/header/version
foreach(t IN ITEMS expected flat_map flat_set mdspan print stacktrace unreachable)
  check_cxx_symbol_exists(__cpp_lib_${t} "version" have_${t})
endforeach()

check_include_file_cxx(stdfloat have_stdfloat)


set(f23 assume expected flat_map flat_set mdspan print
stacktrace stdfloat unreachable)

foreach(t IN LISTS f23)
  if(have_${t})
    add_executable(${t} ${t}.cpp)

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

if(TARGET stdfloat)
  if(cppcheck)
  set_property(TARGET stdfloat PROPERTY CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK};--suppress=unreadVariable")
  endif()
  target_compile_options(stdfloat PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-unused-variable>)
endif()

# https://gcc.gnu.org/gcc-14/changes.html
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14)
    if(TARGET stacktrace)
      target_link_libraries(stacktrace PRIVATE stdc++exp)
    endif()
    if(TARGET print AND WIN32)
      target_link_libraries(print PRIVATE stdc++exp)
    endif()
  else()
    if(TARGET stacktrace)
      target_link_libraries(stacktrace PRIVATE stdc++_libbacktrace)
    endif()
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(TARGET stacktrace)
    target_compile_options(stacktrace PRIVATE -fsized-deallocation)
    target_link_libraries(stacktrace PRIVATE stdc++exp)
  endif()
  if(TARGET print AND WIN32)
    target_link_libraries(print PRIVATE stdc++exp)
  endif()
endif()

if(TEST unreachable)
  set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()

if(TEST expected)
  set_property(TEST expected PROPERTY PASS_REGULAR_EXPRESSION "42")
endif()

if(TEST mdspan)
  set_property(TEST mdspan PROPERTY PASS_REGULAR_EXPRESSION "1004 1005")
endif()

# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f23 Nf)
list(LENGTH t Ne)
message(STATUS "C++23 features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()
