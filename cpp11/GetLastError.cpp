#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <system_error>

#include <iostream>

[[ noreturn ]] void PrintError(const char* name)
{
    DWORD err = GetLastError();

    std::string message = std::system_category().message(err);

    std::cerr << "ERROR:" << name << ": " << err << ": " << message << "\n";

    ExitProcess(err);
}

int main(){
    // intentionally generate an error

    if(!GetProcessId(nullptr))
        PrintError("GetProcessId");
}
