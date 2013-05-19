/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                           C P U                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __CPU_include__
#define __CPU_include__

/** 
 * \~german
 * \brief Zugriff auf einige spezielle %CPU-Anweisungen
 * 
 * Die Klasse implementiert eine abstraktion des Prozessors. Sie bietet Funktionen zum aktivieren 
 * und deaktivieren von Interrupts im globalen Sinne. Ferner ist es möglich die %CPU anzuhalten.
 * Ist die %CPU angehalten, so wird sie durch das Auftreten eines Interrupts wieder aktiviert.
 * 
 * Um die %CPU für immer anzuhalten ist es notwendig erst die Interrupts zu deaktivieren und danach 
 * die %CPU anzuhalten.
 * 
 * \~english
 * \brief Hardware accessor for %CPU specific instructions
 *
 * Class CPU implements an abstraction of the processor. It provides methods to
 * enable/disable interrupts globally and to halt the processor.
 */
class CPU {
  private:
    /**
     * \~german 
     * \brief Diese Variable speichert den letzten Zustand
     * 
     * Um den letzten Zustand der Interrupts wieder herzustellen, muss dieser Wert gespeichert 
     * werden. Bei 0x0200 waren die bisherigen Interrupts an, bei 0 waren sie aus. 
     * Alle anderen Zustände sind undefiniert und dürfen nicht angenommen werden.
     * 
     * \~english
     * \brief This variable stores the last known state of the interrupt flag.
     * 
     * Only 0x0200 for active interrupts and 0 for deaktivated interrupts are allowed.
     */
    int iIFlag;
    
  public:
    
    /**
     * \~german
     * \brief Konstruktor setzt \ref iIFlag auf 0
     * 
     * \~english
     * \brief initialize \ref iIFlag with zero
     **/
    CPU():iIFlag(0){
      
    }
    
    /** 
     * \~german
     * \brief Interrupts werden global aktiviert
     * 
     * \~english
     * \brief globally enable interrupts 
     */
    inline void enable_int () {
      asm(
        "movl $0x0200, %0 \n\t"
        "sti \n\t"
        :"=r"(iIFlag)
      );
    }
    
    /** 
     * \~german
     * \brief Interupts werden global deaktiviert
     * 
     * \~english
     * \brief globally dissable interrupts
     */
    inline void disable_int () {
      asm(
        "pushf\n\t"
        "cli\n\t"
        "movl (%%esp), %0\n\t"
        "add $4, %%esp \n\t"
        :"=r"(iIFlag)
      );
    }
    
    /** 
     * \~german
     * \brief stellt den letzten bekannten Zustand des Interrupt-Flags der %CPU wieder her
     * 
     * Waren die Interrupts vor der letzten Deaktivierung aktiv, so werden sie wieder aktiviert. 
     * Waren sie aber bereits ausgeschaltet, so sind sie dies dann weiterhin. Umgekehrt gilt das 
     * gleiche
     * 
     * \~english
     * \brief restore old, known state of interrupt
     */
    inline void retore_interrupt_state () {
      asm(
        "cli \n\t"
        "andl $0x0200, %0 \n\t"
        "pushf \n\t"
        "orl %0, (%%esp) \n\t"
        "popf \n\t"
        :
        :"r"(iIFlag)
      );
    }
    
    /** 
     * \~german
     * \brief hält die %CPU an
     * 
     * Wenn die %CPU angehalten wird, so wird der Programmzähler (EIP) nicht weiter erhöht und 
     * die %CPU berechnet keine Anweisung mehr, bis ein Interrupt auftritt. Sobald dies geschieht, 
     * so behandelt die %CPU diese Unterbrechung und führt dann mit der Ausführung des nächsten 
     * normalen Befehls fort, so als wäre halt nie aufgerufen worden.
     * 
     * Für eine dauerhaftes Anhalten müssen vor dem Aufruf dieser Funktionen die Interrupts 
     * deaktiviert werden. Dann muss der Computer per Hand ausgeschalten werden.
     * 
     * \~english
     * \brief halt the %cpu
     *
     * When the cpu is halted the program counter will not increase until an
     * interrupt occurs.  If an interrupt occurs the cpu will handle the
     * interrupt and continue with the execution after the halt command.
     */
    inline void halt () {
      asm("hlt");
    }
};

#endif
