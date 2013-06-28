/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                           C P U                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __virtcpu_include__
#define __Virtcpu_include__

#include <signal.h>
#include <stdlib.h>
#include <useful/pic.h>

/** 
 * \~german
 * \brief Emulation spezielle %CPU-Anweisungen für die virtuelle CPU eines Prozesses.
 * 
 * Die Klasse implementiert eine abstraktion des Prozessors. Sie bietet Funktionen zum aktivieren 
 * und deaktivieren von Interrupts im globalen Sinne. Ferner ist es möglich die %CPU anzuhalten.
 * Ist die %CPU angehalten, so wird sie durch das Auftreten eines Interrupts wieder aktiviert.
 * 
 * Um die %CPU für immer anzuhalten ist es notwendig erst die Interrupts zu deaktivieren und danach 
 * die %CPU anzuhalten.
 * 
 * \~english
 * \brief Emulation of %CPU specific instructions of a virtual process CPU.
 *
 * Class CPU implements an abstraction of the processor. It provides methods to
 * enable/disable interrupts globally and to halt the processor.
 */
class Virtual_CPU {
  private:
    /**
     * \~german 
     * \brief Diese Variable speichert den aktuellen Zustand
     * 
     * Diese Variable speichert den aktuellen Zustand um ihn bei Veränderung zurückzugeben.
     * 
     * \~english
     * \brief This variable stores the current state of the interrupt flag to enable feedback for extended APIs.
     */
    bool state;
    
  public:
    
    /**
     * \~german
     * \brief Konstruktor setzt \ref state auf false
     * 
     * \~english
     * \brief initialize \ref state to false
     **/
    Virtual_CPU() : state(false){}
    
    /** 
     * \~german
     * \brief Interrupts werden global aktiviert
     * 
     * \return der alte Zustand
     *
     * \~english
     * \brief globally enable interrupts 
     *
     * \return the old state
     */
    bool enable_int ();
    
    /** 
     * \~german
     * \brief Interupts werden global deaktiviert
     *
     * \return der alte Zustand
     * 
     * \~english
     * \brief globally dissable interrupts
     *
     * \return the old state
     */
    bool disable_int ();
       
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
    void halt ();
};

#endif
