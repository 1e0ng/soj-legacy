/*
 * =====================================================================================
 *
 *       Filename:  Util.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 08:21:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef UTIL_H
#define UTIL_H

typedef void (*SigHandler)(int);

SigHandler Signal(int signum, SigHandler handler);

#endif
