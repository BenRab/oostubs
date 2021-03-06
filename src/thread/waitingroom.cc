#include "thread/waitingroom.h"
#include "thread/lock.h"
#include "useful/scheduler.h"

/** \todo Implement method **/
Waitingroom::~Waitingroom(){
  if(empty())
    	return;

  for(CustomerIterator it = queue.begin(); it != queue.end(); ++it)
  {
	scheduler.ready(**it);
  }
}

/** \todo Implement method **/
void Waitingroom::remove(Customer& that){
  if(empty())
	return;

  for(CustomerIterator it = queue.begin(); it != queue.end(); ++it)
  {
	if(*it == &that)
        {
		Lock lock;
		queue.erase(it);
        }
  }
}

/** \todo Implement method **/
void Waitingroom::enqueue(Customer& that){
  Lock lock;
  queue.push_back(&that);
}

/** \todo Implement method **/
Customer& Waitingroom::dequeue(){
  Customer *cmr;
  if(!empty())
  {
    Lock lock;
    cmr = queue.front();
    queue.pop_front();
  }
  return *reinterpret_cast<Customer*>(cmr);
}
