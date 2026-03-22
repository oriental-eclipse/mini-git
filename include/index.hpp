#ifndef INDEX_HPP
#define INDEX_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

using Index = std::unordered_map<std::string, std::string>;

Index readIndex();
void writeIndex(Index &index);
void stageFile(const std::string &fileName, const std::string &hash);

#endif 
