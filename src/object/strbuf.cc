/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/strbuf.h"

Stringbuffer::Stringbuffer() : pos(0){
  
}

Stringbuffer::~Stringbuffer(){
  
}

void Stringbuffer::put (char c) {
  buffer[pos] = c;
  pos++;
  if (pos == sizeof (buffer))
    flush ();
}

