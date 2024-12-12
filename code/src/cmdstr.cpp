#include <iostream>
#include <stdio.h>
#include <sstream>
#include <filesystem>
#include <windows.h>

#include "commands.h"
#include "cmdstr.h"

string get_current_date_time() 
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return string(buffer);
}

void cmd_loop() 
{
    vector<string> args;
    int status = 0;

    while (!status) 
    {
        auto path = filesystem::current_path();
        cout << path.string() << ">";
        args = cmd_read();
        status = cmd_execute(args);
    }
}

vector<string> cmd_read() 
{
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> args;
    string word;

    while (iss >> word) 
    {
        args.push_back(word);
    }

    return args;
}

int cmd_execute(vector<string> args) 
{
    command_names maybe_command_name = string_to_enum(args[0]);
    
    if (maybe_command_name != UNKNOWN) 
    {
        return (commands[maybe_command_name].exec)(args);
    } 
    else 
    {
        return (commands[EXE].exec)(args);
    }
    return 0;
}

