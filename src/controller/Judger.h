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
#include "../common/Packet/JCConnect.h"
#include "../common/Cake.h"
#include "Database.h"
#include <string>
//#include <vector>
#include <time.h>
using namespace Network;

//set an uplimit for judge time in case server gets down
#define MAX_JUDGE_TIME 10

struct CakeInfo
{
    int rid;//run id
    int pid;//problem id
    int uid;//user id
    time_t beginTime;

    CakeInfo()
    {
        CleanUp();
    }
    void CleanUp()
    {
        rid = -1;
        pid = -1;
        uid = -1;
        beginTime = 0;
    }
};

class Judger: public PacketPlayer
{
public:
    enum Status{INVALID, INITIALIZING, AVAILABLE, BUSY};
    
    Judger();
    ~Judger();

    int GetJudgerId()const{return judgerId;}
    void SetJudgerId(int jid){judgerId = jid;}

    time_t GetLastStartJudgeTime()const{return cake.beginTime;}
    void SetLastStartJudgeTime(time_t judgeTime){cake.beginTime = judgeTime;}

    Status GetStatus()const{return status;}
    void SetStatus(Status s){status = s;}

    int GetRidJudging()const{return cake.rid;} 
    void SetRidJudging(int rid){cake.rid = rid;}

    bool IsLanguageSupported(int lan)const
    {
        if(lan <= LAN_MAX_ID && lan >= LAN_MIN_ID)
            return supportedLan[lan - LAN_MIN_ID];
        return false;
    }
    bool IsAvailable()const{return status == AVAILABLE;}

    int InitFromPacket(JCConnect *packet);
    int Judge(const Cake &c);
    int UpdateCakeToDB(const CakeReturn &cr, Database *db);

    //interface
    virtual int ProcessInput();
    virtual int ProcessOutput();
    virtual Packet *ReceivePacket();
    virtual int SendPacket(Packet *packet);
private:
    //std::vector<JudgeInfo> queue;
    
    int judgerId;//each judger is assigned a unique id

    Status status;//which status the judge is in

    bool supportedLan[LAN_NUMBER];//true:support false:not

    CakeInfo cake;
};

class JudgerManager
{
public:
    const static int MAX_JUDGER_NUMBER = 20;

    static JudgerManager &GetInstance()
    {
        static JudgerManager instance;
        return instance;
    }

    Judger *NewJudger();
    void RemoveJudger(Judger *j);
    void RemoveJudger(int jid);
    size_t GetJudgerNumber()const{return size;}

    Judger *GetAvailableJudgerFor(int lan);
    Judger *GetJudgerById(int jid);

    void PrepareFdset(fd_set *rset, int &maxfd);
    int ProcessInput(fd_set *rset);
    int ProcessOutput(fd_set *rset);

    void Tick();

    void OnClose();//restore not completely judged cake to db
private:
    void DoRemoveJudger(int index);

    JudgerManager();
    ~JudgerManager();
    JudgerManager &operator=(const JudgerManager &);
    JudgerManager(const JudgerManager &);

    Judger *judger[MAX_JUDGER_NUMBER];
    size_t size;
    size_t indexer;

    static int JudgerIndexer;//index judgers
};

#endif
