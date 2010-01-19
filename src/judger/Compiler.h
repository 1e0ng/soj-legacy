#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>

class Compiler
{
public:
	virtual ~Compiler(){}
	virtual std::string GetName()const
	{
		return "";
	}
	void SetCC(const std::string &cc)
	{
		this->cc = cc;
	}
	//all path should not ends with slash
	void SetSrcPath(const std::string &path)
	{
		srcPath = path;
	}
	void SetDestPath(const std::string &path)
	{
		destPath = path;
	}
	void SetOptions(const std::string &opts)
	{
		options = opts;
	}

	virtual bool Compile(int id) const = 0;
protected:
	std::string cc;
	std::string srcPath;
	std::string destPath;
	std::string options;
};

class GCCCompiler : public Compiler
{
public:
	GCCCompiler()
	{
		cc = "gcc";
		options = "-g -O2 -std=gnu99 -static -lm";
		//options = "-m32";
	}
	virtual std::string GetName()const
	{
		return "GCC";
	}
	virtual bool Compile(int id)const;
};

class GPPCompiler : public Compiler
{
public:
	GPPCompiler()
	{
		cc = "g++";
		options = "-g -O2 -static";
		//options = "-m32";
	}
	virtual std::string GetName()const
	{
		return "G++";
	}
	virtual bool Compile(int id)const;
};

class JavaCompiler : public Compiler
{
public:
	JavaCompiler()
	{
		cc = "javac";
		options = "-O -sourcepath . -source 1.5 -d . ";
	}
	virtual std::string GetName()const
	{
		return "Javac";
	}
	virtual bool Compile(int id)const;
};



class CompilerFactory
{
public:
	static CompilerFactory &GetInstance()
	{
		static CompilerFactory instance;
		return instance;
	}
	int Initialize();

	Compiler *GetCompiler(const std::string &lan);
	void DisposeCompiler(Compiler *compiler){}
	static void SetupCompiler(Compiler &compiler, const std::string &srcPath, const std::string &destPath);
private:
	CompilerFactory();
	~CompilerFactory();
	CompilerFactory(const CompilerFactory &);
	CompilerFactory &operator=(const CompilerFactory &);

	static CompilerFactory *instance;
	std::vector<Compiler *> compilers;
};

#endif
