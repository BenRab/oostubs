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
#include "useful/kout.h"

extern PIC pic;
extern Plugbox plugbox;
extern unsigned int globalTaskChoice;

/** \todo \~german implementieren \~english write implementation */
Keyboard::Keyboard(){
}

/** \todo \~german implementieren \~english write implementation */
void Keyboard::plugin(){
  plugbox.assign(PIC::keyboard + 32, *this); 
  pic.allow(PIC::keyboard);
}

/** \todo \~german implementieren \~english write implementation */
void Keyboard::trigger(){
  //Interreupt-Behandlung, schreibe Zeichen an bestimmte Stelle
  Key k = key_hit();
  unsigned short x;
  unsigned short y;

  //Strg+Alt+Entf -> Neustart
  if(k.valid() && k.alt() && k.ctrl() && k.scancode() == 0x53)//k.scan.del)
  {
    reboot();
  }
  //Alt+1 -> globalTaskChoice = 1 
  else if(k.valid() && k.alt() && k.scancode() == 2)
  {
    globalTaskChoice = 1;
  }
  //Alt+2 -> globalTaskChoice = 2
  else if(k.valid() && k.alt() && k.scancode() == 3)
  {
    globalTaskChoice = 2;
  }
  else if(k.valid())
  {
   /* kout.flush();
    kout.getpos(x, y);
    kout.setpos(0, 10);
    kout << k;
    kout.flush();
    kout.setpos(x, y);*/
  }
}



