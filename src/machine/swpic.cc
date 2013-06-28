#include "machine/swpic.h"

#include <signal.h>
#include <stdlib.h>

Software_PIC::Software_PIC()
{
    sigemptyset(&enabledSet);
    sigfillset(&enabledSet);
    sigdelset(&enabledSet, SIGSEGV);
    sigfillset(&disabledSet);
    sigdelset(&disabledSet, SIGSEGV);
}

Software_PIC::~Software_PIC(){}

void Software_PIC::allow(Interrupts interrupt)
{
    sigdelset(&enabledSet, SIGRTMIN+interrupt);
    sigaddset(&disabledSet, SIGRTMIN+interrupt);
}

void Software_PIC::forbid(Interrupts interrupt)
{
    sigaddset(&enabledSet, SIGRTMIN+interrupt);
    sigdelset(&disabledSet, SIGRTMIN+interrupt);
}

unsigned char Software_PIC::getISR(bool secondPic)
{
    sigset_t curSet;
    sigpending(&curSet);
    unsigned short res=0;
    for(int sig=SIGRTMIN+(secondPic?8:0);sig<SIGRTMIN+(secondPic?16:8);sig++)
    {
        res|=(sigismember(&curSet, sig)?0x100:0);
        res>>=1;
    }

    return res;
}
