#include "thread/organizer.h"

/** \todo Implement method **/
void Organizer::block(Waitingroom& room){
}

/** \todo Implement method **/
void Organizer::wakeup(Customer& customer){
}

/** \todo Implement method **/
void Organizer::kill(Customer& that){
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
