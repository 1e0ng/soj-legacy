#include "OutputChecker.h"
#include "Log.h"
#include "stdio.h"
#include "Configuration.h"
#include <string.h>

OutputChecker theChecker;

int OutputChecker::Check(int pid, int rid)const
{
    char tmp[512] = {0};
    FILE *sout, *pout;//standard output and program output
    sprintf(tmp, "%s/%d", stdOutputPath.c_str(), pid);
    sout = fopen(tmp, "r");
    if(sout == NULL)
    {
        log(Log::WARNING)<<"OutputChecker:Can't open file \""<<tmp<<"\" for read"<<endlog;
        return FILE_ERROR;
    }
    sprintf(tmp, "%s/%d", programOutputPath.c_str(), rid);
    pout = fopen(tmp, "r");
    if(pout == NULL)
    {
        log(Log::WARNING)<<"OutputChecker:Can't open file \""<<tmp<<"\" for read"<<endlog;
        fclose(sout);
        return FILE_ERROR;
    }

    int ret = OK;
    char s[256], p[256];
    for(;;) {
        int send = fscanf(sout, "%256s", s);
        int pend = fscanf(pout, "%256s", p);
        if (send != pend) {
            ret = WA;
            break;
        }
        if (strcmp(s, p) != 0) {
            ret = WA;
            break;
        }
    }
    /*
    bool send = false, pend = false, OKready = true;

    for(;;)
    {
        if(fscanf(sout, "%c", &s) == EOF)
        {
            s = ' ';
            send = true;
        }
        if(fscanf(pout, "%c", &p) == EOF)
        {
            p = ' ';
            pend = true;
        }
        if(send && pend)
        {
            if(OKready)
                ret = OK;
            else
                ret = OK;
            break;
        }
        if(s != p)
        {
            OKready = false;
            if(!IsBlank(s) && !IsBlank(p))
            {
                ret = WA;
                break;
            }
            if(IsBlank(s)&&IsBlank(p))
                continue;
            if(IsBlank(s))
            {
                for(;;)
                {
                    if(fscanf(sout, "%c", &s) == EOF)
                    {
                        send = true;
                        ret = WA;
                        break;
                    }
                    if(!IsBlank(s))
                        break;
                }
                if(send)
                    break;
                if(s != p)
                {
                    ret = WA;
                    break;
                }
            }
            else if(IsBlank(p))
            {
                for(;;)
                {
                    if(fscanf(pout, "%c", &p) == EOF)
                    {
                        ret = WA;
                        pend = true;
                        break;
                    }
                    if(!IsBlank(p))
                        break;
                }
                if(pend)
                    break;
                if(s != p)
                {
                    ret = WA;
                    break;
                }
            }
        }
    }*/
    fclose(sout);
    fclose(pout);
    return ret;
}

int OutputChecker::Initialize()
{
    stdOutputPath = Configuration::GetInstance().GetStandardOutputPath();
    programOutputPath = Configuration::GetInstance().GetProgramOutputPath();
    return 0;
}
