#include "connection.h"
#include "Log.h"
#include "Configuration.h"
#include <cstring>
#include <iostream>

int s2n(char x[]){
	int y=0;
	for(unsigned int i=0;i<strlen(x);i++){
		y=y*10+x[i]-'0';
	}
	return y;
}
int Connection::fetchCake(Cake& x){
	if(!initialed)return 1;
	if(mysql_query(conn,"select rid,pid,judgeStatus,language,sourceCode,uid from status where judgeStatus=1 order by rid")){
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 1;
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL){
		return 2;
	};
	x.setRid(s2n(row[0]));
	x.setPid(s2n(row[1]));
	x.setJudgeStatus(s2n(row[2]));
	x.setLanguage(s2n(row[3]));
	x.setSourceCode(row[4]);
	x.setUid(s2n(row[5]));
	mysql_free_result(res);
	char tmp[100];
	sprintf(tmp,"select timeLimit,memoryLimit,accepted from problem where pid=%d",x.getPid());
	//printf("%s\n",tmp);
	if(mysql_query(conn,tmp)){
		log(Log::WARNING)<<mysql_error(conn)<<endlog;
		return 1;
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL){
		log(Log::WARNING)<<"The problem doesn't exist!"<<endlog;
		return 3;
	}
	x.setTimeLimit(s2n(row[0]));
	x.setMemoryLimit(s2n(row[1]));
	x.setProblemAccepted(s2n(row[2]));
	mysql_free_result(res);
	sprintf(tmp,"select accepted from user where uid=%d",x.getUid());
	if(mysql_query(conn,tmp)){
		log(Log::WARNING)<<mysql_error(conn)<<endlog;
		return 1;
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL){
		log(Log::WARNING)<<"The user doesn't exist!"<<endlog;
		return 4;
	}
	x.setUserAccepted(s2n(row[0]));
	mysql_free_result(res);
	return 0;
}
int Connection::init(){
if(mysql_server_init(0,0,0)){
		fprintf(stderr,"Database initialisation error.\n");
		return 1;
	}
	conn=mysql_init(NULL);
	Configuration &conf = Configuration::GetInstance();
	if(!mysql_real_connect(conn,conf.GetDbHost().c_str(),conf.GetDbUsername().c_str()
				,conf.GetDbPassword().c_str(),conf.GetDbDatabase().c_str(),0,NULL,0)){
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 1;
	}
	initialed=1;
	return 0;	
}
void Connection::close(){
	mysql_close(conn);
	mysql_server_end();
}

int Connection::updateCake(const Cake &x)
{
	if(!initialed)return 1;
	char tmp[100];
	sprintf(tmp,"update status set judgeStatus=%d where rid=%d",x.getJudgeStatus(),x.getRid());
	if(mysql_query(conn,tmp)){
		log(Log::WARNING)<<mysql_error(conn)<<endlog;
		return 1;
	}
	//int acceptedPro,submittedPro;
	int result=x.getJudgeStatus();
	if(result==3||result==4||result==8){//The code has been AC,or WA, or PE
		sprintf(tmp,"update status set rtime=%d,rmemory=%d where rid=%d",x.getRtime(),x.getRmemory(),x.getRid());
		if(mysql_query(conn,tmp)){
			log(Log::WARNING)<<mysql_error(conn)<<endlog;
			return 1;
		}
	}
	if(result==3){//The code has been accpeted!
		sprintf(tmp,"update problem set accepted=%d where pid=%d",x.getProblemAccepted()+1,x.getPid());
		if(mysql_query(conn,tmp)){
			log(Log::WARNING)<<mysql_error(conn)<<endlog;
			return 1;
		}
		sprintf(tmp,"update user set accepted=%d where uid=%d",x.getUserAccepted()+1,x.getUid());
		if(mysql_query(conn,tmp)){
			log(Log::WARNING)<<mysql_error(conn)<<endlog;
			return 1;
		}
	}
	/*
	else{//The code has been rejected!
		sprintf(tmp,"update problem set accepted=%d where pid=%d",x.getProblemAccepted(),x.getPid());
		if(mysql_query(conn,tmp)){
			log(Log::WARNING)<<mysql_error(conn)<<endlog;
			return 1;
		}
		sprintf(tmp,"update user set accepted=%d where uid=%d",x.getUserAccepted(),x.getUid());
		if(mysql_query(conn,tmp)){
			log(Log::WARNING)<<mysql_error(conn)<<endlog;
			return 1;
		}
	}*/
	return 0;
}
