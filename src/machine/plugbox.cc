/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                         P L U G B O X                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/plugbox.h"
#include "useful/panic.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

Plugbox::Plugbox(){
  //Var init
  unsigned int i;
  
  i=0;
  while(i<uiGateCount){
    gates[i] = &panic;
    i++;
  }
}

void Plugbox::assign(unsigned short slot, Gate& gate){
  //ubergebene Slotnummer sollte krorekt sein
  if(slot<uiGateCount){
    gates[slot] = &gate;
  }
}

Gate& Plugbox::report(unsigned short slot){
  //ubergebene Slotnummer sollte krorekt sein
  if(slot<uiGateCount){
    return *(gates[slot]);
  }else{
    return panic;
  }
}
