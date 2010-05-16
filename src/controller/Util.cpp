/*
 * =====================================================================================
 *
 *       Filename:  Util.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2010 02:55:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Util.h"
#include <signal.h>

SigHandler Signal(int signum, SigHandler handler)
{
    struct sigaction act, oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);;
    act.sa_flags = 0;
    if(sigaction(signum, &act, &oact) < 0)
        return (SIG_ERR);
    return oact.sa_handler;
}
