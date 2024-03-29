#include "Judger.h"
#include "Configuration.h"
#include "Sandbox.h"
#include "Compiler.h"
#include "Runner.h"
#include "OutputChecker.h"
#include "Log.h"
#include "RunStruts.h"
#include "util.h"
#include "../common/Packet/JCConnect.h"
#include "../common/Packet/CJConnectReply.h"
#include "../common/Packet/JCJudgeThisReturn.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <assert.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>

using namespace std;
using namespace Network;

int Judger::StartUp()
{
	if(Configuration::GetInstance().Initialize() != 0)
	{
		cerr<<"Can't initialize configuration."<<endl;
		return -1;
	}
    Configuration &conf = Configuration::GetInstance();
	if(_log.Initialize() != 0)
	{
		cerr<<"Log initialization failed."<<endl;
		return -1;
	}
	if(CompilerFactory::GetInstance().Initialize() != 0)
	{
		cerr<<"Compilers initialization failed."<<endl;
		return -1;
	}
	if(RunnerFactory::GetInstance().Initialize() != 0)
	{
		cerr<<"Runner initialization failed."<<endl;
        return -1;
	}
	if(theChecker.Initialize() != 0)
	{
		cerr<<"FileChecker initialization failed."<<endl;
		return -1;
	}
    log(Log::INFO)<<"Connecting to server..."<<endlog;
	if(stream.OpenClientSocket(conf.GetServerIp().c_str(), conf.GetServerPort()) != 0)
	{
		cerr<<"Network initialization failed."<<endl;
		return -1;
	}
    else
    {
        log(Log::INFO)<<"Connected to server.Begin init from server..."<<endlog;
        JCConnect packet;
        try
        {
            SendPacket(&packet);
        }
        catch(NetworkException &e)
        {
            log(Log::CRITICAL)<<"Network error:"<<e.What()<<" Exit."<<endlog;
            return -1;
        }
    }
    idleTime=false;
	return 0;
}

void Judger::CleanUp()
{
    stream.Close();
}
void Judger::CleanTmpFiles(){
  	string src=Configuration::GetInstance().GetSrcFilePath();
  	string dest=Configuration::GetInstance().GetDestFilePath();
	string pout=Configuration::GetInstance().GetProgramOutputPath();
	char tmp[512];
	snprintf(tmp,sizeof(tmp),"rm -rf %s/* %s/* %s/*",src.c_str(),dest.c_str(),pout.c_str());
	//	if(system(tmp)!=0){
	//	log(Log::ERROR)<<"Remove tmp files error"<<endlog;
	//	}
}
int Judger::DoJudge(Cake &ck)
{
    log(Log::INFO)<<"Begin processing run "<<ck.rid<<" "<<endlog;

    JCJudgeThisReturn packet;
    packet.SetRid(ck.rid);
    packet.SetJudgerId(judgerId);

    //phase 1
    if(ck.storeSourceCode(Configuration::GetInstance().GetSrcFilePath().c_str()))
    {
        log(Log::ERROR)<<"Store source code "<<ck.pid<<" failed."<<endlog;
        packet.SetResult(JR_WA);
        SendPacket(&packet);
        CleanTmpFiles();
        return 0;
    }

    //phase 2
    string lan = GetLanName(ck.language);

    Compiler *compiler = CompilerFactory::GetInstance().GetCompiler(lan);
    //log(Log::INFO)<<"The compiler name:"<<compiler->GetName()<<endlog;
    assert(compiler);
    if(!compiler->Compile(ck.rid))
    {
        //mark ce
        packet.SetResult(JR_CE);
        SendPacket(&packet);
        log(Log::INFO)<<"Run "<<ck.rid<<": compilation error."<<endlog;
        CleanTmpFiles();
        return 0;
    }
    //phase 3
    Runner *runner = RunnerFactory::GetInstance().GetRunner(lan);
    assert(runner);

    int result = Runner::OK;
    long timeLimit = ck.timeLimit/*in ms */, memoryLimit = ck.memoryLimit * 1024/* in bytes */;
    if(lan == "java")
    {
        timeLimit *= Configuration::GetInstance().GetJavaTimeFactor();//Loose the limit if Java is used.
        memoryLimit *= Configuration::GetInstance().GetJavaMemoryFactor();
    }
    runner->SetTimeLimit(timeLimit);
    runner->SetMemoryLimit(memoryLimit);
    runner->Run(ck.pid, ck.rid, lan);
    result = runner->GetResult();
    if(result == Runner::SYS_ERROR)
    {
        log(Log::WARNING)<<"Can't run program "<<ck.rid<<". Skip."<<endlog;
        packet.SetResult(JR_RE);
        SendPacket(&packet);

        RunnerFactory::GetInstance().DisposeRunner(runner);
        log(Log::INFO)<<"Run "<<ck.rid<<": runtime error."<<endlog;
        CleanTmpFiles();
        return 0;
    }
    else if(result != Runner::OK)
    {
        //mark this run as re, tle, mle or etc here
        switch(result)
        {
        case Runner::OUTPUT_LIMIT_EXCEEDED:
        	packet.SetResult(JR_OLE);
        	log(Log::INFO)<<"Run "<<ck.rid<<": OLE."<<endlog;
        	break;
        case Runner::RUNTIME_ERROR:
        case Runner::RESTRICTED_SYSCALL:
            packet.SetResult(JR_RE);
            log(Log::INFO)<<"Run "<<ck.rid<<": RE."<<endlog;
            break;
        case Runner::MEMORY_LIMIT_EXCEEDED:
            packet.SetResult(JR_MLE);
            log(Log::INFO)<<"Run "<<ck.rid<<": MLE."<<endlog;
            break;
        case Runner::TIME_LIMIT_EXCEEDED:
            packet.SetResult(JR_TLE);
            log(Log::INFO)<<"Run "<<ck.rid<<": TLE."<<endlog;
            break;
        default:
            packet.SetResult(JR_RE);
            log(Log::WARNING)<<"Unknown run result!"<<result<<endlog;
        }
        SendPacket(&packet);

        RunnerFactory::GetInstance().DisposeRunner(runner);

        CleanTmpFiles();
        return 0;
    }
    RunUsage ru = runner->GetRunUsage();
    RunnerFactory::GetInstance().DisposeRunner(runner);

    //phase 4
    result = theChecker.Check(ck.pid, ck.rid);
    if(result == OutputChecker::FILE_ERROR)
    {
        log(Log::WARNING)<<"Can't check output "<<ck.rid<<" .Skip."<<endlog;
        packet.SetResult(JR_WA);
        SendPacket(&packet);
        log(Log::INFO)<<"Run "<<ck.rid<<": WA."<<endlog;
 
        CleanTmpFiles();
        return 0;
    }
    //mark this run as AC, WA, PE
    packet.SetRtime(ru.time);
    packet.SetRmemory(ru.memory);
    switch(result)
    {
    case OutputChecker::OK:
        packet.SetResult(JR_AC);
        log(Log::INFO)<<"Run "<<ck.rid<<": AC."<<endlog;
        break;
    case OutputChecker::PE:
        packet.SetResult(JR_PE);
        log(Log::INFO)<<"Run "<<ck.rid<<": PE."<<endlog;
        break;
    case OutputChecker::WA:
        packet.SetResult(JR_WA);
        log(Log::INFO)<<"Run "<<ck.rid<<": WA."<<endlog;
        break;
    default:
        log(Log::WARNING)<<"unknown check result."<<endlog;
    }
    SendPacket(&packet);

    CleanTmpFiles();
    return 0;
}

int Judger::Run()
{
    while(!bStopped)
    {
        try
        {
            Loop();
        }
        catch(NetworkException &e)
        {
            log(Log::CRITICAL)<<"Network error:"<<e.What()<<". Exit."<<endlog;
            break;
        }
    }
    return 0;
}

void Judger::Loop()
{
    int fd = stream.GetSocketFd();

    struct timeval tv;
    tv.tv_sec = TIME_PER_TICK / 1000;
    tv.tv_usec = TIME_PER_TICK % 1000 * 1000;

    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);

    int ret;
    if( (ret = select(fd + 1, &rset, NULL, NULL, &tv)) <= 0)
    {
        if(ret == -1)
        {
            if(errno == EINTR)
            {
                log(Log::INFO)<<"Select was interrupt by some signal."<<endlog;
            }
            else
            {
                //usually this meaning programing error
                log(Log::ERROR)<<"Select error!"<<endlog;
                assert(false);
            }
        }
        else//timeout
        {
        	if(!idleTime){
	            log(Log::INFO)<<"Idle loop..."<<endlog;
	            idleTime=true;
	        }
        }
        return;
    }
    idleTime=false;
    if(FD_ISSET(fd, &rset))
    {
        Packet *packet = ReceivePacket();
        if(!packet)
        {
            //now won't reach here
            log(Log::INFO)<<"Something comes but is not a complete packet!.Exiting..."<<endlog;
            //here continue running is meaningless
            return;
        }
        if(judgerId == -1)//expecting cjconnect reply
        {
            if(packet->GetPacketType() != CJ_CONNECT_REPLY_PACKET)
            {
                log(Log::CRITICAL)<<"Expect CJ_CONNECT_REPLY_PACKET but comes "<<packet->GetPacketType()<<endlog;
                assert(false);
            }
            else
            {
                packet->Execute(this);
                log(Log::INFO)<<"Initialization complete.My judger id is "<<judgerId<<endlog;
            }
        }
        else
        {
            log(Log::INFO)<<"A new packet received.PacketType="<<packet->GetPacketType()<<endlog;
            packet->Execute(this);
        }
        delete packet;
    }
    else
    {
        log(Log::WARNING)<<"Some socket was ready but is not expected!"<<endlog;
        assert(false);
    }
    //do something else
}

int Judger::SendPacket(Packet *packet)
{
    assert(packet);

    packet->Write(stream);
    log(Log::INFO)<<"Judger::SendPacket Sent packet (type = "<<packet->GetPacketType()<<") successfully."<<endlog;
    return 0;
}

Packet *Judger::ReceivePacket()
{
    int ret, type;
    Packet *packet = NULL;

    if((ret = stream.PeekInt(type)) != sizeof(int) || type < 0 || type >= MAX_PACKET_ID)
    {
        if(ret == 0)
        {
            log(Log::INFO)<<"Server closed connection.Exiting..."<<endlog;
            exit(0);
        }
        else
        {
            log(Log::ERROR)<<"Judger::ReceivePacket Error "<<strerror(errno)<<endlog;
            assert(false);
        }
        //can't continue
    }
    else
    {
        packet = PacketFactoryManager::GetInstance().GetPacketFactory(type)->GetPacket();
        assert(packet);

        packet->Read(stream);
        log(Log::INFO)<<"Judger::ReceivePacket Packet (type = "<<type<<") received successfully."<<endlog;
    }
    return packet;
}
