#ifndef JUDGER_H
#define JUDGER_H

#include <string>
#include "connection.h"

class Judger
{
public:
	enum JudgeResult
	{
		QUEUEING = 1,
		JUDGING,
		AC,
		WA,
		TLE,
		MLE,
		CE,
		PE,
		RE
	};
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
	Judger(){bStopped = false;}
	~Judger(){}
	Judger(const Judger &);
	Judger &operator = (const Judger &);

	Connection conn;
};

#endif
