
#include "object/fixedPointNumber.h"

/// values for output of the digits after dot for  decimal
unsigned int auiValues[10] = { 500000000,
                               250000000,
                               125000000,
                                62500000,
                                31250000,
                                15625000,
                                 7812500,
                                 3906250,
                                 1953125,
                                  976563};

/// number of leading zeros for output of digits after dot for decimal
unsigned char aucValLeadZero[10] = {0,0,0,1,1,1,2,2,2,3};

extern "C" void _pow(float f1, float f2, float& f3);

/** \brief negate the Number
 * 
 */
SFixedPointNumber SFixedPointNumber::neg(){
  SFixedPointNumber uRes(-iValue);
  return uRes;
}

/** \brief power of the Number
 * 
 */
SFixedPointNumber SFixedPointNumber::pow(SFixedPointNumber uPower){
  //Var init
  SFixedPointNumber uRes(0);
  float fResult;
  
  //no negative number
  if(iValue<=0){
    return uRes;
  }
  
  //einfach andere Fkt. nehmen
  _pow(toFloat(), uPower.toFloat(), fResult);
  //und zurueckwandeln
  uRes.fromFloat(fResult);
  
  return uRes;
}

/** \brief sqare root of the Number
 * 
 * Babylonische Methode
 */
SFixedPointNumber SFixedPointNumber::sqrt(){
  //Var init
  SFixedPointNumber uRes(0);
  SFixedPointNumber uOld(0);
  SFixedPointNumber uOne(0x400);
  SFixedPointNumber uTwo(0x800);
  
  //no negative number!
  if(iValue<0){
    return uRes;
  }
  
  uRes.iValue = this->iValue / 2;
  while(uRes.iValue != uOld.iValue){
    uOld.iValue = uRes.iValue;
    uRes        = (uRes + ((*this)/uRes)) / uTwo;  
  }
  
  return uRes;
}


/** \brief any root of the Number
 * 
 */
SFixedPointNumber SFixedPointNumber::root(SFixedPointNumber uPower){
  //Var init
  SFixedPointNumber uOne(0x400);
  SFixedPointNumber uRes(0);
  
  //no negative number!
  if(iValue<0){
    return uRes;
  }
  
  //inverse bilden und Potenz...
  uPower = uOne/uPower;
  return pow(uPower);
}

/** \brief addition of two FPN
 * 
 * 
 */
SFixedPointNumber SFixedPointNumber::operator+(const SFixedPointNumber& uRight){
  SFixedPointNumber uRes(iValue+uRight.iValue);
  return uRes;
}

/** \brief subtraction of two FPN
 * 
 * 
 */
SFixedPointNumber SFixedPointNumber::operator-(const SFixedPointNumber& uRight){
  SFixedPointNumber uRes(iValue-uRight.iValue);
  return uRes;
}

/** \brief multiply number
 * 
 */
SFixedPointNumber SFixedPointNumber::operator*(const SFixedPointNumber& uRight){
  SFixedPointNumber uRes;
  
  uRes.iValue = (int)(((long long int)this->iValue)*((long long int)uRight.iValue)>>10);
  
  return uRes;
}

/** \brief divide number
 * 
 */
SFixedPointNumber SFixedPointNumber::operator/(const SFixedPointNumber& uRight){
  //Var init
  SFixedPointNumber uRes;
  
  uRes.iValue = (this->iValue/(uRight.iValue>>5))<<5;
  
  return uRes;
}

/** \brief calculate power
 * 
 */
SFixedPointNumber SFixedPointNumber::operator^(const SFixedPointNumber& uRight){
  return this->pow(uRight);
}

/** \brief calculate root
 * 
 */
SFixedPointNumber SFixedPointNumber::operator%(const SFixedPointNumber& uRight){
  return this->root(uRight);
}


/** \brief add to current Value
 * 
 */
SFixedPointNumber& SFixedPointNumber::operator+=(const SFixedPointNumber& uRight){
  iValue+=uRight.iValue;
  return *this;
}

/** \brief subtract from current Value
 * 
 */
SFixedPointNumber& SFixedPointNumber::operator-=(const SFixedPointNumber& uRight){
  iValue-=uRight.iValue;
  return *this;
}



/** \brief dummy
 * 
 */
SFixedPointNumber SFixedPointNumber::operator+(){
  SFixedPointNumber uRes(this);
  return uRes;
}

/** \brief negate number
 * 
 */
SFixedPointNumber SFixedPointNumber::operator-(){
  return neg();
}

/** \brief convert SFixedPointNumber to float
 * 
 */
float SFixedPointNumber::toFloat(){
  //Var init
  unsigned int uiRes;
  unsigned int uiValue;
    signed int  iPos;
  unsigned int uiBiasedExp;
  
  //Sonderfall 0
  if(iValue == 0){
    return 0.0f;
  }
  
  //Vorzeichen
  if(iValue<0){
    uiValue=(unsigned int)-iValue;
    uiRes = 0x80000000;
  }else{
    uiValue=(unsigned int)iValue;
    uiRes = 0;
  }
  
  //hoechste 1Bit finden
  iPos = 30;
  while(0 == ((1<<iPos)&uiValue)){
    iPos--;
  }
  
  //Exponent bestimmen
  uiBiasedExp = 127 + (iPos-10);
  uiRes       = uiRes | ((uiBiasedExp & 0xFF) << 23);
  
  //Mantisse ueberfuehren
  if(iPos>=23){
    uiRes     = uiRes | ((uiValue>>(iPos-23)) & 0x007FFFFF);
  }else{
    uiRes     = uiRes | ((uiValue<<(23-iPos)) & 0x007FFFFF);
  }
  
  return *((float*)&uiRes);
}

/** \brief convert float to SFixedPointNumber
 * 
 */
void  SFixedPointNumber::fromFloat(float fValue){
  //Var init
  unsigned int uiFValue;
    signed int  iPos;
  
  uiFValue = *((unsigned int*)&fValue);
  
  //Sonderfaelle abhandeln
  if(uiFValue==0 || 0x7F800000==(uiFValue&0x7F800000) || 0==(uiFValue&0x7F800000)){
    iValue=0;
  }
  
  //Versatz bestimmen
  iPos = ((uiFValue&0x7F800000)>>23)+10 - 127;
  
  //zurecht schieben
  if(iPos>=23){
    iValue = (int)(((uiFValue&0x007FFFFF) | 0x00800000) << (iPos-23));
  }else{
    iValue = (int)(((uiFValue&0x007FFFFF) | 0x00800000) >> (23-iPos));
  }
  
  //Vorzeichen
  if(uiFValue&0x80000000){
    iValue=-iValue;
  }
}



/** \brief generate a SFixedPointNumber from two parts, without extra signum
 * 
 */
SFixedPointNumber genFPN(int iBefore, unsigned int uiAfter){
  //Var init
  SFixedPointNumber uRes(iBefore<<10);
  unsigned char ucPos;
  unsigned int uiTmp;
  int          iTmpAfter;
  
  //3 Nachkommastellen versuchen -> ,200 -> 200 -> 200000000
  uiAfter *= 1000000;
  uiTmp     = 0;
  iTmpAfter = 0;
  for(ucPos = 0; ucPos<10; ucPos++){
    if(auiValues[ucPos]+uiTmp<=uiAfter){
      uiTmp     += auiValues[ucPos];
      iTmpAfter += 1 << (9-ucPos);
    }
  }
  //bei negativer Zahl das zweierkomplement nehmen
  if(iBefore<0){
    iTmpAfter = -iTmpAfter;
  }
  uRes.iValue += iTmpAfter;
  
  return uRes;
}

/** \brief generate a SFixedPointNumber from three parts, with extra signum
 * 
 */
SFixedPointNumber genFPN(char cSignum, int iBefore, unsigned int uiAfter){
  //Var init
  SFixedPointNumber uRes(iBefore<<10);
  unsigned char ucPos;
  unsigned int uiTmp;
  int          iTmpAfter;
  
  //3 Nachkommastellen versuchen -> ,200 -> 200 -> 200000000
  uiAfter *= 1000000;
  uiTmp     = 0;
  iTmpAfter = 0;
  for(ucPos = 0; ucPos<10; ucPos++){
    if(auiValues[ucPos]+uiTmp<=uiAfter){
      uiTmp     += auiValues[ucPos];
      iTmpAfter += 1 << (9-ucPos);
    }
  }
  //bei negativer Zahl das zweierkomplement nehmen
  if(iBefore<0 || cSignum<0){
    iTmpAfter = -iTmpAfter;
  }
  uRes.iValue += iTmpAfter;
  
  return uRes;
}

/**
 * 
 * 
 * calculation is ld(1024)/ld(ucBasis)
 */
unsigned char getPrecision(unsigned char ucBasis){
  if(ucBasis>32){
    return 2;
  }
  if(ucBasis>10){
    return 3;
  }
  if(ucBasis>5){
    return 4;
  }
  if(ucBasis>3){
    return 5;
  }
  if(ucBasis==3){
    return 7;
  }
  
  return 10;
}

/** \brief output operation
 * 
 */
O_Stream& operator << (O_Stream& aStream, SFixedPointNumber aFPN) {
  //Var init
  unsigned char ucBasis;
  unsigned char ucLeadingZeros;
  unsigned char ucPos;
  unsigned int  uiSum;
  char cSignum;
  
  //Vorzeichen festhalten (fuer -0,... wichtig)
  cSignum = (aFPN.iValue<0)?-1:1;

  //vorderen Teil ausgeben
  if(aFPN.iValue<0){
    uiSum = ((-aFPN.iValue)&0x3FF);
    aFPN.iValue += uiSum;
    aStream << "-" << ((-aFPN.iValue) >> 10) << ".";
  }else{
    aStream << "+" << (aFPN.iValue >> 10) << ".";
  }
  
  //abschneiden
  if(cSignum<0){
    aFPN.iValue = uiSum;
  }
  aFPN.iValue = aFPN.iValue & 0x3FF;
  
  ucBasis = (unsigned char)(aStream.base);
  
  if(aFPN.iValue!=0){
    if(10==ucBasis){
      //summe erstellen
      uiSum = 0;
      ucPos = 0;
      while(aFPN.iValue!=0){
        if(aFPN.iValue & 1){
          ucLeadingZeros = aucValLeadZero[9-ucPos];
          uiSum += auiValues[9-ucPos];
        }
        aFPN.iValue = aFPN.iValue >> 1;
        ucPos++;
      }
      
      //fuehrende Nullen ausgeben
      while(ucLeadingZeros!=0){
        ucLeadingZeros--;
        aStream << "0";
      }
      
      //Text ausgeben
      aStream << uiSum;
      
    }else{
      for(ucPos=0;ucPos<getPrecision(ucBasis);ucPos++){
        aFPN.iValue*=ucBasis;
        if(aFPN.iValue<0x400){
          aStream << "0";
        }
      }
      aFPN.iValue = aFPN.iValue>>10;
      aStream << aFPN.iValue;
    }
  }else{
    if(10==ucBasis){
      aStream << "000000000";
    }else{
      aStream << "0";
    }
  }
  
  return aStream;
}

