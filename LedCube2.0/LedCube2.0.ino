#include <SPI.h>
#include "FrameBuffer.h"

int dataPin = D7;
int clockPin = D5;
int latchPin = D0;
FrameBuffer buff;


void setup()  {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

//  Serial.begin(9600);

  buff = FrameBuffer();
//  buff.SetBit(true, 0, 0, 0);
//  buff.SetBit(true, 1, 1, 1);
//  buff.SetBit(true, 2, 2, 2);
//  buff.SetBit(true, 3, 3, 3);
}

void loop() {
  // buff.SetBitsInFullLayer(true, 0);
  // buff.Draw2DLine(true, 0, 0, 3, 1, 0);
  buff.SetBit(true, 2, 3, 0);
  
  // buff.SetBitsInFullLayer(true, 1);
  // buff.SetBitsInFullLayer(true, 3);
  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPin, LOW);
    std::vector<uint8_t> inputs = buff.TranslateLayerFromBitset(i);
    for (int j = 0; j < inputs.size(); j++){
      // Serial.print(i);
      // Serial.print(" ");
      // Serial.print(j);
      // Serial.print(" ");
      // Serial.print(char(inputs[j]));
      // Serial.print("\n");
      SPI.transfer(char(inputs[j]));
    // delay(100);
    }
    digitalWrite(latchPin, HIGH);
  }

//  delay(300);

//  buff.SetBitsInFullLayer(false, 0);
//
//  buff.SetBitsInFullLayer(true, 1);
////  buff.SetBitsInFullLayer(true, 3);
//
//  for (int i = 0; i < 4; i++) {
//    digitalWrite(latchPin, LOW);
//    std::vector<uint8_t> inputs = buff.TranslateLayerFromBitset(i);
//    for (int j = 0; j < inputs.size(); j++){
//
//      SPI.transfer(char(inputs[j]));
//    }
//    digitalWrite(latchPin, HIGH);
//    delay(100);
//  }
////
//  delay(300);
}

