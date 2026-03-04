#ifndef HASHER_HPP
#define HASHER_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>

struct Blob{
    std::string hash;
    std::string content;
};

struct objectPath{
    std::string dirPath;
    std::string filePath;
};

uint64_t hashingLogic(const std::string &originalString);
Blob fileHasher(const std::string &fileName);
void fileCopy(const objectPath &objPath, const std::string &content);
objectPath filePathCreation(const Blob &blob);


#endif