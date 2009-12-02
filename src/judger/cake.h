#ifndef CAKE_H
#define CAKE_H
class Cake{
public:
	void setRid(int x);
	void setPid(int x);
	void setJudgeStatus(int x);
	void setLanguage(int x);
	void setRtime(int x);
	void setRmemory(int x);
	void setSourceCode(char* x);
	void setTimeLimit(int x);
	void setMemoryLimit(int x);
	void setUid(int x);
	void setProblemAccepted(int x);
	void setUserAccepted(int x);
	
	int getRid()const;
	int getPid()const;
	int getJudgeStatus()const;
	int getLanguage()const;
	int getRtime()const;
	int getRmemory()const;
	void getSourceCode(char x[])const;
	int getTimeLimit()const;
	int getMemoryLimit()const;
	int getUid()const;
	int getProblemAccepted()const;
	int getUserAccepted()const;

	int storeSourceCode(const char *path);
private:
	int rid;
	int pid;
	int judgeStatus;
	int language;
	int rtime;
	int rmemory;
	char sourceCode[65536];
	int timeLimit;
	int memoryLimit;
	int uid;
	int problemAccepted;
	int userAccepted;
};
/*
$LANGUAGE[] = "All";
$LANGUAGE[] = "C++";
$LANGUAGE[] = "C";
$LANGUAGE[] = "JAVA";

$JUDGE_STATUS[] = "All";
$JUDGE_STATUS[] = "Queueing";
$JUDGE_STATUS[] = "Judging";
$JUDGE_STATUS[] = "Accepted";
$JUDGE_STATUS[] = "Wrong Answer";
$JUDGE_STATUS[] = "Time Limit Exceeded";
$JUDGE_STATUS[] = "Memory Limit Exceeded";
$JUDGE_STATUS[] = "Compile Error";
*/
#endif
