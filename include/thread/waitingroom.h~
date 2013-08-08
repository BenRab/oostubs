/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         W A I T I N G R O O M                             *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __waitingroom_header__
#define __waitingroom_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/customer.h"
#include <deque>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief A waitingroom Customers can wait in.
 *
 *  The waitingroom consists of a queue the customers wait in until they can be
 *  serviced.  On destruction of a waitingroom all waiting customers need to be
 *  released. In this case the result of the operation the customers waited for 
 *  depends on the implementation of the service the customers waited for.
 *
 *  \see Semaphore
 **/
class Waitingroom
{
  private:
    /** \brief Queue to store waiting customers in **/
    std::deque<Customer*> queue;

    /** \brief Iterator type definition
     *
     *  This iterator type can be used to iterate over the queue of waiting
     *  customers in a type-safe manner.
     *
     **/
    typedef std::deque<Customer*>::iterator CustomerIterator;
	public:
    /** \brief Destructor reactivating waiting customers
     *
     *  The waiting customers need to be reactivated on destrcution of the
     *  waitingroom since otherwise they will never be scheduled to run
     *  again.
     *
     **/
		virtual ~Waitingroom();
    /** \brief Remove a customer from the waiting queue
     *
     *  This represents a kill command for customers currently waiting in this
     *  room.
     *
     *  \param that Customer to be killed.
     *
     *  \see Scheduler::kill
     **/
		void remove(Customer& that);
    /** \brief Add a customer to the end of the waiting queue
     *
     * \param that Customer to be enqueued
     **/
    void enqueue(Customer& that);
    /** \brief Check if queue is empty
     *
     *  \return true iff empty
     **/
    bool empty() const{return queue.empty();};
    /** \brief Remove the customer in the front line
     *
     *  If there is no customer waiting the result is undefined.
     *
     *  \return the customer in the front or undefined
     **/
    Customer& dequeue();
};

#endif
