#ifndef HASHER_HPP
#define HASHER_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

struct Blob{
    std::string hash;
    std::string content;
};

uint64_t hashingLogic(const std::string &originalString);
Blob fileHasher(const std::string &fileName);

#endif