// https://en.cppreference.com/w/cpp/error/current_exception
#include <array>
#include <iostream>
#include <exception>
#include <cstdlib>

void handle_error_ptr(std::exception_ptr err_ptr)
// passing by value is ok
{
  try {
    if (err_ptr) {
      std::rethrow_exception(err_ptr);
    }
  } catch(const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}


int main(){
  // intentionally generate an error

  std::array<int,1> x;

  std::exception_ptr err_ptr;

  try{
    std::cout << x.at(1) << std::endl;
  }
  catch (...){
    err_ptr = std::current_exception();
  }
  handle_error_ptr(err_ptr);

  std::cout << "OK: exception handled" << std::endl;
  return EXIT_SUCCESS;

}
