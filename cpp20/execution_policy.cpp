// https://devblogs.microsoft.com/cppblog/using-c17-parallel-algorithms-for-better-performance/

#include <cstddef>
#include <iostream>
#include <algorithm> // std::sort, std::ranges::generate
#include <chrono>
#include <random>
#include <ratio>
#include <vector>
#include <cstdlib>
#include <iomanip>

#include <execution> // std::execution


constexpr size_t N = 1'000'000;
constexpr int iterationCount = 1;

void print_results(
const char *const tag,
double ratio
)
{
  std::cout << std::fixed << std::setprecision(2);

  std::cout << std::left << std::setw(13) << tag << "  " << ratio << "\n";
}

int main() {

// efficiently generate random numbers
// https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag
  std::vector<std::uint32_t> arr(N);
  std::mt19937 gen {std::random_device{}()};
  std::ranges::generate(arr, gen);

std::cout << "Sorting " << N << " elements\n";
std::cout << "Iteration count " << iterationCount << "\n";
std::cout << "Method        Speed Ratio (vs. sequential)\n";

// sort benchmarks
double tref, tpar, tpar_unseq, tunseq;

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::seq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tref = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Sequential", 1.0);
}

// AppleClang 15, Clang 17 doesn't yet have the following

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tpar = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Parallel", tref / tpar);
}

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par_unseq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tpar_unseq = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Par_Unseq", tref / tpar_unseq);
}

for (int i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::unseq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tunseq = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Unseq", tref / tunseq);
}

  return EXIT_SUCCESS;
}
