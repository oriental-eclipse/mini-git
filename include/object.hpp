#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../include/hasher.hpp"

struct objectPath{
    std::string dirPath;
    std::string filePath;
};

void fileCopy(const objectPath &objPath, const std::string &content);
objectPath filePathCreation(const Blob &blob);

#endif 