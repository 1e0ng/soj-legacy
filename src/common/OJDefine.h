/*
 * =====================================================================================
 *
 *       Filename:  OJDefine.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 07:23:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef OJDEFINE_H
#define OJDEFINE_H

enum Language
{
    LAN_C,
    LAN_CPP,
    LAN_JAVA,

    LAN_NUMBER,
};

enum JudgeResult
{
   JR_AC,           //accepted
   JR_WA,           //wrong anser
   JR_TLE,          //time limit exceeded
   JR_MLE,          //memory limit exceeded
   JR_CE,           //compile error
   JR_PE,           //presentation error
   JR_SYSERR,       //system error
};

#endif
