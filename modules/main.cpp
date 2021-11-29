#include <iostream>
#include <cassert>

import math;

int main(){
   int a=1;
   int b=2;

   int absum = add(a, b);
   int abdif = subtract(a, b);

   assert(a + b == absum);
   assert(a - b == abdif);

   std::cout << "OK: Modules demo" << std::endl;

   return EXIT_SUCCESS;
}
