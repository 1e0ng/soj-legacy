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
    LAN_MIN_ID = 1,

    LAN_CPP = 1,
    LAN_C,
    LAN_JAVA,

    LAN_MAX_ID = 3,
    LAN_NUMBER = 3,
};

enum JudgeResult
{
    JR_QUEUEING = 1,
    JR_JUDGING,
    JR_AC,           //accepted
    JR_WA,           //wrong anser
    JR_TLE,          //time limit exceeded
    JR_MLE,          //memory limit exceeded
    JR_CE,           //compile error
    JR_PE,           //presentation error
    JR_RE,           //runtime error

    JR_RESULT_NUMBER
};

#endif
