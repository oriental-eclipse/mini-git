#include <iostream>
#include "../include/hasher.hpp"
#include "../include/object.hpp"
#include "../include/index.hpp"

int main(){
    std::string fileName;
    std::cout << "\nEnter filename : ";
    std::getline(std::cin, fileName);

    Blob blob = fileHasher(fileName);

    
    fileCopy(filePathCreation(blob), blob.content);

    return 0;
}