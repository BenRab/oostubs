/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          P A N I C                                            * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __lock_header__
#define __lock_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "useful/cpu.h"
#include "useful/log.h"
#include "thread/thread.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * \~english
 * \brief Global interrupt lock
 *
 * This class represent a global interrupt lock to synchronize critical sections. It disables all interrupts on creation until it is destroyed or the asymmetricUnlock function is called. The asymmetricUnlock function is a bypass for specific situations in which a created lock will never be destroyed because the scope it was defined in never ends. Therefore this method may only be called by the kickoff function of Thread.
 **/
class Lock
{
    private:
        /**
         * \~english
         * \brief Interrupt state on entry
         *
         * The original state on lock entry needs to be saved to restore it on
         * destruction of the lock.
         *
         **/
        static bool origState;
            
       /**
        * \~english
        * \brief %Lock entry state
        *
        * The entry state is only kept for debugging purposes to detect invalid
        * double locks or double unlocks.
        *
        **/
        static bool entryState;
    public:
        /**
         * \~english
         * \brief %Lock creation
         *
         * On lock creation the current interrupt enable state is saved and the interrupt are globally disabled.
         * Additionally the entryState variable is checked for double locks and afterwards set to true.
         **/
        Lock()
        {
            origState=cpu.disable_int();
            if(entryState)
                log << "Locking error: double lock" << std::endl;
            entryState=true;
        }

        /**
         * \~english
         * \brief %Lock destruction
         *
         * On lock destruction the saved interrupt state is restored and the
         * entryState variable is checked for double unlocks.
         *
         **/
        ~Lock()
        {
            asymmetricUnlock();
        }

    private:
        /**
         * \~english
         * \brief Explicit unlocking in asymmetric contexts.
         *
         * Unlocks the lock like the destructor would do, but it explicitely
         * called in kickoff of Thread to support the inherent asymmetry of the
         * threads.
         *
         **/
        static void asymmetricUnlock()
        {
            if(!entryState)
                log << "Locking error: double unlock" << std::endl;
            entryState=false;
            if(origState)
                cpu.enable_int();
        }
    friend void Thread::kickoff(Thread*);
};

#endif
