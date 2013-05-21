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

/** \todo \~german implementieren \~english write implementation*/
Plugbox::Plugbox(){
  for(int i=0; i<256; i++){
    interruptArray[i] = &panic;
  }
}

/** \todo \~german implementieren \~english write implementation*/
void Plugbox::assign(unsigned short slot, Gate& gate){
  if(slot >= 0 && slot < 256){
    interruptArray[slot] = &gate;
  } 
}

/** \todo \~german implementieren \~english write implementation*/
Gate& Plugbox::report(unsigned short slot){
  if(slot >= 0 && slot < 256){
    return *interruptArray[slot];
  }

  return panic;
}
