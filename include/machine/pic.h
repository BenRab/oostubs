/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __pic_include__
#define __pic_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/io_port.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Treiber für den %PIC (Programmable Interrupt Controller)
 * 
 * Der %PIC (programmierbarer Interruptkontroller) ermöglicht es dem System bestimmte Interrupts 
 * bzw. unterbrechungen zu erlauben oder zu verbieten. Wurden die Interrupts global aktiviert,
 * so legt der PIC fest, welche Interrupts weitergreicht werden um vom System behandelt zu werden. 
 * Es ist wichtig,d ass Interrupts nur behandelt werden, falls der entsprechende Interrupt erlaubt 
 * wurde und die Behandlung im allgemeinen aktiviert ist - siehe dazu die Klasse \ref CPU.
 * 
 * Der %PIC basiert auf Intels 8259 Chip und besteht aus einem Master-Slave %PIC-System.
 * Heutzutage werden sie meist nur "emuliert". Verwendet wird mittlerweile APIC, welcher für 
 * ein Mehrkernbetrieb notwendig ist.
 * 
 * \~english
 * \brief Driver for Programmable Interrupt Controller
 *
 * The %PIC or Programmable Interrupt Controller enables the system to 
 * allow/forbid interrupts. By allowing an interrupt the PIC defines which
 * interrupts are handled by the system. It is important that interrupts will
 * only be handled if the interrupt has been allowed and if the handling of 
 * interrupts is enabled (see class \ref CPU). 
 */
class PIC{
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
      pic2          = 2,  ///< \~german Anschluss von Slave-PIC \~english second PIC
      serial2       = 3,  ///< \~german RS-232 Port 2 und 4 \~english RS-232 port 2 and 4
      serial1       = 4,  ///< \~german RS-232 Port 1 und 3 \~english RS-232 port 1 and 3
      soundcard     = 5,  ///< \~german Soundkarte oder LPT 2 \~english sound card or LPT 2
      floppy        = 6,  ///< \~german Diskettenkontroller \~english floppy disc controller
      parallelport  = 7,  ///< \~german LPT 1 und unechter Interrupt \~english LPT 1
      rtc           = 8,  ///< \~german Echtzeituhr vom CMOS (RTC) \~english real time clock
      misc          = 9,  ///< \~german verschiedene \~english miscellaneous
      ata4          = 10, ///< \~german vierter ATA(PI)/IDE \~english fourth ATA(PI)/IDE
      ata3          = 11, ///< \~german dritter ATA(PI)/IDE \~english third ATA(PI)/IDE
      secondps2     = 12, ///< \~german zweiter Tastaturkontrolleranschluss \~english second keyboard controller port
      fpu           = 13, ///< \~german Gleitkommazahleneinheit \~english floating point unit
      ata1          = 14, ///< \~german erster ATA(PI)/IDE \~english first ATA(PI)/IDE
      ata2          = 15  ///< \~german zweiter ATA(PI)/IDE und unechter Interrupt\~english second ATA(PI)/IDE
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
    PIC();
  
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
     * \brief sendet ein "Acknowledgement" eines ausstehenden Interrupts
     * 
     * Die Funktion bestätigt die Behandlung eines aufgetretenen Interrupts. Dies sagt dem 
     * PIC, dass der letzte gemeldete Interrupt abgearbeitet wurde
     * 
     * \~english
     * \brief acknowledge the handling of a pending interrupt
     *
     * Acknowledge an occured interrupt. This tells the PIC that his last
     * interrupt has been handled. This Method has to be called before the cpu is
     * allowed to handle any new interrupts. If an interrupt is not acknowledged
     * the same interrupt is called again and again.
     * 
     * If an interrupt accures at the slave %PIC than also the first one has to be acknowledged.
     * 
     * \param secondPIC
     *   Should an acknowledgement send to the second and first PIC or yust the first one?
     */
    void ack(bool secondPIC);
    
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
};

#endif
