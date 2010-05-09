/*
 * =====================================================================================
 *
 *       Filename:  Judger.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 03:25:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef JUDGER_H
#define JUDGER_H
#include "../common/SocketStream.h"
#include "../common/Packet.h"
#include "../common/OJDefine.h"
#include <string>
#include <vector>
#include <time.h>
using namespace Network;

//set an uplimit for judge time in case server gets down
#define MAX_JUDGE_TIME 10

struct JudgeInfo
{
    int rid;//run id
    int pid;//problem id
    int uid;//user id
    time_t beginTime;
};

class Judger
{
public:
    enum Status{INVALID, INITIALIZING, AVAILABLE, BUSY};
    
    Judger();
    ~Judger();

    int GetJudgerId()const{return judgerId;}
    void SetJudgerId(int jid){judgerId = jid;}

    SocketStream &GetSocketStream(){return stream;}

    time_t GetLastStartJudgeTime()const{return lastStartJudgeTime;}
    void SetLastStartJudgeTime(time_t judgeTime){lastStartJudgeTime = judgeTime;}

    Status GetStatus()const{return status;}
    void SetStatus(Status s){status = s;}

    int GetPidJudging()const{return pidJudging;} 
    void SetPidJudging(int pid){pidJudging = pid;}

    int SendPacket(Packet *packet);
    int ReceivePacket();

    bool IsLanguageSupported(Language lan)const
    {
        if(lan < LAN_NUMBER)
            return supportedLan[lan];
        return false;
    }
private:
    vector<JudgeInfo> queue;
    
    int judgerId;//each judger is assigned a unique id

    SocketStream stream;//socket associated with this judger
    time_t lastStartJudgeTime;//in case judger get down during judging

    Status status;//which status the judge is in

    int pidJudging;//the problem id being judged

    bool supportedLan[LAN_NUMBER];//true:support false:not
};

class JudgerManager
{
public:
    const static int MAX_JUDGER_NUMBER = 10;

    static &GetInstance()
    {
        static JudgerManager instance;
        return instance;
    }

    Judger *NewJudger();
    void RemoveJudger(Judger *j);
    void RemoveJudger(int jid);
    size_t GetJudgerNumber()const{return size;}

    Judger *GetAvailableJudgerFor(Language lan);
    Judger *GetJudgerById(int jid);

    ProcessInput();
    ProcessOutput();
private:
    JudgerManager();
    ~JudgerManager();
    JudgerManager &operator=(const JudgerManager &);
    JudgerManager &JudgerManager(const JudgerManager &);

    Judger *judger[MAX_JUDGER_NUMBER];
    size_t size;

    static int JudgerIndexer;//index judgers
};

#endif
