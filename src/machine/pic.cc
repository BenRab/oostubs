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

extern CPU cpu;
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \todo \~german verstehen \~english understand */
PIC::PIC(){
  IO_Port ctrl_1(0x20), //Kontroll- /Befehlsport Master
          ctrl_2(0xa0), //         ||            Slave
          mask_1(0x21), //Datenport Master
          mask_2(0xa1); //    ||    Slave
  
  //Initialisierung

  //Initialisation Control Word - ICW1
  ctrl_1.outb(0x11);//Wir senden auch ICW4, es gibt zwei PICs 
  ctrl_2.outb(0x11);//und wir wollen Initialisieren
  
  //ICW2
  mask_1.outb(32);//Interruptnummer für IRQ0 (Master) schließt genau
                  //an CPU Exceptions an
  mask_2.outb(40);//         ||         IRQ8 (Slave)
  
  //ICW3
  mask_1.outb(4);//Bitmaske für IRQ2
  mask_2.outb(2);//IRQ über den Master und Slave Kommunizieren (IRQ2)
  
  //ICW4
  mask_1.outb(3);//8086 Mode und Automatisches EOI
  mask_2.outb(3);//             ||
  
  mask_1.outb(0xFB);//Maskierung Master (alle außer IRQ2, Verbindung Slave)
  mask_2.outb(0xFF);//Maskierung Slave (alle IRQ verbieten)
}

void PIC::allow(Interrupts interrupt){//setzt Bit vom zu erlaubenden INT auf 0
  IO_Port mask_1(0x21), //Datenport Master
          mask_2(0xa1); //Datenport Slave

  //CPU cpu;
  cpu.enable_int();

  unsigned char status;
  if(interrupt >= 0 && interrupt <=7){//Master maskieren
    status = mask_1.inb();
    mask_1.outb(status & ~(1 << interrupt));

  } else if(interrupt >7 && interrupt <= 15){//Slave maskieren
    status = mask_2.inb();
    mask_2.outb(status & ~(1 << (interrupt-8)));
  } 
}

void PIC::forbid(Interrupts interrupt){//setzt Bit vom zu verbietenden INT auf 1
  IO_Port mask_1(0x21), //Datenport Master
          mask_2(0xa1); //Datenport Slave

  unsigned char status;
  if(interrupt >= 0 && interrupt <=7){//Master maskieren
    status = mask_1.inb();
    mask_1.outb(status | (1 << interrupt));

  } else if(interrupt >7 && interrupt <= 15){//Slave maskieren
    status = mask_2.inb();
    mask_2.outb(status | (1 << (interrupt-8)));
  } 

}

void PIC::ack(bool secondPIC){//ACK aka EOI (End of Interrupt)
  IO_Port ctrl_1(0x20),//Befehlsport Master
          ctrl_2(0xa0);//Befehlsport Slave
  
  ctrl_1.outb(0x20);
  if(secondPIC){
    ctrl_2.outb(0x20);
  }
}

unsigned char PIC::getISR(bool secondPIC){//TODO superior INT, Ack senden?
  IO_Port ctrl_1(0x20),//Befehlsport Master
          ctrl_2(0xa0);//Befehlsport Slave
  
  if(secondPIC){
    return ctrl_2.inb();
  } else
    return ctrl_1.inb();
}

