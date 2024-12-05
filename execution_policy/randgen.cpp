#include <vector>
#include <algorithm> // std::ranges::generate
#include <random>

#include <iomanip> // std::setw
#include <iostream>

#include "randgen.h"

std::vector<std::uint32_t> gen_array(const std::size_t N){
// efficiently generate random numbers
// https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag

std::vector<std::uint32_t> arr(N);

std::mt19937 gen {std::random_device{}()};

std::ranges::generate(arr, gen);

return arr;
}


void print_results(std::string_view tag, double ratio, double microseconds)
{
  std::cout << std::fixed << std::setprecision(2);

  std::cout << std::left << std::setw(13) << tag << "  " << ratio << " " << microseconds << "\n";
}
