
// C++ program to demonstrate the usage of
// contains(), find() and count() functions

#include <flat_map>
#include <utility> // for std::make_pair

#include <iostream>
#include <string>

int main()
{
    std::flat_map<int, std::string> myMap;

    myMap.insert(std::make_pair(1, "Geeks"));
    myMap.insert(std::make_pair(2, "for"));
    myMap.insert(std::make_pair(3, "Geeks"));

    // Check if a key exists using contains()
    if (myMap.contains(2)) {
        std::cout << "Key 2 exists in the map." << "\n";
    }

    // Find an element by key using find()
    auto it = myMap.find(3);
    if (it != myMap.end()) {
        std::cout << "Value at key 3: " << it->second << "\n";
    }

    // Count the number of elements with a specific key
    // using count()
    int key = 2;
    int numOccurrences = myMap.count(key);
    std::cout << "Number of occurrences of key " << key << ": "
         << numOccurrences << "\n";

    return 0;
}
