if(NOT DEFINED HAVE_CXX20_MODULES)
  message(CHECK_START "Checking for C++20 modules...")

  try_compile(HAVE_CXX20_MODULES
  ${CMAKE_CURRENT_BINARY_DIR}/try_mod
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/math.cpp ${CMAKE_CURRENT_SOURCE_DIR}/modules/math.ixx
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED true
  OUTPUT_VARIABLE build_result
  )

  if(HAVE_CXX20_MODULES)
    message(CHECK_PASS "found.")
  else()
    message(CHECK_FAIL "not supported.")
    message(VERBOSE "${build_result}")
  endif()
endif()



# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
