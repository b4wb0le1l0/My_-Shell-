#include <iostream>
#include <windows.h>
#include <time.h>
#include <filesystem>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "commands.h"

command_names string_to_enum(string const c) {
    if (c == "help") {
        return HELP;
    } else if (c == "exit") {
        return EXIT;
    } else if (c == "exe") {
        return EXE;
    } else if (c == "cd") {
        return CD;
    } else if (c == "ls") {
        return LS;
    } else {
        return UNKNOWN;
    }
}


int help(vector<string> const args) 
{
    for (auto c : commands) 
    {
        cout << c.second.name << ": " << c.second.description << endl;
    }
    
    return 0;
}

int exit(vector<string> const args) 
{
    return 1;
}

int exe(vector<string> args) 
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (args.empty()) 
    {
        cerr << "Error: No arguments provided." << endl;
        return 1;
    }

    string commandLine = args[0];
    
    if (commandLine.substr(0, 2) == "./")
    {
        commandLine = commandLine.substr(2);
    }

    if (commandLine.substr(commandLine.size() - 4) != ".exe") 
    {
        commandLine += ".exe";
    }

    for (size_t i = 1; i < args.size(); i++) 
    {
        commandLine += " " + args[i];
    }

    clock_t start = clock();

    if (!CreateProcess(NULL, 
        &commandLine[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
        ))
    {
        cerr << "Error: CreateProcess failed with error code " << GetLastError() << '\n';
        return 1;
    }
    else 
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time of execution: " << seconds << "\n";

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return 0;
}

int ls(vector<string> const args) 
{
    for (const auto &entry : filesystem::directory_iterator(filesystem::current_path())) 
    {
        cout << entry.path().filename().string() << endl;
    }

    return 0;
}

int cd(vector<string> args) 
{
    try 
    {
        if (args[1] == "..") 
        {
            filesystem::current_path(filesystem::current_path().remove_filename());
        } 
        else 
        {
            filesystem::current_path(filesystem::current_path().append(args[1]));
        }
    } 
    catch (const filesystem::filesystem_error& e)
    {
        cerr << "Error: not dir with this name " + args[1] + "!\n";
    }
    return 0;
}

unordered_map<command_names, command> commands = 
{
    { HELP, {"help", "Displays a list of commands", help}},
    { EXIT, {"exit", "Ends the program", exit}},
    { CD, {"cd", "Change directory", cd}},
    { LS, {"ls", "List directory contents", ls}},
    { EXE, {"exe", "Create new process with your program and consult the time of execution", exe}}
};

