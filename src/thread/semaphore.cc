#include "thread/semaphore.h"
#include "useful/scheduler.h"

/** \todo Implement constructor **/
Semaphore::Semaphore(unsigned int value){
}


/** \todo Implement method **/
void Semaphore::p(){
  --counter;
  
  if(counter < 0)
	scheduler.block(*this);
}

/** \todo Implement method **/
void Semaphore::v(){
  ++counter;

  if(counter <= 0)
  {
	scheduler.wakeup(dequeue());
  }
}
