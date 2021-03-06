/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         S E M A P H O R E                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __semaphore_header__
#define __semaphore_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/waitingroom.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Basic synchronisation object
 *
 *  This object can be used to synchronize multiple threads. It posses the method signal, which increases the internal variable and possibly readys a blocked thread. The method wait causes the calling thread to block if the internal value is zero. It inherits from Waitingroom to keep track of all the currently waiting threads.
 **/
class Semaphore : public Waitingroom
{
  private:
    /** \brief Current value of semaphore
     *
     * \todo Declare internal variable
     **/
  	unsigned int counter;
	public:
    /** \brief Default Constructor
     *
     *  It sets the internal variable to value.
     *
     *  \param value The initial value
     **/
	Semaphore(unsigned int value);
    /** \brief Virtual Destructor to wake up al waiting customers **/
	virtual ~Semaphore(){}
    /** \brief Decrease value or block calling thread **/
	void p();
    /** \brief Increase value or wake up blocked thread **/
	void v();
    /** \brief Decrease value or block calling thread **/
	void wait(){p();}
    /** \brief Increase value or wake up blocked thread **/
	void signal(){v();}
};

#endif
