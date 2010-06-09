#ifndef JUDGER_H
#define JUDGER_H

#include "../common/OJDefine.h"
#include "../common/SocketStream.h"
#include "../common/Packet.h"
#include "../common/Cake.h"
#include <string>

#define TIME_PER_TICK 100

class Judger: public Network::PacketPlayer
{
public:
	static Judger &GetInstance()
	{
		static Judger instance;
		return instance;
	}
    void SetJudgerId(int id){judgerId = id;}
    int GetJudgerId()const{return judgerId;}

	int StartUp();
	void CleanUp();
	int Run();
	bool bStopped;

    int DoJudge(Cake &cake);//judge a cake

    //interface
    virtual Network::Packet *ReceivePacket();
    virtual int SendPacket(Network::Packet *packet);
private:
    void Loop();
    void CleanTmpFiles();

	Judger(){bStopped = false; judgerId = -1;}
	~Judger(){}
	Judger(const Judger &);
	Judger &operator = (const Judger &);

    int judgerId;
    bool idleTime;
};

#endif
