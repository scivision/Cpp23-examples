// https://devblogs.microsoft.com/cppblog/using-c17-parallel-algorithms-for-better-performance/

#include <cstddef>
#include <iostream>
#include <algorithm> // std::sort, std::ranges::generate
#include <chrono>
#include <random>
#include <ratio>
#include <vector>
#include <cstdlib>

#include <execution> // std::execution


constexpr size_t N = 1'000'000;
constexpr int iterationCount = 1;

void print_results(
const char *const tag,
const std::vector<std::uint32_t>& sorted,
std::chrono::steady_clock::time_point tic,
std::chrono::steady_clock::time_point toc
)
{
  const auto tdur = std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic).count();

  std::cout << tag << " " << sorted.front() <<
    ".." << sorted.back() << " Time: " << tdur << " ms\n";
}

int main() {

// efficiently generate random numbers
// https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag
  std::vector<std::uint32_t> arr(N);
  std::mt19937 gen {std::random_device{}()};
  std::ranges::generate(arr, gen);

// sort benchmarks

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
print_results("Serial   ", sorted, tic, toc);
}

// AppleClang 15, Clang 17 doesn't yet have the following

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
print_results("Parallel ", sorted, tic, toc);
}

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par_unseq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
print_results("Par_Unseq", sorted, tic, toc);
}

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::unseq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
print_results("Unseq    ", sorted, tic, toc);
}

  return EXIT_SUCCESS;
}
