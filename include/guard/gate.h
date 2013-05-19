/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          G A T E                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __gate_include__
#define __gate_include__

/** 
 * \~german
 * \brief Basisklasse für die Interruptbehandlung
 * 
 * Mit Hilfe dieser Überklasse kann eine Menge von Klassen die Behandlung von Interrupts 
 * durchführen. Jede Unterklasse muss die Funktion \ref trigger() mit den jeweiligen, gewünschten 
 * Verhalten implementieren.
 * 
 * \~english
 * \brief Interrupt handling base class
 *
 * Superclass of a set of classes that are able to handle interrupts. Every
 * subclass of Gate has to implement method trigger() with appropriated
 * behavior.
 **/
class Gate {
  protected:
    /**
     * \~german
     * \brief Nummer des Interrupts, der die Behandlung durch dieses Gates ausgelöst hat
     * 
     * \~english
     * \brief number of occured interrupt
     */
    unsigned short gateInterruptNumber;
    
  public:
    
    /**
     * \~german
     * \brief Konstruktor setzt \ref gateInterruptNumber auf einen ungueltigen Wert
     * 
     * \~english
     * \brief set \ref gateInterruptNumber to an illigal value
     */
    Gate(): gateInterruptNumber(256){}
    
    /** 
     * \~german
     * \brief abstrakte Funktion zur Interruptbehandlung
     * 
     * Tritt ein bestimmter Interrupt auf, so wird diese Funktion der entsprechenden 
     * Unterklasse aufgerufen. Die Ausführung ist asynchron zu den anderen Anweisungen 
     * des Betriebssystem.
     * Da es verschiedene Interrupts gibt, die auch unterschiedliches Verhalten erfordern, 
     * müssen mehrere Unterklassen angelegt werden, je eine pro gewünschten Interrupt. Alle 
     * anderen Interrupts können auf eine einzige, weitere Unterklasse gelegt werden.
     * 
     * \~english
     * \brief interrupt handling method
     *
     * This method is called after an interrupt occured. It is executed 
     * asynchronous to other activities of the operation system. To enable 
     * different behavior according to the occured interrupt this method has to 
     * be implemented in a subclasses of Gate.
     **/
    virtual void trigger() = 0;
    
    /**
     * \~german
     * \brief setzen der Interruptnummer
     * 
     * Ein Gateobjekt kann für mehrere Interrupts zuständig sein. Hier sei besonders das
     * gloabe \ref Panic -Objekt erwähnt. Um die Interrupts unterscheiden zu können kann 
     * die Nummer vor der Behandlung gesetzt werden.
     * 
     * \param slot
     *   Nummer des aufgetretenen Interrups
     * 
     * \~english
     * \brief set interrupt number
     * 
     * It is possible to use one Gate object for multiple objects. To identify the original 
     * interrupt the number could be set here.
     * 
     * \param slot
     *   number of occured interrupt
     */
    void setInterruptNumber(unsigned short slot){
      gateInterruptNumber = slot;
    }
};

#endif
