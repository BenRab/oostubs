/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     G U A R D I A N                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */

#include "useful/kout.h"
#include "useful/cpu.h"

/* GLOBAL OBJECTS */

/* declare methods as c-like  */
extern "C" void guardian (unsigned short slot);

extern "C" void handleException(unsigned short slot, void* eip, unsigned int eflags, unsigned short cs);
extern "C" void handleExceptionE(unsigned short slot, void* eip, unsigned int eflags, unsigned short cs, unsigned int errorCode);
extern "C" void handleExceptionReserved(unsigned short slot);

/* METHODS  */

/** \brief Entry point for interrupts
 *
 * @param slot number of occurred interrupt
 */
void guardian (unsigned short slot) {

}



/** \brief This function is called if a normal exception is raised by the cpu.
 * 
 * This exception are special interrupts. They are raised if a fault, trap or abort occures
 * and need to be handled. Normally the OS has to take care of this. <br>
 * This function only print the data and stops everything.
 * 
 * @param slot 
 *   number of occurred exception as interrupt number
 * @param eip
 *   This is the instruction pointer where the error occures.
 * @param eflags
 *   This are eflags while the error occures.
 * @param cs
 *   This is the value of the cs-register while the error occures.
 */
void handleException(unsigned short slot, void* eip, unsigned int eflags, unsigned short cs){
  //Fehler melden
  kout.flush();
  kout << endl;
  kout << "Exception "    << slot << " occures";
  kout << endl            << "(";
  kout << "cs: "        << dec  << cs;
  kout << ", eflags: "  << bin  << eflags;
  kout << ", eip: "     << eip;
  kout << ")"           << endl;
  
  //und anhalten
  cpu.disable_int();
  cpu.halt();
}

/** \brief This function is called if a normal exception with error code is raised by the cpu.
 * 
 * This exception are special interrupts. They are raised if a fault, trap or abort occures
 * and need to be handled. Normally the OS has to take care of this. <br>
 * This function only print the data and stops everything.
 * 
 * @param slot 
 *   number of occurred exception as interrupt number
 * @param eip
 *   This is the instruction pointer where the error occures.
 * @param eflags
 *   This are eflags while the error occures.
 * @param cs
 *   This is the value of the cs-register while the error occures.
 * @param errorCode
 *   This is the error code presented by the cpu for this error. The format is exception specific.
 */
void handleExceptionE(unsigned short slot, void* eip, unsigned int eflags, unsigned short cs, unsigned int errorCode){
  //Fehler melden
  kout.flush();
  kout << endl;
  kout << "Exception "    << slot << " occures";
  kout << endl            << "(";
  kout << "cs: "          << dec  << cs;
  kout << ", eflags: "    << bin  << eflags;
  kout << ", eip: "       << eip;
  kout << ", errorCode: " << bin  << errorCode;
  kout << ")"             << endl;
  
  //und anhalten
  cpu.disable_int();
  cpu.halt();
}

/** \brief This function is called if a reserved exception is raised by the cpu.
 * 
 * This exception are special interrupts. They should never be raised!
 * 
 * This function only print the data and stops everything.
 * 
 * @param slot 
 *   number of occurred exception as interrupt number
 */
void handleExceptionReserved(unsigned short slot){
  //Fehler melden
  kout.flush();
  kout << endl;
  kout << "reserved Exception " << slot << " occures" << endl;
  
  //und anhalten
  cpu.disable_int();
  cpu.halt();
}
