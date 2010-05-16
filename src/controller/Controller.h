/*
 * =====================================================================================
 *
 *       Filename:  Controller.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2010 04:13:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../common/SocketStream.h"

//in microseconds
#define TIME_PER_TICK 100

class Controller
{
public:
    static Controller &GetInstance()
    {
        static Controller instance;
        return instance;
    }
    int Init();
    int Loop();
    int CleanUp();

    bool bStopped;
private:
    //for singleton
    Controller(){bStopped = false;}
    ~Controller(){}
    Controller(const Controller &);
    Controller &operator=(const Controller &);

    Network::SocketStream listener;
};

#endif
