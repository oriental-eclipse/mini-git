#include <iostream>
#include "../include/hasher.hpp"
#include "../include/object.hpp"
#include "../include/index.hpp"

int main(int argc, char* argv[]){
    if(argc < 3){
        std::cerr << "Expecting: ./ksks add <filename>\n";
        return 1;
    }

    const char* command = argv[1];
    std::string fileName(argv[2]);

    if(strcmp(command, "add") != 0){
        std::cerr << "Unknown command : " << command << '\n';
        return 1;
    }

    Blob blob = fileHasher(fileName);
    
    fileCopy(filePathCreation(blob), blob.content.c_str(), blob.content.size());

    stageFile(fileName, blob.hash);

    return 0;
}