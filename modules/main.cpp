#include <iostream>
import math;

int main(){
   int a=1;
   int b=2;

   int absum = add(a, b);
   int abdif = subtract(a, b);

   if (a + b != absum) { return EXIT_FAILURE; }
   if (a - b != abdif) { return EXIT_FAILURE; }

   std::cout << "OK: Modules demo" << std::endl;

   return EXIT_SUCCESS;
}
