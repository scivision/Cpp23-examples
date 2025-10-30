// https://en.cppreference.com/w/cpp/language/attributes/assume

#include <cmath>
#include <cstdlib>

void g(int){};
void h(void){};

void f(int& x, int y)
{


    [[assume(x > 0)]]; // Compiler may assume x is positive

    g(x / 2); // More efficient code possibly generated

    x = 3;
    int z = x;

    // commented due to AppleClang
    // error: assumption is ignored because it contains (potential) side-effects [-Werror,-Wassume]
    // [[assume((h(), x == z))]];
    // Compiler may assume x would have the same value after
                               // calling h
                               // The assumption does not cause a call to h

    h();
    g(x); // Compiler may replace this with g(3);

    h();
    g(x); // Compiler may NOT replace this with g(3);
          // An assumption applies only at the point where it appears

    z = std::abs(y);

    // commented due to AppleClang
    // error: assumption is ignored because it contains (potential) side-effects [-Werror,-Wassume]
    // [[assume((g(z), true))]]; // Compiler may assume g(z) will return

    g(z); // Due to above and below assumptions, compiler may replace this with g(10);

    [[assume(y == -10)]]; // Undefined behavior if y != -10 at this point

    [[assume((x - 1) * 3 == 12)]];

    g(x); // Compiler may replace this with g(5);

}

int main(){
    int x = 10;
    int y = -10;
    f(x, y);
    return EXIT_SUCCESS;
}
