/*
 * =====================================================================================
 *
 *       Filename:  Log.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 08:34:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Log.h"
#include "Configuration.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

int _Log::Init()
{
    f = fopen(Configuration::GetInstance().logFile.c_str(), "a");
    if(!f)
        return -1;
    return 0;
}

int _Log::AddLog(const char *str)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    fprintf(f, "%s %s",  buf, str);
    return 0;
}

void Log(const char *fmt, ...)
{
    char buf[MAX_LOG_LENGTH - 32];//make room for time
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    _log.AddLog(buf);
}
