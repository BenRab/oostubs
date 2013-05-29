/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 B                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/task3B.h"

#include "useful/kout.h"
#include "useful/cpu.h"
#include "useful/keyboard.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                     EXTERNS                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void gotoAnalyse(void);

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL VARIABLES                 #
\* * * * * * * * * * * * * * * * * * * * * * * * */
bool bFirstOccurance=true;

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    FUNCTIONS                    #
\* * * * * * * * * * * * * * * * * * * * * * * * */
Task3B::Task3B() : Application(){
  kout.setpos(31,1);
  kout << "OOStuBs - Task 3B" << endl << endl;
  
  keyboard.plugin();
  cpu.enable_int();
}

Task3B::~Task3B(){
  
  cpu.disable_int();
}

unsigned int alphaAckermann(unsigned int a, unsigned int n){
  if(n==0){
    if(bFirstOccurance){
      gotoAnalyse();
      bFirstOccurance = false;
    }
    return 0;
  }else if(n==1){
    return 1;
  }
  
  return a;
}

unsigned int doAckermann(unsigned int a, unsigned int b, unsigned int n){
  if(n==0){
    return a+b;
  }else if(b==0){
    return alphaAckermann(a,n-1);
  }
  
  return doAckermann(a, doAckermann(a, b-1, n), n-1);
}

void outputAckermannResult(unsigned int x, unsigned int y, unsigned int n, unsigned int uRes){
  kout << "doAckermann(" << x << ", " << y << ", " << n << ")=" << uRes << endl;
}

void doTask3BAction(unsigned int* ende){
  unsigned int x, y, n;
  
  x=9*(ende[1]/0x11111111); //damit keine "unused variable ende"-Warnung kommt
  y=2;
  n=2;
  
  outputAckermannResult(x, y, n, doAckermann(x,y,n));
}

/**
 * 
 * 
 * 
 */
void Task3B::action(){
  //Var init
  unsigned int ende[]={0xEEEEEEEE, 0x11111111, 0xDDDDDDDD, 0xEEEEEEEE};
  
  bFirstOccurance = true;
  doTask3BAction(ende);
}
