// https://en.cppreference.com/w/cpp/thread/stop_token

#include <iostream>
#include <stop_token>
#include <thread>
#include <cstdlib>

using namespace std::literals::chrono_literals;

void f(std::stop_token stop_token, int value)
{
    while (!stop_token.stop_requested())
    {
        std::cout << value++ << ' ' << std::flush;
        std::this_thread::sleep_for(50ms);
    }
    std::cout << std::endl;
}

int main()
{
    std::jthread thread(f, 5); // prints 5 6 7 8... for approximately 1 second
    std::this_thread::sleep_for(1s);
    // The destructor of jthread calls request_stop() and join().

    return EXIT_SUCCESS;
}
