#include "user/task5.h"

#include "useful/keyboard.h"
#include "useful/kout.h"
#include "useful/scheduler.h"
#include "thread/lock.h"
#include "useful/cpu.h"

void Task5::Cmd::action(){

  unsigned short tempX,tempY;
  while(true)
  {
    {
      Lock lock;
      kout.clear();
      buffer.clear();
      kout.flush();
      kout.setpos(x, y);
      kout << "oostubs:$ ";
      kout.flush();
      kout.getpos(tempX, tempY);
    }
    while(true)
    {
      Key k=keyboard.getkey();
      Lock lock;
      kout.setpos(tempX, tempY);
      if(k.ascii()=='\n')
        break;
      else
      {
        buffer.push_back(k.ascii());
        kout << k.ascii();
        kout.flush();
      }
      kout.getpos(tempX, tempY);

    }
	  parseBuffer();
    keyboard.getkey();
  }
}

void Task5::Cmd::registerApp(Application& app, const char* name){
    apps[name]=&app;
    appState[name]=false;
}

void Task5::Cmd::parseBuffer(){
    std::size_t argPos;
    argPos = buffer.find("start");
    if(argPos != std::string::npos)
    {
        handleCommand(start, argPos+sizeof("start"));
        return;
    }
    argPos = buffer.find("stop");
    if(argPos != std::string::npos)
    {
        handleCommand(stop, argPos+sizeof("stop"));
        return;
    }
    argPos = buffer.find("list");
    if(argPos != std::string::npos)
    {
        handleCommand(list, argPos+sizeof("list"));
        return;
    }
    handleCommand(help, argPos);
}

void Task5::Cmd::handleCommand(Commands cmd, std::size_t argPos)
{
    switch(cmd)
    {
        case(start): return startApp(argPos);
        case(stop) : return stopApp(argPos);
        case(list) : return listApps();
        case(help) : return printHelp();
    }
}

bool Task5::Cmd::parseApp(std::size_t argPos, ApplicationIterator& i, ExecutionIterator& j){
  i = apps.find(buffer.substr(argPos));
  j = appState.find(buffer.substr(argPos));
  return (i!=apps.end() && j!=appState.end());
}

void Task5::Cmd::startApp(std::size_t argPos){
   ApplicationIterator i;
   ExecutionIterator j;
   if(parseApp(argPos, i, j))
       if(!j->second)
       {
           scheduler.ready(*i->second);
           j->second=true;
       }
}

void Task5::Cmd::stopApp(std::size_t argPos){
   ApplicationIterator i;
   ExecutionIterator j;
   if(parseApp(argPos, i, j))
       if(j->second)
       {
           scheduler.kill(*i->second);
           j->second=false;
       }
}

void Task5::Cmd::listApps(){
    Lock lock;
    kout << endl;
    for(ApplicationIterator i=apps.begin(); i!=apps.end();i++)
        kout << i->first.c_str() << " ";
    kout << endl;
}

void Task5::Cmd::printHelp()
{
    Lock lock;
    kout << endl;
    kout << "start <app name> : starts the given application" << endl;
    kout << "stop <app name>  : stops the given application" << endl;
    kout << "list             : list all available applications" << endl;
    kout << "help             : output this help" << endl;
}

Task5::Task5() : Task4(false), cmd(cmdX, cmdY){

}

void Task5::action(){
 	kout.clear();
	kout.setpos(31,1);
	kout << "OOStuBs - Task 5" << endl << endl;
  	cmd.registerApp(counter1, "Counter-1");
  	cmd.registerApp(counter2, "Counter-2");
  	cmd.registerApp(rotCursor, "Rotating-Cursor");
	scheduler.ready(cmd);
  	cpu.enable_int();
}
