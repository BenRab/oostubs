/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \todo \~german verstehen \~english understand */
PIC::PIC(){
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);
  
  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  
  mask_1.outb(32);
  mask_2.outb(40);
  
  mask_1.outb(4);
  mask_2.outb(2);
  
  mask_1.outb(3);
  mask_2.outb(3);
  
  mask_1.outb(0xFB);
  mask_2.outb(0xFF);
}

/** \todo \~german implementieren \~english write implementation*/
void PIC::allow(Interrupts interrupt){
}

/** \todo \~german implementieren \~english write implementation*/
void PIC::forbid(Interrupts interrupt){
}

/** \todo \~german implementieren \~english write implementation*/
void PIC::ack(bool secondPIC){
}

/** \todo \~german implementieren \~english write implementation*/
unsigned char PIC::getISR(bool secondPIC){
  ///todo remove dummy
  return 0;
}
