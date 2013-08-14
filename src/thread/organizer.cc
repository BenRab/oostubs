#include "thread/organizer.h"
#include "thread/lock.h"

/** \todo Implement method **/
void Organizer::block(Waitingroom& room){
  active()->waiting_in(&room);
  room.enqueue(*active());
  exit();
}

/** \todo Implement method **/
void Organizer::wakeup(Customer& customer){
  customer.waiting_in()->remove(customer);
  customer.waiting_in(0);
  ready(customer);
}

/** \todo Implement method **/
void Organizer::kill(Customer& that){
  Waitingroom *w = that.waiting_in();
  if(w) {
    w->remove(that);
  } else {
    Scheduler::kill(that);
  }
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
