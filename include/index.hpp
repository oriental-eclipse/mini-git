#ifndef INDEX_HPP
#define INDEX_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

std::unordered_map<std::string, std::string> readIndex();
void writeIndex(const std::unordered_map<std::string, std::string> &index);
void stageFile(const std::string &fileName, const std::string &hash);

#endif 
