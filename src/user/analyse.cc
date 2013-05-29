
#include "user/analyse.h"
#include "useful/kout.h"
#include "useful/cpu.h"

/** \brief 
 *    \~english analyse function for exception
 *    \~german  Funktion zur Analyse einer Fehlerbehandlungsroutine.
 * 
 * \~
 * \param[in] slot
 *   \~english
 *   This is the interrupt ID, hence the same parameter as \ref guardian.
 *   \~german
 *   Dies ist die ID des Interrupts, wie er auch der Funktion \ref guardian übergeben worden wäre.
 * 
 * \~
 * \param[in] esp
 *   \~english
 *   This is the pointer to the top of the stack as it would be at the start of function
 *   \ref handleException. No code of the function is been executed thus the esp is in a status
 *   of never touched by the function itself.
 *   \~german
 *   Dieser Zeiger geht auf den Anfang des Stacks, wie er beim Aufruf der Funktion 
 *   \ref handleException wäre. Zu dem festgehaltenem Zeitpunkt wurde zwar die Funktion schon 
 *   aufgerufen, es wurde aber noch keine einzige Zeile abgearbeitet. Die Funktion selber hat
 *   den Stack also noch nicht verändert.
 *   
 *   
 * \~
 * \todo \~german den markierten ToDo-Bereich ausfüllen \~english fill in the todo area
 */
void analyseException(unsigned short slot, void** esp){
  //Ausgabe, was passiert ist
  kout << endl;
  kout << "analyseException(" << slot << ", " << esp << ") called" << endl;
  
  /* * * * * * * * * * * * * * * * * * *\
  # Start ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
  //TODO Analyse-Ausgaben hier hin
  
  /* * * * * * * * * * * * * * * * * * *\
  #  Ende ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
  
  //und anhalten, damit nichts schlimmes passiert
  cpu.disable_int();
  cpu.halt();
}


/** \brief 
 *    \~english analyse function for procedure stack
 *    \~german  Diese Funktion dient der Analyse des Prozedurstacks.
 * 
 * \~english
 * The functions prints the first 60 32 bit words of the stack, 
 * four of them in one line, each.
 * \~german 
 * Es werden die ersten 60 32-Bit-Worte vom Stack ausgegeben. Dabei 
 * erscheinen je vier der Worte in einer Zeile.
 * 
 * \~
 * \param[in] esp
 *   \~english
 *   This is a pointer to the top of the stack as it would be in function \ref alphaAckermann
 *   of task3B.cc before calling gotoAnalyse.
 *   \~german
 *   Dis ist ein Zeiger auf den Anfang des Stacks. Er ist aufgebaut, wie kurz 
 *   vor dem Aufruf der Funktion gotoAnalyse innerhalb von \ref alphaAckermann in 
 *   der Datei task3B.cc. Auf diese Weise kann der Prozedurstack gut analysiert werden.
 * 
 * \~
 * \todo \~german Funktion fuer Analyse ausfuellen. \~english fill in todo area
 */
void analyseProcedureStack(void** esp){
  //Ausgabe, was passiert ist
  kout << endl;
  kout << "analyseProcedureStack(" << esp << ") called" << endl;
  
  /* * * * * * * * * * * * * * * * * * *\
  # Start ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
  //TODO Analyse-Ausgaben hier hin
  
  /* * * * * * * * * * * * * * * * * * *\
  #  Ende ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
} 
