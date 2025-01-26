#include <iostream>
#include <stdfloat>
#include <cstdlib>

int main()
{

#ifdef __STDCPP_FLOAT16_T__
  [[maybe_unused]] std::float16_t h = 0.f16;
  std::cout << "float16_t is supported\n";
#endif
#ifdef __STDCPP_BFLOAT16_T__
  [[maybe_unused]] std::bfloat16_t b = 0.bf16;
  std::cout << "bfloat16_t is supported\n";
#endif
#ifdef __STDCPP_FLOAT32_T__
  [[maybe_unused]] std::float32_t f = 0.f32;
  std::cout << "float32_t is supported\n";
#endif
#ifdef __STDCPP_FLOAT64_T__
  [[maybe_unused]] std::float64_t d = 0.;
  std::cout << "float64_t is supported\n";
#endif
#ifdef __STDCPP_FLOAT128_T__
  [[maybe_unused]] std::float128_t q = 0.;
  std::cout << "float128_t is supported\n";
#endif

  return EXIT_SUCCESS;
}
