/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __o_stream_include__
#define __o_stream_include__

/* INCLUDES */
#include "object/strbuf.h"

/* CLASSES */

/** 
 * \~german
 * \brief Definition der Farben
 * 
 * Durch die Verwendung eines enums werden automatisch die Farben Zahlenwerten zugewiesen.
 * 
 * \~english
 * \brief Color definitions 
 */
enum Colors{
    BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGREY,
    DARKGREY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE
};

/** \brief Manipulation object to set foreground color
 *
 *  the object will be created through the call of the constructor.
 *  Afterwards it is passed via the << operator to the O_Stream object.
 *  The O_Stream object then passes the internal color to the driver through the abstract setAttribute function.
 *  Care needs to be taken, since the attribute change will effect the whole buffer including preceding characters.
 */
class FGColor{
  public:
    /** 
     * \brief internal color to be passed to driver
     */
    Colors color;
    /** 
     * \brief Constructor setting internal color
     * \param color new foreground color
     */
    FGColor(Colors color) : color(color){}
};

/** \brief Manipulation object to set background color
 *
 *  the object will be created through the call of the constructor.
 *  Afterwards it is passed via the << operator to the O_Stream object.
 *  The O_Stream object then passes the internal color to the driver through the abstract setAttribute function.
 *  Care needs to be taken, since the attribute change will effect the whole buffer including preceding characters.
 */
class BGColor{
  public:
    /** 
     * \brief internal color to be passed to driver 
     */
    Colors color;
    /** 
     * \brief Constructor setting internal color
     * \param color new background color
     */
    BGColor(Colors color) : color(color){}
};

/** \brief Manipulation object to set blinking
 *
 *  the object will be created through the call of the constructor.
 *  Afterwards it is passed via the << operator to the O_Stream object.
 *  The O_Stream object then passes the internal blink attribute to the driver through the abstract setAttribute function.
 *  Care needs to be taken, since the attribute change will effect the whole buffer including preceding characters.
 */
class Blink{
  public:
    /** 
     * \brief internal state to be passed to driver 
     */
    bool blink;
    /** 
     * \brief Constructor setting internal state
     * \param blink new blinking state
     */
    Blink(bool blink) : blink(blink){}
};


/** \brief Manipulation class providing formatted output support
 *
 * O_Stream extends the Stringbuffer and contains the definitions of the 
 * << operator of the most important predefined datatypes. It is used to 
 * implement the known usability of the C++ io_stream library. 
 * At the moment the display of characters, strings and digits is supported.
 * Besides the operator definition contained in O_Stream several auxiliary 
 * manipulators are defined. These manipulators are used to choose the basis 
 * for display of digits and to print the buffer after an endl.
 */
class O_Stream : public Stringbuffer{
  protected: 
    /// \~german  intern gespeicherte Vordergrundfarbe
    /// \~english internal saved foreground color
    int fgColor;
    /// \~german  intern gespeicherte Hintergrundfarbe
    /// \~english internal saved background color
    int bgColor;
    /// \~german  intern gespeicherte Blinkverhalten
    /// \~english internal saved blinking status
    bool blink;
    
    /**
     * \~german 
     * \brief ermöglicht dem O_Stream das setzen der Attribute
     * 
     * Dem Stream können Attributwerte wie Farbe übergeben werden. Aufgrund der Kapselung 
     * kann die Klasse aber die Attribute nicht setzen. Deshalb wird die abstrakte Funktion 
     * deklariert, die in einer abgeleiteten Klasse implementiert werden muss.
     * 
     * \param fgColor
     *    Vordergrundfarbe
     * 
     * \param bgColor
     *    Hintergrundfarbe
     * 
     * \param blink
     *    Soll es blinken?
     * 
     * \~english 
     * \brief interface to set attributes
     * 
     * It is possible to stream in attributes like colour. But this class does not know
     * how to how to set this, the driver has to do it. Hence this abstract function is provided
     * as an interface and a later, specific class has to implement it.
     * 
     * \param fgColor
     *    new foreground colour
     * 
     * \param bgColor
     *    new background colour
     * 
     * \param blink
     *    blinking state
     */
    virtual void setAttributes(int fgColor, int bgColor, bool blink) = 0;
    
  public:
    
    /** 
     * \brief basis for display of digits eg. 2, 8, 10 or 16 
     */
    enum Base{
      bin=2,
      oct=8,
      dec=10,
      hex=16
    };
    
    /** 
     * \brief current selected base 
     */
    Base base;
    
    /** 
     * \brief Default constructor initialising with dezimal system 
     */
    O_Stream();
  
    /** 
     * \brief Default Destructor
     */
    virtual ~O_Stream();
    
    /** \brief overloded output operator
     *
     * Operator << overloading the default operator. Is used to convert
     * the given datatype into a string that can be printed on an output device.
     * This operator has to be implemented for every standard data type (char, 
     * unsigned char, short, unsigned short, int, unsigned int, long, 
     * unsigned long, void*, char*).
     *
     * @param value value of datatype (has the type of datatype) 
     * @return reference to the current O_Stream object.
     **/
    O_Stream& operator << (char value); 
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (unsigned char value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (char* value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (const char* value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (unsigned short value); 
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (short value); 
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (unsigned int value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (int value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (unsigned long value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (long value);
    
    /** \copydoc operator<<(char value) **/
    O_Stream& operator << (void* value);
    
    /** \brief overloded output manipulator
     *
     * Operator << overloading the default operator. It is used to change the way the characters are printed on the screen.
     *
     * @param fgColor new foreground color
     * @return reference to the current O_Stream object.
     */
    O_Stream& operator << (FGColor fgColor);
    
    /** \brief overloded output manipulator
     *
     * Operator << overloading the default operator. It is used to change the way the characters are printed on the screen.
     *
     * @param bgColor new background color
     * @return reference to the current O_Stream object.
     */
    O_Stream& operator << (BGColor bgColor);
    
    /** \brief overloded output manipulator
     *
     * Operator << overloading the default operator. It is used to change the way the characters are printed on the screen.
     *
     * @param blink new blinking state
     * @return reference to the current O_Stream object.
     */
    O_Stream& operator << (Blink blink);
    
    /** \brief overloaded output operator for manipulator functions
     *
     * Operator << overloading the default operator is used to call defined 
     * manipulators.
     *
     * @param f mainpulator function to be applied to the ostream
     * @return reference to the current O_Stream object.
     **/
    O_Stream& operator << (O_Stream& (*f) (O_Stream&));
    
    /* declaration for manipulator functions */
    friend O_Stream& endl(O_Stream&);
    friend O_Stream& bin(O_Stream&);
    friend O_Stream& oct(O_Stream&);
    friend O_Stream& dec(O_Stream&);
    friend O_Stream& hex(O_Stream&);
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                          M A N I P U L A T O R E N                        *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * The following methods receive and return a referenz to the current O_Stream
 * object. Class O_Stream defines an operator that can be used to call this so
 * called manipulators. It is eveen possible to embedd the output of the method
 * into the input of the stream.
 * Main goal of the manipulators is to influence the display of the following 
 * output (eg. by choosing a basis for the display of digits).
 **/ 

/** 
 * \brief print buffer after adding a newline 
 */
O_Stream& endl(O_Stream &out);

/** 
 * \brief switch basis of o_stream to binary 
 */
O_Stream& bin(O_Stream &out);

/** 
 * \brief switch basis of o_stream to octal 
 */
O_Stream& oct(O_Stream &out);

/** 
 * \brief switch basis of o_stream to decimal 
 */
O_Stream& dec(O_Stream &out);

/** 
 * \brief switch basis of o_stream to hexadecimal 
 */
O_Stream& hex(O_Stream &out);

#endif
