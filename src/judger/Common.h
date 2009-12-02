#ifndef COMMON_H
#define COMMON_H

#include <string>

extern const char *SignalName[];
extern const char *SyscallName[];

#define LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

//get current time in string in the format fmt
std::string GetTimeInString(const char *fmt);

#endif//COMMON_H
