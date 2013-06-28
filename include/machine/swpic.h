/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __swpic_include__
#define __swpic_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include <signal.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Emulation eines %PIC (Programmable Interrupt Controller) Treibers
 * 
 * Der %PIC (programmierbarer Interruptkontroller) ermöglicht es dem System bestimmte Interrupts 
 * bzw. unterbrechungen zu erlauben oder zu verbieten. Wurden die Interrupts global aktiviert,
 * so legt der PIC fest, welche Interrupts weitergreicht werden um vom System behandelt zu werden. 
 * Es ist wichtig,d ass Interrupts nur behandelt werden, falls der entsprechende Interrupt erlaubt 
 * wurde und die Behandlung im allgemeinen aktiviert ist - siehe dazu die Klasse \ref Virtual_CPU.
 * 
 * Der %PIC basiert auf Intels 8259 Chip und besteht aus einem Master-Slave %PIC-System.
 * Heutzutage werden sie meist nur "emuliert". Verwendet wird mittlerweile APIC, welcher für 
 * ein Mehrkernbetrieb notwendig ist.
 * 
 * \~english
 * \brief Emulation of a Driver for the PIC (Programmable Interrupt Controller)
 *
 * The %PIC or Programmable Interrupt Controller enables the system to 
 * allow/forbid interrupts. By allowing an interrupt the PIC defines which
 * interrupts are handled by the system. It is important that interrupts will
 * only be handled if the interrupt has been allowed and if the handling of 
 * interrupts is enabled (see class \ref Virtual_CPU). 
 */
class Software_PIC{
  private:
      sigset_t enabledSet, disabledSet;
  public:
    /** 
     * \~german
     * \brief externe Interruptquellen
     * 
     * Die folgende Liste gibt die oft genutze Liste der Interrupts an. Sie ist nicht für alle
     * Computer gleich, da sie sich danach richtet, welche Hardware an den entsprechenden 
     * Interrupteingang vom PIC angeschlossen ist.
     * 
     * Die ersten acht Einträge stammen vom ersten PIC (Master), 
     * die letzten acht vom zweiten PIC (Slave).
     * 
     * \~english
     * \brief External interrupt sources
     */
    enum Interrupts{
      timer         = 0,  ///< \~german Intervallzähler (PIT) \~english timer (PIT)
      keyboard      = 1,  ///< \~german Tastaturkontroller \~english keyboard controller
    };
    
    /** 
     * \~german
     * \brief Standardkonstruktor
     * 
     * Er initialisiert den PIC und maskiert alle einkommenden Interrupt, damit wird keiner  an
     * die %CPU durchgereicht.
     * 
     * \~english
     * \brief Default Constructor
     *
     * Setting up the PIC and masking all incoming interrupt channels
     */
    Software_PIC();


    ~Software_PIC();
    /** 
     * \~german
     * \brief erlaubt einen speziellen Interrupt von der Hardware
     * 
     * Die Funktion ermöglich dem System Interrupts von speziellen Geräten mit Hilfe des %PICs
     * zu behandeln. Damit überhaupt ein Interrupt behandelt werden kann muss vorher 
     * \ref CPU::enable_int() aufgerufen werden um die Interrupts global zu erlauben.
     * 
     * \~english
     * \brief allow a specific hardware interrupt
     *
     * Enables the system to handle interrupts of the specified 
     * device using the %PIC. To enable the handling of any interrupt 
     * \ref CPU::enable_int() has to be called first.
     *
     * \param interrupt 
     *   number of interrupt that will be allowed
     */
    void allow(Interrupts interrupt);
    
    /** 
     * \~german
     * \brief verbietet einen speziellen Interrupt der Hardware
     * 
     * Diese Funktion deaktiviert einen bestimmten Interrupt mit Hilfe des %PICs.
     * 
     * 
     * \~english
     * \brief forbid a specific hardware interrupt
     *
     * Disables an interrupt useing the %PIC.
     *
     * \param interrupt 
     *   number of interrupt that will be forbiden
     */
    void forbid(Interrupts interrupt);
    
    /** 
     * \~german
     * \brief den ISR eines der beiden PICs ermitteln
     * 
     * Diese Information ist besonders zur Behandlung eines "Spurious Interrupt" interessant. 
     * Dieser tritt auf, wenn ein Interrupt gemeldet wird. Aber wenn die CPU bereits zur 
     * Behandlung ist, hat die eigentliche Hardware ihren IRQ zurück genommen. Der PIC muss nun 
     * die Nummer eines Interrupts melden. Jedoch liegt keiner mehr vor. Deshalb meldet der PIC
     * dann seine letzte Nummer. Der Slave meldet also 15, der Master die 7.
     * 
     * \attention
     * Sollte der zweite (Slave) PIC den "Spurious Interrupt", so ist dies für den ersten 
     * ein echter Interrupt. Der erste PIC muss deshalb ein \c ACK erhalten.
     * 
     * \note
     * Eine Behandlung dieser "Spurious Interrupt" in der Funktion \ref guardian ist nur 
     * optional. Diese Funktion muss aber in jedem Fall inplementiert werden.
     * 
     * \param secondPIC
     *   Soll der ISR des zweiten PICs zurückgegeben werden?
     * 
     * \return
     *   Der ISR des angefragten PICs.
     * 
     * \~english
     * \brief returns the ISR of one of the two PICs
     * 
     * \param secondPIC
     *   Should the ISR of the second PIC be returned?
     * 
     * \return
     *   The ISR of the desired PIC.
     */
    unsigned char getISR(bool secondPIC = false);

    friend class Virtual_CPU;
};

#endif
