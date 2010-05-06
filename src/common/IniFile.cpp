/*
 * =====================================================================================
 *
 *       Filename:  IniFile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2010 06:32:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "IniFile.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string>
using namespace std;

bool IniFile::InitFromFile(const char *file)
{
    FILE *f = fopen(file, "r");
    bool ret = false;
    if(f)
    {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        char *buf = new char[size + 1];
        buf[size] = 0;
        fseek(f, 0, SEEK_SET);
        fread(buf, size, 1, f);
        ret = InitFromString(buf, size);
        delete buf;
    }
    return ret;
}

inline bool IsBlank(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}
//pos will be positioned at file end or newline character's position
inline void SkipLine(const char *buf, long size, int &pos)
{
    for(; pos < size && buf[pos] && buf[pos] != '\n'; ++pos);
}

bool IniFile::InitFromString(const char *buf, long size)
{
    enum State{START, ENTER_SECTION, LEAVE_SECTION, ENTER_KEY, LEAVE_KEY, ENTER_VALUE, LEAVE_VALUE};
    State s = START;

    string section;
    string key;
    string value;
    for(int i = 0; i < size; i++)
    {
        switch(s)
        {
        case START:
            {
                while(i < size && buf[i])
                {
                    if(buf[i] == ';' || buf[i] == '\n' || buf[i] == '\r')
                    {
                        SkipLine(buf, size, i);
                        ++i;
                    }
                    else if(buf[i] == '[')
                        break;
                    else
                        return false;
                }
                if(!(i < size && buf[i]))
                    return true;
                s = ENTER_SECTION;
            }
            break;
        case ENTER_SECTION:
            {
                while(i < size && buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
                    ++i;
                if(buf[i] == '\n' || buf[i] == '\r')
                    return false;
                int j = i;
                while(j < size && buf[j] && buf[j] != ']' && buf[j] != '\n')//no multi-line
                    ++j;
                if(buf[j] != ']')//file ends but section not ends
                    return false;
                int k = j;
                --j;
                while(buf[j] == ' ' || buf[j] == '\t' || buf[j] == '\r')
                    --j;
                section.assign(buf + i, j - i + 1);
                i = k;
                s = LEAVE_SECTION;
            }
            break;
        case LEAVE_SECTION:
            {
                while(i < size && buf[i] && buf[i] != '\n')
                {
                    if(buf[i] == ';')
                    {
                        SkipLine(buf, size, i);
                    }
                    else if(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\r')
                        ++i;
                    else
                        return false;
                }
                if(buf[i] != '\n')//file ends
                    return true;
                ++i;
                while(i < size && buf[i])//skip empty line and comments
                {
                    if(buf[i] == '\r' || buf[i] == '\n' || buf[i] == ';')
                    {
                        SkipLine(buf, size, i);
                        ++i;
                    }
                    else if(buf[i] == '[')
                    {
                        s = ENTER_SECTION;
                        break;
                    }
                    else if(buf[i] == ' ' || buf[i] == '\t')
                    {
                        return false;
                    }
                    else
                    {
                        s = ENTER_KEY;
                        --i;
                        break;
                    }
                }
            }
            break;
        case ENTER_KEY:
            {
                int j = i + 1;
                while(j < size && buf[j] && buf[j] != '=' && buf[i] != '\n')//looking for '='
                    ++j;
                if(buf[j] != '=')//file ends but value not met yet
                    return false;
                int k = j;
                --j;
                //          xxxxxxx = xxxxxxxx
                //          i      jk
                while(buf[j] == ' ' || buf[j] == '\t' || buf[j] == '\r')
                    --j;//we can rest assure that this won't go out of bound because buf[i] is not blank

                //          xxxxxxx = xxxxxxxx
                //          i     j k
                key.assign(buf + i, j - i + 1);
                i = k;
                s = ENTER_VALUE;
            }
            break;
        case LEAVE_KEY://not used
            break;
        case ENTER_VALUE:
            {
                while(i < size && buf[i] && (buf[i] == ' ' || buf[i] == '\t') && buf[i] != '\n')
                    ++i;
                if(!(i < size && buf[i]) || buf[i] == '\n')//no value
                    return false;
                int j = i + 1;
                while ( j < size && buf[j] && buf[j] != '\n' && buf[j] != ';')//file ending doesn't matter
                    ++j;
                int k = j;
                --j;
                while(buf[j] == ' ' || buf[j] == '\t' || buf[j] == '\r')
                    --j;
                value.assign(buf + i, j - i + 1);
                profile[section][key] = value;
                i = k;
                if(buf[k] == ';')
                    SkipLine(buf, size, i);
                s = LEAVE_VALUE;
            }
            break;
        case LEAVE_VALUE:
            {
                while(i < size && buf[i])
                {
                    if(buf[i] == ';' || buf[i] == '\n' || buf[i] == '\r')
                    {
                        SkipLine(buf, size, i);
                        ++i;
                    }
                    else if(buf[i] == '[')
                    {
                        s = ENTER_SECTION;
                        break;
                    }
                    else if(buf[i] == ' ' || buf[i] == '\t')
                    {
                        return false;
                    }
                    else
                    {
                        s =ENTER_KEY;
                        --i;
                        break;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    return true;
}

bool IniFile::GetStringValue(const char *section, const char *key, char *dest, size_t size)
{
    string val = profile[section][key];
    if(val.empty())
    {
        *dest = '\0';
        return false;
    }
    else
    {
        strncpy(dest, val.c_str(), size);
        return true;
    }
}

bool IniFile::GetIntValue(const char *section, const char *key, int &dest)
{
    string val = profile[section][key];
    if(val.empty())
    {
        dest = 0;
        return false;
    }
    else
    {
        dest = atoi(val.c_str());
        return true;
    }
}

/* 
int main(int argc, char *argv[])
{
    IniFile ini;
    if(ini.InitFromFile("test.ini"))
    {
        for(IniFile::SectionKey_t::iterator it1 = ini.profile.begin(); it1 != ini.profile.end(); ++it1)
        {
            printf("section %s\n", (it1->first).c_str());
            for(IniFile::KeyValue_t::iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2)
            {
                printf("\"%s\" = \"%s\"\n", (it2->first).c_str(), (it2->second).c_str());
            }
        }
    }
    else
    {
        printf("failed");
    }
}
*/
