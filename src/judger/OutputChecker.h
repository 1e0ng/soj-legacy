#ifndef OUTPUTCHECKER_H
#define OUTPUTCHECKER_H

#include <string>

class OutputChecker
{
	enum{OK, WA, PE, FILE_ERROR};
	void SetStdOutputPath(const std::string &path)
	{
		stdOutputPath = path;
	}
	void SetProgramOutputPath(const std::string &path)
	{
		programOutputPath = path;
	}

	int Check(int id)const;

	int Initialize();
private:
	static bool IsBlank(char c)
	{
		return c == '\n' || c == ' ' || c == '\b' || c == '\t';
	}

	std::string stdOutputPath;//should not ends with slash
	std::string programOutputPath;
};

extern OutputChecker theChecker;

#endif
