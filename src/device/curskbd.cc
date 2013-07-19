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
#include "thread/lock.h"
#include <pthread.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL OBJECTS                   #
\* * * * * * * * * * * * * * * * * * * * * * * * */

extern pthread_mutex_t keyMutex;
extern volatile unsigned int keyBuffer;
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */
Curses_Keyboard::Curses_Keyboard() : Gate(), sem(0){

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
    {
        Lock lock;
        buffer.push_back(key_hit());
    }
    sem.signal();
}

Key Curses_Keyboard::getkey()
{
    sem.wait();
    Lock lock;
    Key k=buffer.front();
    buffer.pop_front();
    return k;
}
