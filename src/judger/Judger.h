#ifndef JUDGER_H
#define JUDGER_H

#include "../common/OJDefine.h"
#include "../common/SocketStream.h"
#include "../common/Packet.h"
#include <string>

class Judger: public PacketPlayer
{
public:
	const static int POLL_INTERVAL = 500;//in ms

	static Judger &GetInstance()
	{
		static Judger instance;
		return instance;
	}
	int StartUp();
	void CleanUp();
	int Run();
	bool bStopped;
private:
	Judger(){bStopped = false; judgerId = -1;}
	~Judger(){}
	Judger(const Judger &);
	Judger &operator = (const Judger &);

    int judgerId;
};

#endif
