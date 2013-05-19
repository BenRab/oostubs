/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"

const int ROWS = 25;
const int COLS = 80;
char* const CGA = (char*) 0xb8000;//VRAM Start

/** \todo implementieren **/
CGA_Screen::CGA_Screen(){
    cursorX = 0;	
    cursorY = 0;
    setpos(cursorX, cursorY);
    attribut = 7;//LIGHTGREY auf BLACK=7, WHITE auf BLACK=15, YELLOW auf RED blink=206(gelb auf hellrot)
    //setCursorAttributes(64, 31);	
}

/** \todo implementieren **/
CGA_Screen::~CGA_Screen(){
 
}

void CGA_Screen::setCursorAttributes (unsigned char start, unsigned char end) {
    IO_Port indexPort(INDEXREGISTER);
    IO_Port dataPort(DATENREGISTER);

    indexPort.outb(10);
    dataPort.outb(start);//start
    indexPort.outb(11);
    dataPort.outb(end);//end    
}

/** cursor setzen **/
void CGA_Screen::setpos (unsigned short x, unsigned short y) {
    IO_Port indexPort(INDEXREGISTER);
    IO_Port dataPort(DATENREGISTER);

    unsigned short address = y*COLS+x;
    cursorX = x;
    cursorY = y;
    indexPort.outb(15);
    dataPort.outb(address & 0xff);//low byte
    indexPort.outb(14);
    dataPort.outb((address >> 8) & 0xff);//high byte	
}

/** cursorposition lesen **/
void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
    x = cursorX;
    y = cursorY; 
}

/** zeichen an x/y schreiben **/
void CGA_Screen::show (unsigned short x, unsigned short y, char c, unsigned char attrib) {
    *(CGA+(y*COLS+x)*2)   = c;
    *(CGA+(y*COLS+x)*2+1) = attrib;
}

/** zeichenkette an aktueller Position **/
void CGA_Screen::print (const char* string, unsigned int n) {
    unsigned short x,y;
    getpos(x,y);
    for(unsigned int i=0; i<n; i++) {
	if(x >= COLS || string[i] == '\n')
	{
            x = 0;
            if(y >= ROWS-1)
            {
		scrollup();
	    }
	    else
		y++;
	    if(string[i] == '\n')
		continue;//sonst wird \n ausgegeben
	}	    
	show(x++, y, string[i], attribut);
    }
    setpos(x, y);
}

/** aktuellen Bildschirm nach oben scrollen, untere Zeile mit Leerzeichen fuellen **/
void CGA_Screen::scrollup () {
    for(int i=0; i<(ROWS-1)*COLS*2; i++)
	*(CGA+i) = *((CGA+COLS*2)+i);//Bildschirminhalt um eine Zeile nach oben schieben

    for(int i=0; i<COLS; i++)
    {
	show(i, ROWS-1, ' ', attribut);//letzte Zeile mit Leerzeichen fuellen
    }

}

/** aktuellen Bildschirm mit Leertasten fuellen **/
void CGA_Screen::clear () {
    for(int i=0; i<ROWS*COLS; i++) {
	*(CGA+i*2) = ' ';
    	*(CGA+i*2+1) = attribut;
    }
}

/** attribute setzen fgColor->4Bit, bgColor->3Bit blink->1Bit**/
void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink, bool enableblink){

  if(fgColor != -1){
    attribut &= 0xF0;//0%11110000 fgColor auf 0 setzen
    attribut |= (fgColor%16);
  }

  if(bgColor != -1){
    attribut &= 0x8F;//0%10001111 bgColor auf 0 setzen
    attribut |= ((bgColor%8)<<4);
  }

  if(enableblink){
    attribut &= 0x7F;//0%01111111 blink auf 0 setzen
    attribut |= ((blink%2)<<7);
  }
}

