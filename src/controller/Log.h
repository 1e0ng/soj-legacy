/*
 * =====================================================================================
 *
 *       Filename:  Log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 08:31:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef LOG_H
#define LOG_H
#include <stdio.h>

const static int MAX_LOG_LENGTH = 512;

class _Log
{
public:
    int Init();
    int AddLog(const char *str);
private:
    FILE *f;
};

extern _Log _log;

void Log(const char *fmt, ...);

#endif
