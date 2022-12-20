# Subprocess aborted, stack smashing, etc. are deliberately NOT caught by CTest WILL_FAIL property
# https://gitlab.kitware.com/cmake/cmake/-/issues/20397
# This script catches them and makes WILL_FAIL work as expected

execute_process(COMMAND ${exe}
RESULT_VARIABLE ret
ERROR_VARIABLE err
)

if(NOT ret EQUAL 0)
  message(FATAL_ERROR "Error code ${ret}
${err}"
  )
endif()
