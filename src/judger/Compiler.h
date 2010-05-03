#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>

class Compiler
{
public:
    enum CompilerType{COMPILER_GCC, COMPILER_GPP, COMPILER_JAVA};

	virtual ~Compiler(){}

	virtual std::string GetName()const = 0;

    virtual CompilerType GetCompilerType() const = 0;

	void SetCC(const std::string &cc)
	{
		this->cc = cc;
	}
    std::string GetCC()const
    {
        return cc;
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
	virtual std::string GetName()const
	{
		return cc;
	}
    virtual CompilerType GetCompilerType()const
    {
        return COMPILER_GCC; 
    } 
    virtual bool Compile(int id)const;
};

class GPPCompiler : public Compiler
{
public:
	virtual std::string GetName()const
	{
        return cc;
	}
    virtual CompilerType GetCompilerType()const
    {
        return COMPILER_GPP;
    }
	virtual bool Compile(int id)const;
};

class JavaCompiler : public Compiler
{
public:
	virtual std::string GetName()const
	{
		return cc;
	}
    virtual CompilerType GetCompilerType()const
    {
        return COMPILER_JAVA;
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
    Compiler *GetCompiler(Compiler::CompilerType type);
    bool HasCompiler(Compiler::CompilerType type)
    {
        return compilers[type] != NULL;
    }
	static void SetupCompiler(Compiler &compiler, const std::string &srcPath, const std::string &destPath);
private:
	CompilerFactory();
	~CompilerFactory();
	CompilerFactory(const CompilerFactory &);
	CompilerFactory &operator=(const CompilerFactory &);

	std::vector<Compiler *> compilers;
};

#endif
