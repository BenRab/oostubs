/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                   C G A _ S T R E A M                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __cursstr_include__
#define __cursstr_include__

#include "object/o_stream.h"
#include "machine/cursscr.h"

/** 
 * \~german
 * \brief Curses basierte Ausgabe, ählich zu std::cout von C++
 * 
 * Curses_Stream ermöglicht die Ausgabe verschiedener Daten als Zeichenkette über eine CGA-Emulation auf einer curses-basierten GUI. Die Klasse ist sowohl von \ref Curses_Screen und \ref O_Stream abgeleitet. Dadurch
 * sind weitere Ausgabeformate und Effekte möglich.
 * 
 * \~english
 * \brief Curses based output mechanism, similar to cout
 *
 * Curses_Stream enables the output of different data as string using a curses emulated CGA 
 * screen. It is derived from the class Curses_Screen and O_Stream, which enables additional 
 * formats and effects.
 */
class Curses_Stream  : public O_Stream, public Curses_Screen {
  public:
    
    /**
     * \~german
     * \brief Der Konstruktor ruft die Funktion \ref CGA_Screen::setAttributes, um damit die
     *        durch \ref O_Stream verwalteten Attribute zu übernehmen.
     * 
     * \~english
     * \brief constructor calls \ref Curses_Screen::setAttributes to set the default attributes of 
     *  \ref O_Stream
     * 
     */
    Curses_Stream();
    
    /** 
     * \~german
     * \brief ausgeben des Inhaltes des internen Puffers
     * 
     * Diese Funktion wird automatisch aufgerufen, sobald der Puffer voll ist oder eine 
     * "neue Zeile" als Zeichen zum Puffer hinzugefügt werden soll.
     * 
     * \~english
     * \brief flush the content of the internal buffer
     *
     * It is called automaticaly as soon as the buffer is full or if a newline is
     * encountered.
     **/
    virtual void flush();
    
    /**
     * \~german
     * \brief verbindet die setAttributes-Funktion von O_Stream mit dem CGA-Treiber
     * 
     * \~english
     * \brief combine the setAttributes function of O_Stream with the presented interface of the
     *        Curses driver
     */
    virtual void setAttributes(int fgColor, int bgColor, bool blink);
    
};

#endif
