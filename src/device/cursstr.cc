/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                              C U R S E S _ S T R E A M                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/cursstr.h"
#include "config.h"

Curses_Stream::Curses_Stream(){
  Curses_Screen::setAttributes(fgColor, bgColor, blink);
}

void Curses_Stream::flush () {
  print (buffer, pos);
  pos = 0;
}

void Curses_Stream::setAttributes(int fgColor, int bgColor, bool blink){
  Curses_Screen::setAttributes(fgColor, bgColor, blink);
}
