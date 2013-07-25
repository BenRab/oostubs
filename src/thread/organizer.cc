#include "thread/organizer.h"


/** \todo Implement method **/
void Organizer::block(Waitingroom& room){
  active()->waiting_in(&room);
  room.enqueue(*active());
  exit();
}

/** \todo Implement method **/
void Organizer::wakeup(Customer& customer){
  customer.waiting_in(0);
  ready(customer);
}

/** \todo Implement method **/
void Organizer::kill(Customer& that){
  Waitingroom *w;
  if((w = that.waiting_in()))
  	w->remove(that);
  
  Scheduler::kill(that);
  
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
