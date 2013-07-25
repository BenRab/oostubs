#include "thread/waitingroom.h"

/** \todo Implement method **/
Waitingroom::~Waitingroom(){
}

/** \todo Implement method **/
void Waitingroom::remove(Customer& that){
  if(queue.empty())
	return;

  for(CustomerIterator it = queue.begin(); it != queue.end(); ++it)
  {
	if(*it == &that)
		queue.erase(it);
  }
}

/** \todo Implement method **/
void Waitingroom::enqueue(Customer& that){
  queue.push_back(&that);
}

/** \todo Implement method **/
Customer& Waitingroom::dequeue(){
  Customer *cmr = queue.front();
  queue.pop_front();

  return *reinterpret_cast<Customer*>(cmr);
}
