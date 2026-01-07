#include <iostream>
#include "../include/hasher.hpp"

int main(){
    std::string fileName;
    uint64_t hash1, hash2;

    std::cout << "\nenter1:";
    std::getline(std::cin, fileName);

    hash1 = fileHasher(fileName);

    std::cout << "\nenter2:";
    std::getline(std::cin, fileName);

    hash2 = fileHasher(fileName);

    std::cout << hash1 << '\n' << hash2;

    if(hash1 == hash2){
        std::cout << "\nsame";
    }
    else{
        std::cout << "\nnot same";
    }

    return 0;
}