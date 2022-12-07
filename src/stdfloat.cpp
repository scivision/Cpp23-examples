#include <stdfloat>

int main()
{

#ifdef __STDCPP_FLOAT16_T__
  std::float16_t h = 0.;
  std::cout << "float16_t is supported" << std::endl;
#endif
#ifdef __STDCPP_BFLOAT16_T__
  std::bfloat16_t b = 0.;
  std::cout << "bfloat16_t is supported" << std::endl;
#endif
#ifdef __STDCPP_FLOAT32_T__
  std::float32_t f = 0.;
  std::cout << "float32_t is supported" << std::endl;
#endif
#ifdef __STDCPP_FLOAT64_T__
  std::float64_t d = 0.;
  std::cout << "float64_t is supported" << std::endl;
#endif
#ifdef __STDCPP_FLOAT128_T__
  std::float128_t q = 0.;
  std::cout << "float128_t is supported" << std::endl;
#endif

    return 0;
}
