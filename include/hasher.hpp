#ifndef HASHER_HPP
#define HASHER_HPP

#include <string>
#include <cstdint>
#include <fstream>

uint64_t hashingLogic(const std::string &originalString);
uint64_t fileHasher(std::string fileName);

#endif