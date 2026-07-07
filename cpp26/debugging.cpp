#include <debugging>

#include <cstdlib>
#include <iostream>

int main()
{
    if(std::is_debugger_present())
      std::cout << "Debugger is present\n";
    else
      std::cout << "Debugger is not present\n";

    return EXIT_SUCCESS;
}
