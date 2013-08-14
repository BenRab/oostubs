#include "user/task4.h"
#include "thread/lock.h"
#include "useful/kout.h"
#include "useful/keyboard.h"
#include "useful/scheduler.h"
#include "useful/cpu.h"
#include "useful/log.h"

Task4::RotCursor::RotCursor(unsigned short x, unsigned short y) : i(0), x(x), y(y), coop(false){}

void Task4::RotCursor::action(){
	while(true)
	{
        {
            Lock lock;
		    kout.flush();
		    kout.setpos(x, y);
		    switch(i++%4)
		    {
                case(0):	kout << '|';
                            break;
                case(1):	kout << '/';
                            break;	
                case(2):	kout << '-';
                            break;
                case(3):	kout << '\\';
                            break;
            }
		    kout.flush();
        }
        if(coop)
            resume();
	}
}

Task4::Counter::Counter(unsigned short x, unsigned short y) : i(0), x(x), y(y), coop(false){}

void Task4::Counter::action(){
	while(true)
	{
        {
		    Lock lock;
		    kout.flush();
		    kout.setpos(x, y);
		    kout << "Counter: " << i++ << endl;
        }
        if(coop)
            resume();
	}
}

Task4::Task4(bool coop) : coop(coop),
                 rotCursor(rotCursorX, rotCursorY),
				 counter1(counter1X, counter1Y),
				 counter2(counter2X, counter2Y){
}

void Task4::action(){
    kout.clear();
	kout.setpos(31,1);
	kout << "OOStuBs - Task 4" << endl << endl;
    if(coop)
    {
        rotCursor.enableCoop();
        counter1.enableCoop();
        counter2.enableCoop();
    }
    scheduler.ready(rotCursor);
	scheduler.ready(counter1);
	scheduler.ready(counter2);
    cpu.enable_int();
}
