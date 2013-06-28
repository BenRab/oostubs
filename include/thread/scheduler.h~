/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "thread/thread.h"
#include <deque>
 
/**
 * \~english
 * \brief Basic Scheduler
 *  
 * This class represent a simple FIFO-Scheduler. It holds a list of the
 * currently available threads. Through the \ref Scheduler::resume method it
 * can issue a context switch to another ready thread. The resulting context
 * switch may also switch to the same thread if the ready list is empty.
 *
 **/
class Scheduler : protected Dispatcher {
private:
  /** 
   * \~english 
   * \brief Queue of threads that are ready to be processed 
   **/
    std::deque<Thread*> threads;
  /**
   * \~english
   * \brief Type definition of thread iterator
   **/
    typedef std::deque<Thread*>::iterator ThreadIterator;

public:
  /** \brief Start the scheduling by starting the first thread of the system
   * 
   * \param first The first thread of the system
   **/ 
	void schedule(Thread& first);
  
  /** \brief Insert the specified thread into the queue
   *
   * of threads that are ready to be processed.
   *
   * @param that reference to the thread to be inserted
   **/
  void ready(Thread& that);

  /** \brief Remove the currently active thread from the queue
   *
   * of thread and resumes with the next thread. If there are no
   * more threads the scheduler starts an idle loop.
   **/
  void exit();

  /** \brief Remove the specified thread from the queue of processes.
   *
   * @param that reference of the thread to be killed.
   */
  void kill(Thread& that);

  /** \brief Use the scheduling algorithm to get the next thread and
   * resumes with that thread.
   **/
  void resume();
};

#endif
