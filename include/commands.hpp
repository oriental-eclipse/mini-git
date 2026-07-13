#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <ftw.h>
#include "../include/hasher.hpp"
#include "../include/object.hpp"
#include "../include/index.hpp"

struct Command{
    const char* name;
    int (*handler)(const int, const char*[]);
};

extern Command commands[];
extern const size_t COMMAND_COUNT;

int dispatcher(const int argc, const char* argv[]);
int addCommand(const int argc, const char* argv[]);
int initCommand(const int argc, const char* argv[]);

#endif