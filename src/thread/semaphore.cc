#include "thread/semaphore.h"
#include "useful/scheduler.h"

/** \todo Implement constructor **/
Semaphore::Semaphore(unsigned int value){
  counter = value;
}


/** \todo Implement method **/
void Semaphore::p(){
  if(counter <= 0)
    scheduler.block(*this);
  else
    --counter;
}

/** \todo Implement method **/
void Semaphore::v(){
  if(counter <= 0 && !empty())
    scheduler.wakeup(dequeue());
  else
    ++counter;
}
