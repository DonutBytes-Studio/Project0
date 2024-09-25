#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {

public:
    void log(LogLevel level, const string& message);

private:
    string levelToString(LogLevel level);
};

#endif
