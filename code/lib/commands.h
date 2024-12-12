#ifndef COMMANDS_H
#define COMMANDS_H

#include <string> 
#include <vector>
#include <unordered_map>

using namespace std;

typedef int (*command_exe) (vector<string> const);

enum command_names {
    HELP,
    EXIT,
    EXE,
    CD,
    LS,
    UNKNOWN
};

command_names string_to_enum(string const);

struct command {
    string name;
    string description;
    command_exe exec;
};

extern unordered_map<command_names, command> commands;

#endif