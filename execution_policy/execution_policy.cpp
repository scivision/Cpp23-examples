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

void print_results(
const char *const tag,
double ratio
)
{
  std::cout << std::fixed << std::setprecision(2);

  std::cout << std::left << std::setw(13) << tag << "  " << ratio << "\n";
}

int main(int argc, char *argv[])
{
  std::size_t N = 1'000'000;
  std::size_t iterationCount = 1;

  if(argc > 1)
    N = std::atoll(argv[1]);
  if(argc > 2)
    iterationCount = std::atoll(argv[2]);

  if (N < 1)
  {
    std::cerr << "N must be a positive integer\n";
    return EXIT_FAILURE;
  }
  if(iterationCount < 1)
  {
    std::cerr << "Iteration count must be a positive integer\n";
    return EXIT_FAILURE;
  }

// efficiently generate random numbers
// https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag
  std::vector<std::uint32_t> arr(N);
  std::mt19937 gen {std::random_device{}()};
  std::ranges::generate(arr, gen);

std::cout << "Sorting " << N << " elements over " << iterationCount << " iterations\n";
std::cout << "Method        Speed Ratio (vs. sequential)\n";

// sort benchmarks
double tref, tpar, tpar_unseq, tunseq;

for (std::size_t i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::seq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tref = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Sequential", 1.0);
}

for (std::size_t i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tpar = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Parallel", tref / tpar);
}

for (std::size_t i = 0; i < iterationCount; ++i)
{
std::vector<std::uint32_t> sorted(arr);
const auto tic = std::chrono::steady_clock::now();
std::sort(std::execution::par_unseq, sorted.begin(), sorted.end());
const auto toc = std::chrono::steady_clock::now();
tpar_unseq = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count();
print_results("Par_Unseq", tref / tpar_unseq);
}

for (std::size_t i = 0; i < iterationCount; ++i)
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
