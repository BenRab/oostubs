/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 B                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __task3B_include__
#define __task3B_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/appl.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** \brief Third test application, part 2
 *
 * This application test the functionality of the implemented interrupt system.
 * It prints the task identification and then repeatedly draws a line in an
 * endless loop.  Interrupts from the keyboard are printed onto the screen to a
 * fixed location. This should disturb the drawing of the line.
 **/
class Task3B : public Application{
  public:
    
    /** \brief Default constructor
     *
     * prints task information and enables interrupts
     **/
    Task3B();
    
    /** \brief Destructor
     *
     * disables interrupts, should never be called due to the endless loop
     **/
    virtual ~Task3B();
    
    /** \brief prints the line **/
    virtual void action();
};

#endif
