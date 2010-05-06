/*
 * =====================================================================================
 *
 *       Filename:  IniFile.h
 *
 *    Description:  Read ini file
 *
 *        Version:  1.0
 *        Created:  05/03/2010 06:32:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INIFILE_H
#define INIFILE_H

#include <map>
#include <string>

class IniFile
{
public:
    bool InitFromFile(const char *file);
    bool InitFromString(const char *buf, long size);

    bool GetStringValue(const char *section, const char *key, char *dest, size_t size);
    bool GetIntValue(const char *section, const char *key, int &dest);
public:
    typedef std::map<std::string, std::string> KeyValue_t;
    typedef std::map<std::string, KeyValue_t> SectionKey_t;
    SectionKey_t profile;
};

#endif
