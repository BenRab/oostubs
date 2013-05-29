/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 A                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __task3A_include__
#define __task3A_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/appl.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** \brief Third test application, part 1
 *
 * This application test the functionality of the implemented interrupt system.
 * It prints the task identification and then repeatedly draws a line in an
 * endless loop.  Interrupts from the keyboard are printed onto the screen to a
 * fixed location. This should disturb the drawing of the line.
 **/
class Task3A : public Application{
  protected:
    void testFPN();
    void testFPNAdd();
    void testFPNMul();
    void testFPNDiv();
    void testFPNPow();
    void testFPNSqrt();
    
  public:
    
    /** \brief Default constructor
     *
     * prints task information and enables interrupts
     **/
    Task3A();
    
    /** \brief Destructor
     *
     * disables interrupts, should never be called due to the endless loop
     **/
    virtual ~Task3A();
    
    /** \brief main part of the class **/
    virtual void action();
};

#endif
