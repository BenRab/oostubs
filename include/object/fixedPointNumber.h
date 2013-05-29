
#ifndef FPN_HEADER
#define FPN_HEADER

#include "device/cgastr.h"


/** \brief This class enclose a fixed point number.
 * 
 * 
 */
typedef struct SFixedPointNumber{
  /// FPN with 21 bin digits before and 10 after dot
  int iValue;
  
  SFixedPointNumber(): iValue(0){
  }
  
  SFixedPointNumber(SFixedPointNumber* pVal): iValue(pVal->iValue){
  }
  
  SFixedPointNumber(int iValueV): iValue(iValueV){
  }
  
  SFixedPointNumber neg();
  SFixedPointNumber pow(SFixedPointNumber uPower);
  SFixedPointNumber sqrt();
  SFixedPointNumber root(SFixedPointNumber uPower);
  
  SFixedPointNumber operator+(const SFixedPointNumber& uRight);
  SFixedPointNumber operator-(const SFixedPointNumber& uRight);
  SFixedPointNumber operator*(const SFixedPointNumber& uRight);
  SFixedPointNumber operator/(const SFixedPointNumber& uRight);
  
  SFixedPointNumber operator^(const SFixedPointNumber& uRight);
  SFixedPointNumber operator%(const SFixedPointNumber& uRight);

  SFixedPointNumber& operator+=(const SFixedPointNumber& uRight);
  SFixedPointNumber& operator-=(const SFixedPointNumber& uRight);
  
  SFixedPointNumber operator+();
  SFixedPointNumber operator-();
  
  float toFloat();
  void  fromFloat(float fValue);
}SFixedPointNumber; 


SFixedPointNumber genFPN(int iBefore, unsigned int uiAfter);
SFixedPointNumber genFPN(char cSignum, int iBefore, unsigned int uiAfter);

O_Stream& operator << (O_Stream& aStream, SFixedPointNumber aFPN);

#endif
