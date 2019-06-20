#include <iostream>
import math;

int main(){
   int a=1;
   int b=2;

   int absum = add(a, b);
   int abdif = subtract(a, b);

   std::cout << "a: " << a << "  b: " << b << std::endl;
   std::cout << "a+b: " << absum << "  a-b: " << abdif <<  std::endl;

   return EXIT_SUCCESS;
}
