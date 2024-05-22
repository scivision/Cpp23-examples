#include <chrono>
#include <iostream>
#include <stop_token>
#include <thread>
#include <cstdlib>

using namespace std::chrono_literals;

void worker_fun(int id, std::stop_source stop_source)
{
    std::stop_token stoken = stop_source.get_token();
    for (int i = 10; i; --i)
    {
        std::this_thread::sleep_for(300ms);
        if (stoken.stop_requested())
        {
            std::printf("  worker%d is requested to stop\n", id);
            return;
        }
        std::printf("  worker%d goes back to sleep\n", id);
    }
}

int main()
{
    std::jthread threads[4];
    std::cout << std::boolalpha;
    auto print = [](const std::stop_source& source)
    {
        std::printf("stop_source stop_possible = %s, stop_requested = %s\n",
                    source.stop_possible() ? "true" : "false",
                    source.stop_requested() ? "true" : "false");
    };

    // Common source
    std::stop_source stop_source;

    print(stop_source);

    // Create worker threads
    for (int i = 0; i < 4; ++i)
        threads[i] = std::jthread(worker_fun, i + 1, stop_source);

    std::this_thread::sleep_for(500ms);

    std::puts("Request stop");
    stop_source.request_stop();

    print(stop_source);

    // Note: destructor of jthreads will call join so no need for explicit calls

    return EXIT_SUCCESS;
}
