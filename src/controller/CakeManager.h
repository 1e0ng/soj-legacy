/*
 * =====================================================================================
 *
 *       Filename:  CakeManager.h
 *
 *    Description:  Manage  cakes being judged
 *
 *        Version:  1.0
 *        Created:  05/07/2010 06:39:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CAKE_MANAGER_H
#define CAKE_MANAGER_H

#include <bitset>

class CakeManager
{
public:
    const static int MAX_CAKE_NUMBER = 64;

    CakeManager():size(0){}
    ~CakeManager();

    Cake *GetCakeToJudge();
    void ReleaseCake(Cake *cake);

    void Tick();
    int LoadCakes();
private:
    Cake cake[MAX_CAKE_NUMBER];
    bitset<MAX_CAKE_NUMBER> usedFlag;    
    size_t size;
};

#endif
