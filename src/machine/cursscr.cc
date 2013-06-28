/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cursscr.h"
#include "config.h"

Curses_Screen::Curses_Screen() : attribute(0x7){
  win=newwin(25,80,0,0);
  scrollok(win, true);
  redrawwin(win);
}

Curses_Screen::~Curses_Screen(){
}

void Curses_Screen::setpos (unsigned short x, unsigned short y) {
  wmove(win, y, x);
}

void Curses_Screen::getpos (unsigned short& x, unsigned short& y) const{
  getyx(win, y, x);
}

void Curses_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attrib) {
  unsigned short xSave, ySave;
  getpos(xSave, ySave);
  wmove(win, y, x);
  wechochar(win, character);
  wmove(win, ySave, xSave);
}

void Curses_Screen::print (const char* string, unsigned int n) {
 waddnstr(win, string, n);
 wrefresh(win);
}

void Curses_Screen::scrollup () {
  scroll(win);
}

void Curses_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  
}

void Curses_Screen::clear(){
    werase(win);
}
