/*
 * =====================================================================================
 *
 *       Filename:  CakeManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2010 06:57:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "CakeManager.h"

CakeManager::~CakeManager()
{
    usedFlag.reset();
    for(int i = 0; i < MAX_CAKE_NUMBER; i++)
        cake[i].CleanUp();
}
