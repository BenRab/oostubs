/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/o_stream.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
  
}

O_Stream::~O_Stream(){
  
}

// display of a character
O_Stream& O_Stream::operator << (char c) {
  put(c);
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char c) {
  return *this << (char) c;
}

// display of a string
O_Stream& O_Stream::operator << (char* string) {
  return *this << static_cast<const char*>(string);
}

O_Stream& O_Stream::operator << (const char* string) {
  while (*string)
    put (*string++);
  return *this;
}

// display of digits using basis base to determen the output refering to 
// the value
O_Stream& O_Stream::operator << (short ival) {
  return *this << (long) ival;
}

O_Stream& O_Stream::operator << (unsigned short ival) {
  return *this << (unsigned long) ival;
}

O_Stream& O_Stream::operator << (int ival) {
  return *this << (long ) ival;
}

O_Stream& O_Stream::operator << (unsigned int ival) {
  return *this << (unsigned long) ival;

}

// display of a digit as a long
O_Stream& O_Stream::operator << (long ival) {
  // if value is negative a minus is outputed first
  if (ival < 0) {
    put ('-');
    ival = -ival;
  }
  // than the absolute value of the digit is outputed
  return *this << (unsigned long) ival;
}

O_Stream& O_Stream::operator << (unsigned long ival) {
  unsigned long div;
  char digit;
   
  if (base == 8)
    put ('0');              // oktal digits start with a NULL
  else if (base == 16) {
    put ('0');              // hexadezimal digits start with 0x
    put ('x');
  }
  
  // computes the max power of the choosen basis, that is smaler than the value
  // of the digit
  for (div = 1; ival/div >= (unsigned long) base; div *= base);
  
  // prints the digit character after character
  for (; div > 0; div /= (unsigned long) base) {
    digit = ival / div;
    if (digit < 10)
      put ('0' + digit);
    else
      put ('a' + digit - 10);
    ival %= div;
  }
  return *this;
}

// display of a counter as hexadezimal digit
O_Stream& O_Stream::operator << (void* ptr) {
  Base oldbase = base;
  base = hex;
  *this << (unsigned long) ptr;
  base = oldbase;
  return *this;
}

// call of a manipulator
O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}

O_Stream& O_Stream::operator << (FGColor color){
  flush();
  fgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}

O_Stream& O_Stream::operator << (BGColor color){
  flush();
  bgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}

O_Stream& O_Stream::operator << (Blink blink){
  flush();
  this->blink = blink.blink;
  setAttributes(fgColor, bgColor, this->blink);
  return *this;
}


// ENDL: prints buffer after adding a newline at the end of the buffer
O_Stream& endl (O_Stream& os) {
  os << '\n';
  os.flush ();
  return os;
}

// BIN: choose binary basis for display
O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}

// OCT: choose oktale basis for display
O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}

// DEC: choose dezimal basis for display
O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}

// HEX: choose hexadezimal basis for display
O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

