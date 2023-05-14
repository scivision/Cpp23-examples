// https://en.cppreference.com/w/cpp/utility/source_location

#include <iostream>
#include <string_view>
#include <source_location>
#include <cstdlib>

void log(const std::string_view message,
         const std::source_location location =
               std::source_location::current())
{
    std::clog << "file: "
              << location.file_name() << "("
              << location.line() << ":"
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}

template <typename T> void fun(T x)
{
    log(x);
}

int main()
{
    log("Hello world!");
    fun("Hello C++20!");
    return EXIT_SUCCESS;
}
