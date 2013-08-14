/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         C U S T O M E R                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*/
#ifndef __customer_header__
#define __customer_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/thread.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Forward declaration of Waitingroom
 *
 *  This declaration allows the usage of Waitingroom objects without declaring or defining its content
 **/
class Waitingroom;


/** \brief Extension of Thread able to wait in a Waitingroom
 *
 *  This class extends the basic thread pseudo-concurrency to allow waiting on conditions.
 *  The condition responsible for blocking and reactivating the thread is defined by the implementation of the waitingroom.
 *  \see Semaphore
 *  \see Organizer
 *
 **/
class Customer : public Thread
{
	private:
    /** \brief The waitingroom this thread waits in
     *
     *  If NULL this thread is not waiting in any room.
     **/
		Waitingroom* room;

	public:
    /** \brief Default Constructor
     *
     *  Initializes the thread and declares it non-waiting
     **/
		Customer() : Thread(), room(0){}

	private:
    /** \brief Sets the room this thread is waiting in 
     *
     * Overloaded setter method, which may only be called by Organizer.
     **/

		void waiting_in(Waitingroom* room){
			this->room=room;
		}
	
	public:
    /** \brief Gets the room this thread is waiting in 
     *
     * Overloaded getter method.
     **/
		Waitingroom* waiting_in() const{
			return room;
		}
  /** \brief Friend declaration of Organizer to enable waitingroom changes. **/
	friend class Organizer;
};

#endif
