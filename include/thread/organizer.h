/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         O R G A N I Z E R                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __organizer_header__
#define __organizer_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/scheduler.h"
#include "thread/customer.h"
#include "thread/waitingroom.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Extension of Scheduler to support blocking of Threads
 *
 *  The organizer extends the basic round-robin scheduling through a blocking
 *  semantics. Extended threads called customers are able to wait for certain
 *  operations to finish or may wait if a ressource is unavailable. To support
 *  this ressources which might be unavailable inherit from Waitingroom to
 *  track and manage individual customers waiting for their service. The
 *  organizer handles the transitions of customer between the states "ready",
 *  "running" and "blocked".
 *
 **/
class Organizer : public Scheduler{
  public:
    /** \brief Block the active customer
     *
     * This method puts the currently active customer in the waiting queue of
     * waitingroom. Afterwards the execution switches to the next ready
     * thread.
     *
     *  \param room The room the customer will wait in
     **/
    void block(Waitingroom& room);

    /** \brief Wake up a customer waiting in a room
     *
     *  This method removes the customer from the waitingroom it is waiting in
     *  and puts it in the ready queue.
     *
     *  \param customer The customer to wake up
     **/
    void wakeup(Customer& customer);

    /** \brief Kill a customer either waiting, running or ready
     *
     *  This method extends the functionality of Scheduler::kill through the
     *  removal of currently waiting customers. Therefore the supplied customer
     *  is checked if it is waiting in a room. If this is the case the customer
     *  is removed from the waiting queue of this room. Otherwise
     *  Scheduler::kill is called.
     *
     *  \param that The customer to kill
     **/
    void kill(Customer& that);

    /** \brief Return the currently active customer
     *
     *  \return The currently active customer
     **/
    Customer* active() const;
};

#endif
