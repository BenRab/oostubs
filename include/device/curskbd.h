/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __curskbd_include__
#define __curskbd_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "guard/gate.h"
#include "machine/key.h"
#include "thread/semaphore.h"
 
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Treiber für die Tastatur, incl. Interruptunterstützung.
 * 
 * Diese Klasse ist von Gate abgeleitet und implementiert die Interruptroutine der Tastatur.
 * 
 * \~english
 * \brief %Keyboard driver with interrupt support
 *
 * This class is a subclass of Gate and implements the interrupt routine used 
 * for the keyboard.
 */
class Curses_Keyboard : public Gate  {
  private:
      static const unsigned int maxBufferSize=1;
      std::deque<Key> buffer;
      Semaphore sem;

      /** \brief Fetch a key from the keyboard controller(ncurses)
       *
       * \return A Key object representing the fetched key or an invalid object if none was available
       **/
      Key key_hit();

  public:
     
     /** 
      * \~german
      * \brief Der Konstruktor ruft die vorherigen Konstruktoren auf.
      * 
      * \~english
      * \brief constructor only calls constructor of base classes up to now
      */
     Curses_Keyboard();
     
    /** 
     * \~german
     * \brief aktiviert den Interruptmechanismus für die Tastatur
     * 
     * Die Methode aktiviert die Keyboard Interrupts. Nach dem Aufruf werden die Interrupts, 
     * welche durch die Tastatur generiert werden, weitergereicht. Die Behandlung ist dann 
     * mit trigger möglich.
     * 
     * \~english
     * \brief enable the interrupt mechanism of the keyboard
     * 
     * Method plugin() enables all keyboard interrupts. After calling plugin()
     * interrupts activated by the keyboard are recognised.
     */
    void plugin ();
    
    /** 
     * \~english
     * \brief handle keyboard interrupt
     */
    virtual void trigger ();

    /**
     * \~english
     * \brief fetch a key from the keybord's key storage
     *
     * This method may block the calling thread until a key is available.
     *
     * \return A Key object holding the last pressed key
     **/
    Key getkey();
};

#endif
