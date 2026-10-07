#include "logSystem.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

// Constructors
LogSystem::LogSystem()
{
    // default log level states
    logLevels["TRACE"] = false;
    logLevels["DEBUG"] = true;
    logLevels["INFO"] = true;
    logLevels["WARN"] = true;
    logLevels["ERROR"] = true;
    logLevels["FATAL"] = true;

    // Creates LOG.log file and writes the current system time
    FILE* file = fopen("Log.log", "w");
    auto now = std::chrono::system_clock::now();
    std::time_t currTime = std::chrono::system_clock::to_time_t(now);
    fputs(std::ctime(&currTime), file);
    fclose(file);
}
LogSystem::LogSystem(bool T, bool D, bool I, bool W, bool E, bool F)
{
    // default log level states
    logLevels["TRACE"] = T;
    logLevels["DEBUG"] = D;
    logLevels["INFO"] = I;
    logLevels["WARN"] = W;
    logLevels["ERROR"] = E;
    logLevels["FATAL"] = F;

    // Creates LOG.log file and writes the current system time
    FILE* file = fopen("Log.log", "w");
    auto now = std::chrono::system_clock::now();
    std::time_t currTime = std::chrono::system_clock::to_time_t(now);
    fputs(std::ctime(&currTime), file);
    fclose(file);
}

// Directly prints a char string or an array of char strings to output terminal
void LogSystem::print(const char* str)
{
    std::cout << str << std::endl;
}
void LogSystem::print(const char** strArr[])
{
    while (*strArr != nullptr)
    {
        std::cout << *strArr;

        strArr++;
    }
    std::cout << std::endl;
}
void LogSystem::print(std::string& str)
{
    std::cout << str << std::endl;
}

// Logs messages to terminal and log file
// Log message levels:
// TRACE (T): Basic logging of events occurring
// DEBUG (D): Information that may be useful in debugging/troubleshooting
// INFO (I): Important information about major events/states/etc.
// WARN (W): Unexpected events or states that could cause issues
// ERROR (E): Issues that are causing some functionality to not work, but not a full program crash
// FATAL (F): Issues that cause the program to fail entirely
void LogSystem::log(const char level, const char* source, const char* msg)
{
    std::string str;

    switch (level)
    {
        case 'T':
            if (logLevels["TRACE"]) str = "(TRACE) ";
            break;
        case 'D':
            if (logLevels["DEBUG"]) str = "(DEBUG) ";
            break;
        case 'I':
            if (logLevels["INFO"]) str = "(INFO) ";
            break;
        case 'W':
            if (logLevels["WARN"]) str = "(WARN) ";
            break;
        case 'E':
            if (logLevels["ERROR"]) str = "(ERROR) ";
            break;
        case 'F':
            if (logLevels["FATAL"]) str = "(FATAL) ";
            break;
        default:
            str = "(UNKNOWN) ";
    }

    if (str.size() > 1)
    {
        str.append(source);
        str.append(": ");
        str.append(msg);
        str.append("\n");

        std::cout << str << std::endl; // prints to terminal

        std::ofstream file("Log.log", std::ios::app);
        if (!file.is_open())
        {
            std::perror("Log.log opening failed");
        }
        else
        {
            file << str;
        }
        file.close();
    }
}

// Sets state of log level
void LogSystem::setLogLevel(const char* level, bool state)
{
    logLevels[level] = state;
}