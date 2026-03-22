#include "../include/index.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

static std::string INDEX_PATH = "../index/stage.txt";

std::unordered_map<std::string, std::string> readIndex(){
    std::unordered_map<std::string, std::string> index;

    std::ifstream fin(INDEX_PATH);

    if(!fin){
        return index;
    }

    std::string file, hash;

    if(fin >> file >> hash){
        index[file] = hash;
    }

    return index;
}

