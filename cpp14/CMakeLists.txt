set_property(DIRECTORY PROPERTY LABELS 14)

check_source_compiles(CXX
"#include <cstdlib>
#include <thread>
int main() {
  unsigned int n = std::thread::hardware_concurrency();
  return EXIT_SUCCESS;
}"
HAVE_THREAD
)

if(HAVE_THREAD)
  add_executable(thread_count thread_count.cpp)
  add_test(NAME thread COMMAND thread_count)
endif()
