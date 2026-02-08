#ifndef HASHER_HPP
#define HASHER_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>

uint64_t hashingLogic(const std::string &originalString);
uint64_t fileHasher(std::string fileName);
void fileCopy(uint64_t hashedBlob, std::string fileName);

#endif