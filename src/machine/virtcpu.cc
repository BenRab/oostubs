#include "machine/virtcpu.h"
#include <pthread.h>

bool Virtual_CPU::enable_int () {
        bool oldState=state;
        state=true;
        pthread_sigmask(SIG_SETMASK, &pic.enabledSet, NULL);        
        return oldState;
    }

bool Virtual_CPU::disable_int () {
        bool oldState=state;
        state=false;
        pthread_sigmask(SIG_SETMASK, &pic.disabledSet, NULL);
        return oldState;
    }

void Virtual_CPU::halt()
{
    sigset_t set;
    pthread_sigmask(SIG_UNBLOCK, NULL, &set);
    sigsuspend(&set);
}
