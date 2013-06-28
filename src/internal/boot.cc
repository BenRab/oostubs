#include "machine/key.h"
#include "useful/pic.h"
#include "useful/cpu.h"
#include "object/log.h"


#include <sstream>
#include <iostream>
#include <pthread.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <sys/time.h>
#include <errno.h>

using namespace std;

Log log;
/**
 * \~english
 * \brief Internal global variable containing the last pressed key, that was net delivered to the keyboard driver.**/
volatile unsigned int keyBuffer;
/**
 * \~english
 * \brief Internal global variable containing the current clock period length in us
 **/
volatile unsigned int rrTimeSlice;

pthread_mutex_t keyMutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tsMutex=PTHREAD_MUTEX_INITIALIZER;

extern void kernel();
extern void guardian(unsigned short slot);

class System
{
  private:
    pthread_t os;
  public:
    System()
    {
        initscr();
        noecho();
        cbreak();
    }

    ~System()
    {
        echo();
        nocbreak();
        endwin();
    }

    static void* callKernel(void* arg)
    {
        sigset_t segfaultSet;
        sigfillset(&segfaultSet);
        sigdelset(&segfaultSet, SIGSEGV);
        pthread_sigmask(SIG_BLOCK, &segfaultSet, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        kernel();
        return NULL;
    }

    void start()
    {
        log << "Starting OS" << endl;
        pthread_create(&os, NULL, &System::callKernel, NULL);  
    }

    void signal(unsigned short interrupt, unsigned short exception)
    {
        union sigval value;
        value.sival_int=exception;
        pthread_sigqueue(os, SIGRTMIN+interrupt, value);
    }

    void stop()
    {
        sigset_t segfaultSet;
        sigfillset(&segfaultSet);
        sigdelset(&segfaultSet, SIGSEGV);
        pthread_sigmask(SIG_BLOCK, &segfaultSet, NULL);
        pthread_cancel(os);
        pthread_join(os, NULL);
        endwin();
    }
};

static System os;

class KeyboardEmulation
{
    pthread_t thread;
    static unsigned short interrupt, exception;

    public:
        KeyboardEmulation(unsigned short interrupt, unsigned short exception)
        {
            KeyboardEmulation::interrupt=interrupt;
            KeyboardEmulation::exception=exception;
        }

        void start()
        {
            log << "Starting Keyboard Emulation" << endl;
            pthread_create(&thread, NULL, &KeyboardEmulation::action, NULL);
        }

        void stop()
        {
            log << "Stopping Keyboard Emulation" << endl;
            pthread_cancel(thread);
            pthread_join(thread, NULL);
        }

        static void* action(void* arg)
        {
            sigset_t all;
            sigfillset(&all);
            pthread_sigmask(SIG_BLOCK, &all, NULL);
            while(true)
            {
                int key = getch();
                if(key!=ERR)
                {
                    pthread_mutex_lock(&keyMutex);
                    keyBuffer=key;
                    pthread_mutex_unlock(&keyMutex);
                    os.signal(interrupt, exception);
                }
            }

            return NULL;
        }
};

unsigned short KeyboardEmulation::interrupt;
unsigned short KeyboardEmulation::exception;

static KeyboardEmulation kbd(1,33);

class ClockEmulation
{
    pthread_t thread;
    static unsigned short interrupt, exception;

    public:
        ClockEmulation(unsigned short interrupt, unsigned short exception)
        {
            ClockEmulation::interrupt=interrupt;
            ClockEmulation::exception=exception;            
            rrTimeSlice = 1000000;
        }

        void start()
        {
            log << "Starting Timer Emulation" << endl;
            pthread_create(&thread, NULL, &ClockEmulation::action, NULL);
        }

        void stop()
        {
            log << "Stopping Timer Emulation" << endl;
            pthread_cancel(thread);
            pthread_join(thread, NULL);
        }

        static void* action(void* arg)
        {
            sigset_t all;
            sigfillset(&all);
            pthread_sigmask(SIG_BLOCK, &all, NULL);
            while(true)
            {
                pthread_mutex_lock(&tsMutex);
                unsigned int localBuffer=rrTimeSlice;
                pthread_mutex_unlock(&tsMutex);
                usleep(localBuffer);

                os.signal(interrupt, exception);
            }

            return NULL;
        }

};

unsigned short ClockEmulation::interrupt;
unsigned short ClockEmulation::exception;

static ClockEmulation clk(0, 32);

void handleMultiSig(int sig)
{
    endwin();
    echo();
    nocbreak();
    log << "Got multiple signals: " << strsignal(sig) << "(" << sig << ")" << endl;
    log << "Hard killing OS" << endl;
    _exit(sig);
}

void handleSegfault(int sig)
{
    os.stop();
    handleMultiSig(sig);
}

void handleInts(int signum, siginfo_t* info, void* context)
{
    if(signum>=SIGRTMIN && signum<=SIGRTMAX)
        guardian(info->si_value.sival_int);
}

int main()
{
    struct sigaction intAction;
    sigset_t errorSet;

    signal(SIGSEGV, &handleSegfault);
    signal(SIGINT , &handleMultiSig);
    signal(SIGABRT, &handleMultiSig);
    signal(SIGSEGV, &handleMultiSig);
    signal(SIGTERM, &handleMultiSig);

    sigfillset(&errorSet);
    pthread_sigmask(SIG_BLOCK, &errorSet, NULL);

    memset(&intAction, 0, sizeof(intAction));
    intAction.sa_sigaction=&handleInts;
    intAction.sa_flags=SA_SIGINFO | SA_RESTART;
    sigaction(SIGRTMIN, &intAction, NULL);
    sigaction(SIGRTMIN+1, &intAction, NULL);

    sigdelset(&errorSet, SIGRTMIN);
    sigdelset(&errorSet, SIGRTMIN+1);
    int sig;

    os.start();
    clk.start();
    kbd.start();
    sigwait(&errorSet, &sig);
    pthread_sigmask(SIG_UNBLOCK, &errorSet, NULL);

    log << "Got signal: " << strsignal(sig) << "(" << sig << ")" << endl;
    log << "Terminating OS" << endl;
    clk.stop();
    kbd.stop();
    os.stop();

    log << "OS terminated correctly" << endl;

    return sig;
}
