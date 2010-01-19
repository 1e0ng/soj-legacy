#include "cake.h"
#include "stdio.h"
#include "util.h"
#include "Log.h"
#include <memory.h>
#include <cstdlib>
void Cake::setRid(int x){
	rid=x;
}
void Cake::setPid(int x){
	pid=x;
}
void Cake::setJudgeStatus(int x){
	judgeStatus=x;
}
void Cake::setLanguage(int x){
	language=x;
}
void Cake::setRtime(int x){
	rtime=x;
}
void Cake::setRmemory(int x){
	rmemory=x;
}
void Cake::setSourceCode(char* x){
	strcpy(sourceCode,x);
}
void Cake::setTimeLimit(int x){
	timeLimit=x;
}
void Cake::setMemoryLimit(int x){
	memoryLimit=x;
}
void Cake::setUid(int x){
	uid=x;
}
void Cake::setProblemAccepted(int x){
	problemAccepted=x;
}
void Cake::setUserAccepted(int x){
	userAccepted=x;
}

int Cake::getRid()const{
	return rid;
}
int Cake::getPid()const{
	return pid;
}
int Cake::getJudgeStatus()const{
	return judgeStatus;
}
int Cake::getLanguage()const{
	return language;
}
int Cake::getRtime()const{
	return rtime;
}
int Cake::getRmemory()const{
	return rmemory;
}
void Cake::getSourceCode(char x[])const{
	memcpy(x,sourceCode,sizeof(sourceCode));
}
int Cake::getTimeLimit()const{
	return timeLimit;
}
int Cake::getMemoryLimit()const{
	return memoryLimit;
}
int Cake::getUid()const{
	return uid;
}
int Cake::getProblemAccepted()const{
	return problemAccepted;
}
int Cake::getUserAccepted()const{
	return userAccepted;
}
int Cake::storeSourceCode(const char *path)
{
	char buf[512];
	if(path){
		if(GetLanExt(language)=="java"){
			sprintf(buf,"mkdir -p %s/%d",path,rid);
			if(system(buf)!=0){
				log(Log::INFO)<<"mkdir failed: "<<buf<<endlog;
				return -1;
			}
			sprintf(buf,"%s/%d/Main.java",path,rid);
		}
		else{
			sprintf(buf,"%s/%d.%s",path,rid,GetLanExt(language).c_str());
		}
	}
	else{
		sprintf(buf,"%d",pid);//why pid???
	}
	FILE *f = fopen(buf, "w+");
	if(!f)
		return -1;
	fprintf(f, "%s", sourceCode);
	fflush(f);
	fclose(f);
	return 0;
}
/*
int main(){
	cake c;
	return 0;
}
*/

