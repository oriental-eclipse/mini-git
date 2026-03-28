#include "../include/index.hpp"

static std::string INDEX_PATH = "../index/stage.txt";

Index readIndex(){
    Index index;

    std::ifstream fin(INDEX_PATH);

    if(!fin){
        return index;
    }

    std::string file, hash;

    while(fin >> file >> hash){
        index[file] = hash;
    }

    return index;
}

void writeIndex(const Index &index){
    std::ofstream fout(INDEX_PATH);

    for(const auto &[file, hash] : index){
        fout << file << " " << hash << '\n';
    }
}

void stageFile(const std::string &fileName, const std::string &hash){
    std::filesystem::create_directories("../index");

    Index index = readIndex();

    index[fileName] = hash;

    writeIndex(index);

    std::cout << "Staged " << fileName << '\n';
}