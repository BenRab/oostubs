/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                         P L U G B O X                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __plugbox_include__
#define __plugbox_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "guard/gate.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Administrationseinheit für die Interruptweitergabe
 * 
 * Diese Klasse abstrahiert die IDT (Interruptdeskriptortabelle). Sie ermöglicht dem
 * System für jeden Hardware- und jeden Softwareinterrupt eine entsprechende 
 * Behandlungsroutine zu vergeben und bereit zu stellen.
 * 
 * \~english
 * \brief Interrupt forwarding administration unit
 *
 * This Class is an abstraction of the IDT (interrupt descriptor table). It
 * enables the system to define an appropriate handling routine for every hard
 * and software interrupt.
 **/
class Plugbox {
  private:
    ///\~german Anzahl der Elemente im Gate-Array \~english number of elements in gate array
    static const unsigned int uiGateCount = 256;
    
    /** 
     * \~german
     * \brief Array von Zeigern auf Gate-Objekte
     * 
     * Der Puffer soll Gate-Zeiger für alle möglichen 256 Interrupts vorhalten.
     * 
     * \~english
     * \brief array of pointers to Gate objects
     * 
     * The buffer should contain gates for all 256 possible interrupts.
     **/
     Gate* gates[uiGateCount];
    
  public:
    static const int timer    = 32;
    static const int keyboard = 33;
    
    /** 
     * \~german
     * \brief Standardkonstruktor
     * 
     * Er initialisiert das Array von Gate-Zeiger mit dem globalen \ref Panic -Objekt.
     * 
     * \~english
     * \brief Default constructor
     *
     * initialising the map with the global Panic Gate. 
     **/
    Plugbox ();
    
    /** 
     * \~german
     * \brief bindet ein \ref Gate -Objekt an einen speziellen Interrupt
     * 
     * \param slot 
     *   Zahl des Interrupts, welche mit dem Gateobjekt behandelt werden soll
     * \param gate 
     *   Referenz auf das Gateobjekt für den Interrupt
     * 
     * \~english
     * \brief assign a Gate object to a specific interrupt
     *
     * \param slot 
     *   number of interrupt the gate object will be assigned to
     * \param gate 
     *   reference of the gate object containing the handling routine for the interrupt
     */
    void assign(unsigned short slot, Gate& gate) ;
    
    /** 
     * \~german
     * \brief gibt eine Referenz auf das für den Interrupt richtige \ref Gate -Objekt zurück
     *
     * \param slot 
     *   Nummer des aufgetretenen Interrupts
     * \return 
     *   Referenz auf das Gateobjekt, 
     *   sollte die Zahl ungültig sein, so das globale \ref Panic -Objekt
     * 
     * \~english
     * \brief report the assigned Gate object for a specific interrupt
     *
     * \param slot 
     *   number of occured interrupt 
     * \return 
     *   reference of the Gate object or the Panic gate, if none was assigned
     */
    Gate& report(unsigned short slot);
  };

#endif
