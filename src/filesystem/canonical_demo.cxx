#include <cstring>
#include <iostream>

#include "canonical.hpp"

int main(){

char pathstr[LEN];

strcpy(pathstr, "~/foo");
expanduser(pathstr);
std::cout << pathstr << std::endl;

strcpy(pathstr, "../..");
canonical(pathstr);
std::cout << pathstr << std::endl;

return EXIT_SUCCESS;
}
