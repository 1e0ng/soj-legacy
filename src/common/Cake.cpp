/*
 * =====================================================================================
 *
 *       Filename:  Cake.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2010 03:29:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Cake.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void Cake::CleanUp()
{
    rid = -1;
    pid = -1;
    language = -1;
    rtime = -1;
    rmemory = -1;
    timeLimit = -1;
    memoryLimit = -1;
    uid = -1;
    memset(sourceCode, 0, sizeof(sourceCode));
}
