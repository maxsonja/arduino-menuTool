#include "Arduino.h"

//get center coords for printing
byte getMiddle(byte length, byte line){
  if(length%2>0)length++;
  line>>=1;
  length>>=1;
  if(length>line)return 0;
  return line-length;
}
