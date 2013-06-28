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
#include "device/curskbd.h"
#include "useful/plugbox.h"
#include "useful/pic.h"
#include "useful/kout.h"
#include <pthread.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL OBJECTS                   #
\* * * * * * * * * * * * * * * * * * * * * * * * */

extern pthread_mutex_t keyMutex;
extern volatile unsigned int keyBuffer;
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */
Curses_Keyboard::Curses_Keyboard() : Gate(){

}

void Curses_Keyboard::plugin(){
  plugbox.assign(Plugbox::keyboard, *this);
  pic.allow(Software_PIC::keyboard);
}

Key Curses_Keyboard::key_hit()
{
    pthread_mutex_lock(&keyMutex);
    unsigned int temp=keyBuffer;
    keyBuffer=0;
    pthread_mutex_unlock(&keyMutex);
    return Key(temp);
}

void Curses_Keyboard::trigger()
{
    kout.flush();
    kout.setpos(4,10);
    kout << key_hit();
    kout.flush();
}
