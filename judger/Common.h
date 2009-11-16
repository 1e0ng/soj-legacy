#ifndef COMMON_H
#define COMMON_H

#include <string>

extern const char *signal_name[];

#define LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

//get current time in string in the format fmt
std::string GetTimeInString(const char *fmt);

#endif//COMMON_H
