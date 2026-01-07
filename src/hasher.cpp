#include "../include/hasher.hpp"

uint64_t hashingLogic(const std::string &originalString){
    uint64_t hash = 6942067;     //funny number

    for(unsigned char c : originalString){
        hash = (hash * 67) + (uint64_t)c;
    }
    
    return hash;
}

uint64_t fileHasher(std::string fileName){
    std::ifstream fin;
    std::string line, content = "";
    uint64_t hashedFile = 0;
    fileName.append(".txt");

    fin.open("../objects/" + fileName);

    while(std::getline(fin, line)){
        content.append(line);
    }

    fin.close();

    hashedFile = hashingLogic(content);

    return hashedFile;
}