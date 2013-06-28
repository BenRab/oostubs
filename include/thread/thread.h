/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          T H R E A D                                          * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __thread_include__
#define __thread_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include <ucontext.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/**
 *  \~english
 *  \brief Basic multitasking entity.  
 *
 *  Threads are the entities of scheduling. They are either part of the queue
 *  of threads ready for execution, blocked by a specific semaphore or currently
 *  running. This class defines the needed data structure to represent the
 *  context of a single thread(thread specific stack and thread control block).
 *  Additionally a C function is defined to help initiating the thread specific
 *  action.
 *
 **/
class Thread {

  private:
    /**
     * \~english
     * \brief Local 1MB stack of this thread.
     **/
    unsigned char stack[1024*1024];

    /**
     * \~english
     * \brief %Thread control block in linux specific format.
     **/
    ucontext_t context;

    /**
     * \~english
     * \brief Kickoff function to initiate thread action.
     * \param thread the thread to be started
     **/
    static void kickoff(Thread* thread);

  public:
  /**
   * \~english
   * \brief Default constructor.
   *
   * Initializes the thread control block.
   **/
  Thread();

  /**
   * \~english
   * \brief Destructor.
   *
   * Terminates the execution of this thread.
   **/
  ~Thread();

  /**
   * \~english
   * \brief Resume execution with another ready thread.
   *
   * This method forwards the call to the global scheduler.
   **/
  void resume();

  /**
   * \~english
   * \brief Terminate execution of this thread.
   *
   * This method forwards the call to the global scheduler
   **/
  void exit();

  /**
   * \~english
   * \brief %Thread specific task method.
   *
   * This method needs to be overwritten by an application inheriting from Thread.
   **/
  virtual void action() =0;

  friend class Dispatcher;
  friend class Lock;
};

#endif
