#include <debugging>

#include <cstdlib>
#include <print>

int main()
{
    if(std::is_debugger_present())
      std::println("Debugger is present");
    else
      std::println("Debugger is not present");

    return EXIT_SUCCESS;
}
