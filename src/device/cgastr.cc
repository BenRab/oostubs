/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S T R E A M                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/cgastr.h"

const int ROWS = 25;

/** \todo implementieren **/
void CGA_Stream::flush () {
  print(buf, pos);
  pos = 0; 
}

/** \todo implementieren **/
void CGA_Stream::setAttributes(int fgColor, int bgColor, bool blink, bool enableblink){
     CGA_Screen::setAttributes(    fgColor,     bgColor,      blink,      enableblink);
}
