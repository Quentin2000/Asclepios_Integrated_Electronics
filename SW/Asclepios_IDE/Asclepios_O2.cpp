#include "Asclepios_O2.h"


void O2_setup() {
  Uart1.begin(9600, SERIAL_8N1, RX1, TX1);
  delay(10);
  if (Uart1.available()){
    Serial.println(F("O2 sensor initialized!"));
  }
}


void O2_acquisition() {
  if (Uart1.available()){
    uint8_t begin_code = Uart1.read();
    delay(10);
    uint8_t state_code = Uart1.read();
    delay(10);
    uint8_t high_code = Uart1.read();
    delay(10);
    uint8_t low_code = Uart1.read();
    delay(10);
    uint8_t check_code = Uart1.read();
    delay(10);
    uint8_t checkk_code = Uart1.read();
    delay(10);
    uint8_t checkkk_code = Uart1.read();
    delay(10);
    uint8_t checkkkk_code = Uart1.read();
    delay(10);
    uint8_t checkkkkk_code = Uart1.read();
    delay(10);

//    Serial.print("begin_code :");
//    Serial.print(begin_code);
//    Serial.print("state_code :");
//    Serial.print(state_code);//    
//    Serial.print(F("O2 high_code = "));
//    Serial.println(high_code);
//    Serial.print(F("O2 low_code = "));
//    Serial.println(low_code);
    
    if(begin_code == 255 && state_code == 134){
 
      O2_val = ((high_code * 256) + low_code) * 0.1 ;
      Serial.print(F("O2 = "));
      Serial.print(O2_val);
      Serial.println(F(" %"));
      }
    }

    else {
      Serial.println(F("Could not find O2 sensor, check wiring!"));
      O2_setup();
    }
    while(Uart1.read()>=0);    //clear buffer
}