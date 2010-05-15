/*
 * =====================================================================================
 *
 *       Filename:  CakeImp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2010 04:05:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "../common/Cake.h"
#include "stdio.h"
#include "util.h"
#include "Log.h"
#include <memory.h>
#include <assert.h>
#include <cstdlib>

int Cake::storeSourceCode(const char *path)const
{
    assert(path);

    char buf[512] = {0};
    if(GetLanExt(language)=="java"){
        sprintf(buf,"mkdir -p %s/%d",path,rid);
        if(system(buf)!=0){
            log(Log::INFO)<<"mkdir failed: "<<buf<<endlog;
            return -1;
        }
        sprintf(buf,"%s/%d/Main.java",path,rid);
    }
    else{
        sprintf(buf,"%s/%d.%s",path,rid,GetLanExt(language).c_str());
    }
	FILE *f = fopen(buf, "w+");
	if(!f)
		return -1;
	fprintf(f, "%s", sourceCode);
	fflush(f);
	fclose(f);
	return 0;
}
