#include <iostream>
#include "../include/hasher.hpp"

int main(){
    std::string fileName;
    std::cout << "\nEnter filename : ";
    std::getline(std::cin, fileName);

    uint64_t blob = fileHasher(fileName);

    fileCopy(blob, fileName);

    return 0;
}