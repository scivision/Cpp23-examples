#include <vector>
#include <algorithm>
#include <iostream>
#include <execution>
#include <string_view>
#include <chrono>
#include <cstdlib>

#include "randgen.h"


void print_match(const std::vector<uint32_t>& arr, std::vector<uint32_t>::const_iterator i1){
  if (i1 == arr.end())
    std::cout << "No matching adjacent elements\n";
  else
    std::cout << "The first adjacent pair of equal elements is at "
              << std::distance(arr.begin(), i1) << ", *i1 = "
              << *i1 << '\n';
}


template <typename ExecutionPolicy>

double measure_execution_time(const std::size_t N, ExecutionPolicy policy, std::string_view policy_name, double tref = 0)
{
  std::vector<uint32_t> arr = gen_array(N);

  auto tic = std::chrono::steady_clock::now();

  [[maybe_unused]] auto i1 = std::adjacent_find(policy, arr.begin(), arr.end());

  auto toc = std::chrono::steady_clock::now();
  double duration = std::chrono::duration_cast<std::chrono::microseconds>(toc - tic).count();
  if (tref == 0)
    tref = duration;

  print_results(policy_name, tref / duration, duration);
  //print_match(arr, i1);

  return duration;
}

// https://en.cppreference.com/w/cpp/algorithm/adjacent_find

int main(int argc, char** argv){

  std::size_t N = 10'000'000;

  if(argc > 1)
    N = std::atoll(argv[1]);

std::cout << "finding matching adjacent pair in " << N << " elements\n";

// serial
double tref = 0;

tref = measure_execution_time(N, std::execution::seq, "Sequential", tref);
measure_execution_time(N, std::execution::par, "Parallel", tref);
measure_execution_time(N, std::execution::par_unseq, "Parallel unsequenced", tref);
measure_execution_time(N, std::execution::unseq, "Unsequenced", tref);


  return EXIT_SUCCESS;

}
