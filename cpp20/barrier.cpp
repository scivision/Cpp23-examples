// https://en.cppreference.com/w/cpp/thread/barrier

#include <barrier>

#include <iostream>
#include <string>
#include <thread>  // std::jthread
#include <vector>
#include <cstdlib>

#include <syncstream>


int main()
{
    const auto workers = {"Anil", "Busara", "Carl"};

    auto on_completion = []() noexcept
    {
        // locking not needed here
        static auto phase =
            "... done\n"
            "Cleaning up...\n";
        std::cout << phase;
        phase = "... done\n";
    };

    std::barrier sync_point(std::ssize(workers), on_completion);

    auto work = [&](std::string name)
    {
        std::string product = "  " + name + " worked\n";
        std::osyncstream(std::cout) << product;  // ok, op<< call is atomic
        sync_point.arrive_and_wait();

        product = "  " + name + " cleaned\n";
        std::osyncstream(std::cout) << product;
        sync_point.arrive_and_wait();
    };

    std::cout << "Starting...\n";
    std::vector<std::jthread> threads;
    threads.reserve(std::size(workers));
    for (auto const& worker : workers)
        threads.emplace_back(work, worker);

    return EXIT_SUCCESS;
}
