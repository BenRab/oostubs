/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         M A I N                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/virtcpu.h"
#include "machine/swpic.h"
#include "machine/plugbox.h"
#include "device/curskbd.h"
#include "device/cursstr.h"
#include "device/panic.h"
#include "device/watch.h"
#include "thread/organizer.h"
#include "user/task5.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL OBJECTS                   #
\* * * * * * * * * * * * * * * * * * * * * * * * */
unsigned int uiSpuriousInterruptCount;

Virtual_CPU     cpu;
Software_PIC    pic;
Panic           panic;
Plugbox         plugbox;
Curses_Stream   kout;
Curses_Keyboard keyboard;
Organizer       scheduler;
Watch           watch(10000);
Task5           task;


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** \brief kernel entry point
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 **/
void kernel(){

  keyboard.plugin();
  watch.windup();

  scheduler.schedule(task);
}
