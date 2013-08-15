/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
* Technische Informatik II *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* *
* S C H E D U L E R *
* *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
# INCLUDES #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/scheduler.h"
#include "thread/lock.h"
#include "thread/idle.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
# METHODS #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/**\~english \todo implement**/
void Scheduler::schedule(Thread& first){
  ready(first);
  go(first);
}

/**\~english \todo implement**/
void Scheduler::ready(Thread& that){
  Lock lock;
  threads.push_back(&that);
}

/**\~english \todo implement**/
void Scheduler::exit(){
  kill(*active());
}

/**\~english \todo implement**/
void Scheduler::kill(Thread& that){
  if(threads.empty())
    return;

  ThreadIterator it = threads.begin();

  while (it != threads.end() && *it != &that) 
  {	
    it++;
  } 
  if(*it == &that) 
  {
    Lock lock;
    threads.erase(it);
  }

  if(active() == &that)
  {
    resume();
  }
}

IdleThread idle;

/**\~english \todo implement**/
void Scheduler::resume(){
  Thread* next;
  {
    Lock lock;

    if(threads.empty())
    {
      next = &idle;
    }
    else 
    {
      next = threads.front();
      threads.pop_front();
      threads.push_back(next);
    }
  }
  dispatch(*next);
}
