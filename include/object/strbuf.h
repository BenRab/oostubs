/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __strbuf_include__
#define __strbuf_include__

/* INCLUDES */

#include "config.h"

/** 
 * \~german
 * \brief Puffer für die Textausgabe
 * 
 * Die Klasse Stringbuffer implementiert einen Puffer, der die Zeichen für die Aufgabe
 * auf dem Bildschirm oder einem anderen Ausgabegerät zwischenspeichert. 
 * Ist der Puffer voll oder wünscht der Programmierer explizit eine Ausgabe, so kann dies mittels 
 * der Methode flush() geschehen. Um die Unabhängigkeit vom Ausgabegerät zu erreichen, muss 
 * jede Unterklasse die Funktion flush() entsprechend implementieren und die gesetzten 
 * Attribute interpretieren.
 * Da spätere Unterklassen auf alle Methoden und Variablen zugreifen müssen, werden alle 
 * Elemente mindestens als protected deklariert.
 * 
 * 
 * \~english
 * \brief Buffer containing text to output
 *
 * Stringbuffer implements a buffer gathering characters that have to be 
 * outputed on the screen or a differenct output device. If the buffer is full
 * or the user wishes to print the content of the buffer on the output device
 * method flush() is called. To enable Stringbuffer to work with different 
 * output devices method flush() has to be implemented by the subclasses of 
 * Stringbuffer.
 * Since every subclass needs access to the variables and methods of the
 * Stringbuffer every variable and method of Stringbuffer is declared 
 * 'protected'.
 */
class Stringbuffer {
  protected:
    /** 
     * \brief buffer containing the characters
     */
    char buffer[BUFFERSIZE];
    
    /** 
     * \brief buffer pointer saving the position of the next insertion
     */
    short pos;
    
    /** 
     * \brief Default constructor setting the buffer empty. 
     */
    Stringbuffer();
    
    /** 
     * \brief Default destructor of Stringbuffer
     */
    virtual ~Stringbuffer();
    
    /** \brief insert a character into the buffer
     *
     * Method put() inserts a character into the buffer. If the buffer is full 
     * after the insertion the buffer has to be emptied by calling the method 
     * flush().
     *
     * @param c character to be inserted into the buffer
     */
    void put(char c);
    
    /** \brief flush the content of the buffer to the screen
     *
     * Method flush() prints the curent content of the buffer. It is called 
     * automaticaly as soon as the buffer is full or manualy if an output is 
     * forced. After printing the buffer content the buffer pointer is reseted.
     * To enalbe the Stringbuffer to work with different output mechanisms the
     * method has to be implemented in a subclass of Stringbuffer.
     */
    virtual void flush() = 0;
    
  public:
    
};

#endif
