#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>

class Compiler
{
public:
	Compiler()
	{
		bLogOutput = true;
	}
	virtual std::string GetName()const
	{
		return "";
	}
	void SetCC(const std::string &cc)
	{
		this->cc = cc;
	}
	void SetSrcPath(const std::string &path)
	{
		srcPath = path;
	}
	void SetSrcFilename(const std::string &filename)
	{
		srcFilename = filename;
	}
	void SetDestPath(const std::string &path)
	{
		destPath = path;
	}
	void SetDestFilename(const std::string &filename)
	{
		destFilename = filename;
	}
	void LogOutput(bool flag){bLogOutput = flag;}
	void SetLogPath(const std::string &path)
	{
		logPath = path;
	}
	void SetLogFilename(const std::string &filename)
	{
		logFilename = filename;
	}
	void SetOptions(const std::string &opts)
	{
		options = opts;
	}

	virtual bool Compile() const;

	virtual std::string GetSrcPathname() const{return ComposePathname(srcPath, srcFilename);}
	virtual std::string GetDestPathname() const{return ComposePathname(destPath, destFilename);}
	virtual std::string GetLogPathname() const{return ComposePathname(logPath, logFilename);}
	virtual std::string GetCC() const{return cc;}
	virtual std::string GetOptions() const{return options;}
private:
	static std::string ComposePathname(const std::string &path, const std::string &filename);
protected:
	std::string cc;
	std::string srcPath;
	std::string srcFilename;
	std::string destPath;
	std::string destFilename;
	bool bLogOutput;
	std::string logPath;
	std::string logFilename;
	std::string options;
};

class GCCCompiler : public Compiler
{
public:
	GCCCompiler()
	{
		cc = "gcc";
		options = "-ansi -fno-asm -Wall -lm -DONLINE_JUDGE --static  2";
	}
	virtual std::string getName()const
	{
		return "GCC";
	}
};

class GPPCompiler : public Compiler
{
public:
	GPPCompiler()
	{
		cc = "g++";
		options = "-ansi -fno-asm -Wall -lm -DONLINE_JUDGE --static  2";
	}
	virtual std::string getName()const
	{
		return "G++";
	}
};

class JavaCompiler : public Compiler
{
public:
	JavaCompiler()
	{
		cc = "javac";
	}
	virtual std::string getName()const
	{
		return "Javac";
	}
	//virtual bool Compile()const{}
};



class CompilerFactory
{
public:
	static CompilerFactory *GetInstance()
	{
		if(instance == NULL)
			instance = new CompilerFactory();
		return instance;
	}
	static void DestroyInstance()
	{
		delete instance;
		instance = NULL;
	}

	Compiler *GetCompiler(const std::string &lan);

	~CompilerFactory();
private:
	CompilerFactory();
	static CompilerFactory *instance;
	std::vector<Compiler *> compilers;
};

#endif
