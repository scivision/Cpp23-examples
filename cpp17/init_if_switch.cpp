// https://en.cppreference.com/w/cpp/language/switch
#include <iostream>
#include <cstdlib>

int main(){

    // the C++17 init-statement syntax can be helpful when there is
    // no implicit conversion to integral or enumeration type
    struct Device
    {
        enum State { SLEEP, READY, BAD };
        auto state() const { return m_state; }

        /*...*/

    private:
        State m_state{};
    };

    switch (auto dev = Device{}; dev.state())
    {
        case Device::SLEEP:
            /*...*/
            break;
        case Device::READY:
            /*...*/
            break;
        case Device::BAD:
            /*...*/
            break;
    }

    // pathological examples

    // labels don't require a compound statement either
    switch (int n = 1)
    {
        case 0:
        case 1:
            std::cout << n << '\n';
    }

    return EXIT_SUCCESS;
}
