#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <unordered_map>
#include <string>

class LogManager
{
    public:
    // Constructors
    LogManager();
    LogManager(bool T, bool D, bool I, bool W, bool E, bool F);

    // Directly prints a char string or an array of char strings to output terminal
    void print(const char* str);
    void print(const char** strArr[]);
    void print(std::string& str);

    // Logs messages to terminal and log file
    // Log message levels:
    // TRACE (T): Basic logging of events occurring
    // DEBUG (D): Information that may be useful in debugging/troubleshooting
    // INFO (I): Important information about major events/states/etc.
    // WARN (W): Unexpected events or states that could cause issues
    // ERROR (E): Issues that are causing some functionality to not work, but not a full program crash
    // FATAL (F): Issues that cause the program to fail entirely
    void log(const char level, const char* source, const char* msg);

    // Sets state of log level
    void setLogLevel(const char* level, bool state);

    private:

    // Active log message levels
    std::unordered_map<std::string, bool> logLevels;
};

#endif // LOGMANAGER_H