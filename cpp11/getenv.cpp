// https://en.cppreference.com/w/cpp/utility/program/getenv

#include <iostream>
#include <cstdlib>

std::string get_env_var(std::string const & key) {
    char * val = getenv( key.c_str() );
    return val ? std::string(val) : std::string("");
}

std::string get_home_dir(){
  return get_env_var(
#ifdef _WIN32
  "USERPROFILE"
#else
  "HOME"
#endif
  );
}

int main(){

    std::string home_dir = get_home_dir();
    if (home_dir.empty()) {
        std::cerr << "get_home_dir() failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "home directory: " << home_dir << "\n";

    return EXIT_SUCCESS;
}
