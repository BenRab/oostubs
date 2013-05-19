/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"
#include "machine/key.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

//extern CGA_Stream kout;
extern PIC pic;
extern Plugbox plugbox;

/** \todo \~german implementieren \~english write implementation */
//Keyboard::Keyboard(){
//}

/** \todo \~german implementieren \~english write implementation */
void Keyboard::plugin(){
  length = 0;
  plugbox.assign(gateInterruptNumber, *this); 
  pic.allow(PIC::keyboard);
}

/** \todo \~german implementieren \~english write implementation */
void Keyboard::trigger(){
  //Interreupt-Behandlung, schreibe Zeichen an bestimmte Stelle
}
