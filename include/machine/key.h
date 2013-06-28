/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                           K E Y                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __Key_include__
#define __Key_include__

#include <curses.h>

/**
 * /~english
 * \brief Class representing a pressed key of the keyboard.
 */
class Key {
  private:
    unsigned int asc;
    
  public:
    /** \brief Default constructor setting ASCII code to 0
     *
     * A freshly constructed key is invalid.
     */
    Key () : asc (0) {}

    /** \brief Valid key constructor
     *
     * Since this constructor takes the content of a key the constructed key is
     * valid unless the scancode was 0.
     *
     */
    Key(unsigned int s) : asc(s) {}
    
    /** \brief Test for validity.
     *
     * return  false if ascii code is 0, true otherwise
     */
    bool valid (){ 
      return asc; 
    }
    
    /** \brief Invalidate this key
     *
     * By setting the ascii code to 0 this key will be invalidated.
     */
    void invalidate () { 
      asc = 0; 
    }
    
    /** \brief Set ascii value.
     *
     * \param a The new ascii value
     **/
    void ascii (unsigned char a) { 
      asc = a; 
    }

    /** \brief Set scancode value
     *
     * \param s The new scancode value
     **/
    void scancode (unsigned int s) { 
      asc = s; 
    }

    /** \brief Get scancode value
     *
     * \return current scancode
     **/
    unsigned int scancode () const { 
      return asc;; 
    }
    
    /** \brief Get ascii value
     *
     * \return the current ascii value
     **/
    unsigned char ascii () const { 
      return asc; 
    }
          
    /** \brief overloded cast operator
     *
     * Can be used to cast this key to an ascii char.
     *
     * \return the ascii value of this key contained in a char
     **/
    operator char (){ 
      return (char) asc; 
    }
    
    /**
     * \~german
     * \brief spezielle scan codes
     * 
     * \~english
     * \brief special scan codes
     */
    struct scan { 
      enum {
        f1    = KEY_F(1), 
        del   = KEY_DC, 
        up    = KEY_UP, 
        down  = KEY_DOWN, 
        left  = KEY_LEFT, 
        right = KEY_RIGHT,
      };
    };
};

#endif
