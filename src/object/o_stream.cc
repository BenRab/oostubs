/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/o_stream.h"

/** \todo implementieren **/
O_Stream::O_Stream() : Stringbuffer(){
  base = dec;
  pos = 0;
}

/** \todo implementieren **/
O_Stream::~O_Stream(){
  /* ToDo: insert sourcecode */
}

int ulongToChar(unsigned long n, char* stack, int base)
{
  char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  int i = 79;
  if(base == 16) {
    for(int k=0; k<8; k++)
    {
      stack[i-k] = '0';
    }
  }
  do
  {
    int reminder = n%base;
    n /= base;
    stack[i] = (digits[reminder]);
    --i;
  } while(n > 0);
  if(base == 16) {
    i = 71;
    stack[i--] = 'x';
  }
  if(base == 8) {
    stack[i] = 'o';
    --i;
  }
  if(base == 8 || base == 16) {
    stack[i] = '0';
    --i;
  }
  if(base == 2) {
    stack[i] = 'b';
    --i;
  }
  return i;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (char value) {
  put(value);
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned char value) {
  put((char) value);
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (char* value) {
  int i = 0;
  while(value[i] != '\0'){
    put(value[i]);
    i++;
  }
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (const char* value) {
  return operator<<((char*) value);
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (short value) {
  return operator<<((long) value);
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned short value) {
  return operator<<((unsigned long) value);
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (int value) {
  return operator<<((long) value);
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned int value) {
  return operator<<((unsigned long) value);
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (long value) {
  char stack_[80];
  int i = ulongToChar((unsigned long) value, stack_, base);

  if(value < 0)
  {
    // push the sign on the stack and threat it as an positive number
    stack_[i]='-';
    --i;
  }

  for(int j = i+1; j < 80; ++j)
  {
    put(stack_[j]);
  }
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned long value) {
  char stack_[80];
  int i = ulongToChar(value, stack_, base);

  for(int j = i+1; j < 80; ++j)
  {
    put(stack_[j]);
  }
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (void* value) {
  Base tmp = base;
  base = hex;
  operator<<((unsigned long) value);
  base = tmp;
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (FGColor fgColor){
  setAttributes(fgColor.color, -1, -1, false);
  this->flush();
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (BGColor bgColor){
  setAttributes(-1, bgColor.color, -1, false);
  this->flush();
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (Blink blink){
  setAttributes(-1, -1, blink.blink, true);
  this->flush();
  return *this;
}

/** \todo implementieren **/
O_Stream& endl (O_Stream& os) {
  os.put('\n');
  os.flush();
  return os;
}

/** \todo implementieren **/
O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}

/** \todo implementieren **/
O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}

/** \todo implementieren **/
O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}

/** \todo implementieren **/
O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

O_Stream& flush (O_Stream& os) {
  os.flush();
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
