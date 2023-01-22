check_cxx_symbol_exists(__cpp_lib_filesystem filesystem FEATURE_FILESYSTEM)
if(FEATURE_FILESYSTEM)
check_source_compiles(CXX
[=[
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#error "No C++ filesystem header support"
#endif

int main () {
fs::path tgt(".");
auto h = tgt.has_filename();
return 0;
}
]=]
HAVE_FILESYSTEM
)
endif()
