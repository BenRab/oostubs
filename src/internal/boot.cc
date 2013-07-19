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

#define SIG_CLK SIGRTMIN
#define SIG_KBD SIGRTMIN+1

sigset_t errorSet;

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
        sigfillset(&errorSet);
        sigdelset(&errorSet, SIGILL);
        sigdelset(&errorSet, SIGBUS);
        sigdelset(&errorSet, SIGSEGV);
    }

    ~System()
    {
        echo();
        nocbreak();
        endwin();
    }

    static void* callKernel(void* arg)
    {
        pthread_sigmask(SIG_BLOCK, &errorSet, NULL);
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
        pthread_sigmask(SIG_BLOCK, &errorSet, NULL);
        pthread_cancel(os);
        pthread_join(os, NULL);
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
            pthread_sigmask(SIG_BLOCK, &errorSet, NULL);
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
            pthread_sigmask(SIG_BLOCK, &errorSet, NULL);
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

sig_atomic_t gotSig=0;

void handleErrorSig(int sig)
{
  if(gotSig)
  {
    endwin();
    nocbreak();
    echo();
    _exit(sig);
  }
  else
    gotSig=sig;
}

void handleInts(int signum, siginfo_t* info, void* context)
{
    if(signum>=SIGRTMIN && signum<=SIGRTMAX)
        guardian(info->si_value.sival_int);
}

int main()
{
    struct sigaction intAction;
    struct sigaction errorAction;
    sigset_t rtSet;

    sigemptyset(&rtSet);
    sigaddset(&rtSet, SIG_CLK);
    sigaddset(&rtSet, SIG_KBD);

    sigfillset(&errorSet);
    sigdelset(&errorSet, SIGILL);
    sigdelset(&errorSet, SIGSEGV);
    sigdelset(&errorSet, SIGBUS);

    memset(&errorAction, 0, sizeof(errorAction));
    errorAction.sa_handler=&handleErrorSig;
    errorAction.sa_flags=0;
    errorAction.sa_mask=rtSet;
    sigaction(SIGSEGV, &errorAction, NULL);
    sigaction(SIGINT , &errorAction, NULL);
    sigaction(SIGABRT, &errorAction, NULL);
    sigaction(SIGTERM, &errorAction, NULL);
    sigaction(SIGQUIT, &errorAction, NULL);
    sigaction(SIGHUP , &errorAction, NULL);
    sigaction(SIGILL , &errorAction, NULL);

    memset(&intAction, 0, sizeof(intAction));
    intAction.sa_sigaction=&handleInts;
    intAction.sa_flags=SA_SIGINFO;
    sigaction(SIG_CLK, &intAction, NULL);
    sigaction(SIG_KBD, &intAction, NULL);


    pthread_sigmask(SIG_BLOCK, &rtSet, NULL);

    os.start();
    clk.start();
    kbd.start();
    sigsuspend(&rtSet);

    log << "Got signal: " << strsignal(gotSig) << "(" << gotSig << ")" << endl;
    log << "Terminating OS" << endl;
    clk.stop();
    kbd.stop();
    os.stop();

    log << "OS terminated correctly" << endl;

    return gotSig;
}
