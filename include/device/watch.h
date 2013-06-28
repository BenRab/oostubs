/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          W A T C H                                            * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __watch_include__
#define __watch_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "guard/gate.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * \~english
 * \brief Handler for periodic timer interrupts
 * 
 * This class is a subclass of Gate and implements the interrupt routine used 
 * for the clock.
 */
class Watch : public Gate {
public:
  /**
   * \~english
   * \brief Default Constructor
   *
   * Does nothing special.
   */
  Watch(){}

  /**
   * \~english
   * \brief Constructor initalizing the clock
   *
   * Default constructor of the interrupt handler of the clock. The constructor
   * initialises the clock to cause an interrupt every us microseconds if enabled.
   * \param us interval between interrupts caused by the time-interrupt in 
   *           microsecounds
   */
  Watch (unsigned int us);

  /**
   * \~english
   * \brief Enable the clock interrupt and its handling
   *
   * Method windup() is used to enable the clock interrupt. After calling 
   * windup() the clock interrupt is triggered in the defined interval. This 
   * time interval is defined through the constructor of Watch or a system specific default value.
   */
  void windup();

  /**
   * \~english
   * \brief Handling method of the clock interrupt
   *
   * Handles incoming clock interrupts. Issues a preemtion of the currently
   * running thread and schedules the next one.
   *
   **/
  virtual void trigger();
};

#endif
