// https://en.cppreference.com/w/cpp/container/flat_multiset
// https://www.geeksforgeeks.org/cpp-23-flat-set-header/
#include <algorithm>
#include <flat_set>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>


// utility function to print the flat_set
void printfset(flat_set<int>& fset)
{
    std::ostream_iterator<int> it_out(cout, " ");
    std::copy(fset.begin(), fset.end(), it_out);
    std::cout << "\n";
}

// driver code
int main()
{
    // declaring a vector with random elements to initialize
    // the flat_set
    std::vector<int> vec{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };

    // defining a flat_set container with the vector
    // iterators
    std::flat_set<int> fset(begin(vec), end(vec));

    // printing the fset elements
    std::cout << "Elements in the flat_set: ";
    printfset(fset);

    // size of fset container
    std::cout << "Number of elements in the flat_set: "
         << fset.size() << "\n";

    // checking if 7 is present in the container using
    // find()
    if (fset.find(7) == fset.end()) {
        std::cout << "7 is not present.\n";
    }
    else {
        std::cout << "7 is present.\n";
    }

    // inserting an element to the fset
    fset.insert(7);
    std::cout << "AFTER INSERTING 7!!\n";
    // checking if 7 is present using contains()
    if (fset.contains(7)) {
        std::cout << "7 is present\n";
    }
    else {
        std::cout << "7 is not present.\n";
    }

    // upper_bound and lower_bound
    std::cout << "Upper Bound: " << *fset.upper_bound(3) << "\n";
    std::cout << "Lower Bound: " << *fset.lower_bound(3) << "\n";

    return EXIT_SUCCESS;
}
