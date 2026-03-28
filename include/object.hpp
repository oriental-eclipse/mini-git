#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../include/hasher.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

struct objectPath{
    std::string dirPath;
    std::string filePath;
};

void fileCopy(const objectPath &objPath, const char *content, size_t size);
objectPath filePathCreation(const Blob &blob);
void createDirectory(const char *path);
bool fileExists(const char *path);

#endif 