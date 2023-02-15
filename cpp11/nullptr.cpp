// https://en.cppreference.com/w/cpp/language/nullptr
#include <cstddef>
#include <iostream>

template<class T>
constexpr T clone(const T& t)
{
    return t;
}

void g(int* a)
{
    (void) a;
    std::cout << "Function g called\n";
}

int main()
{
    g(nullptr);        // Fine
   // g(NULL);           // Fine
   // g(0);              // Fine

    g(clone(nullptr)); // Fine
//  g(clone(NULL));    // ERROR: non-literal zero cannot be a null pointer constant
//  g(clone(0));       // ERROR: non-literal zero cannot be a null pointer constant
}
