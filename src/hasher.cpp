#include "../include/hasher.hpp"

uint64_t hashingLogic(const std::string &originalString){
    uint64_t hash = 6942067;     //funny number

    for(unsigned char c : originalString){
        hash = (hash * 67) + (uint64_t)c;
    }
    
    return hash;
}

Blob fileHasher(const std::string &fileName){
    std::ifstream fin;
    std::string fileContent;
    Blob blob;

    fin.open("../data/" + fileName, std::ios::binary);

    if(!fin.is_open()){
        std::cerr << "Fatal Error : File doesn't exist / Could not be opened!\n";
        exit(1);
    }

    std::ostringstream ss;
    ss << fin.rdbuf();
    fileContent = ss.str();

    std::string blobHeader = "blob " + std::to_string(fileContent.size());
    blobHeader.push_back('\0');
    blob.content = blobHeader + fileContent;
    std::stringstream hexer;
    hexer << std::hex << std::setw(16) << std::setfill('0') << hashingLogic(blob.content);;
    blob.hash = hexer.str();

    fin.close();

    return blob;
}