#ifndef JUDGER_H
#define JUDGER_H

#include <string>

class Judger
{
public:
	enum JudgeResult
	{
		AC,
		CE,
		RE,
		TLE,
		MLE,
		PE,
	};
	static int StartUp();
	static void CleanUp();
	static int Run();

	static std::string GetLanName(int lanid);

	static bool bStopped;
};

#endif
