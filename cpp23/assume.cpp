// https://en.cppreference.com/w/cpp/language/attributes/assume
//
// A false assumption is undefined behavior; AppleClang’s implementation materializes this as a trap instruction, raising SIGTRAP.
// Other compilers may simply optimize away paths without visibly trapping, so the issue only appeared with AppleClang.

// Why AppleClang traps: For a language-level assumption it can treat the negated condition as unreachable.
// Emitting an explicit trap (e.g., ud2) is a valid way to represent unreachable code, making UB manifest early.

// Side-effect warnings: Attributes like [[assume((h(), x == z))]] are rejected (ignored) because the expression can have observable side effects;
// AppleClang warns (and with -Werror becomes an error).
// Only pure boolean conditions should be used.

#include <cmath>
#include <cstdlib>

void g(int){};
void h(void){};

void f(int& x, int y)
{
    [[assume(x > 0)]]; // Compiler may assume x is positive

    g(x / 2); // More efficient code possibly generated

    // Set x so later assumption about (x - 1) * 3 == 12 holds (x becomes 5).
    x = 5;
    int z = x;

    // Side-effect examples commented: AppleClang warns and may treat as ignored.
    // [[assume((h(), x == z))]]; // would be ignored: potential side-effects.

    h();
    g(x); // Compiler may replace this with g(5) (after x assignment).

    h();
    g(x); // An assumption applies only at the point where it appears.

    z = std::abs(y);
    // [[assume((g(z), true))]]; // would be ignored: potential side-effects.

    g(z); // With y == -10 below, z == 10.

    [[assume(y == -10)]]; // Undefined behavior if y != -10; here it's true.
    [[assume((x - 1) * 3 == 12)]]; // Holds since x == 5; avoids UB trap.

    g(x); // Compiler may replace this with g(5).
}

int main(){
    int x = 10;
    int y = -10;
    f(x, y);
    return EXIT_SUCCESS;
}
