#include <SPI.h>
#include "FrameBuffer.h"

const int dataPin = D7;
const int clockPin = D5;
const int latchPin = D0;
FrameBuffer buff;

// uint8_t currentLayer = 0;
// uint8_t dir = 1;
// uint8_t indexx = 0;
long lastMillis = 0;

void setup()  {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  Serial.begin(115200);

  buff = FrameBuffer();
  // buff.setPixel(true, 0, 2, 0);
  // buff.setPixel(true, 1, 1, 1);
  // buff.setPixel(true, 2, 2, 2);
  // buff.setPixel(true, 3, 3, 3);
  // buff.setHorizontalLayer(true, 3);
}

void loop() {
  if (millis() - lastMillis > 150) {
    buff.draw2DLine(true, 0, 0, 3, 2, 3);
    // buff.setPixelByIndex(true, indexx, 0);
    // indexx= indexx+1;
    // if (indexx == 16) indexx = 0;

    // index = (index + 1) % (uint8_t)16;
    
  //   for(uint8_t layer = 0; layer < NUMBER_OF_LAYERS; layer++) {
  //     if (layer <= currentLayer) {
  //       buff.setHorizontalLayer(true, layer);
  //     } else {
  //       buff.setHorizontalLayer(false, layer);
  //     }
  //   }

  //   if (currentLayer == 3) {
  //     dir = -1;
  //   }

  //   if (currentLayer == 0) {
  //     dir = 1;
  //   }

  //   currentLayer = (currentLayer + dir);

    lastMillis = millis();
  }

  render();
}


void render() {
  for (int layer = 0; layer < NUMBER_OF_LAYERS; layer++) {
    digitalWrite(latchPin, LOW);
    std::vector<uint8_t> inputs = buff.TranslateLayerFromBitset(layer);

    Serial.printf("layer: %d ", layer);

    for (int j = inputs.size() - 1; j >=0 ; j--){
      Serial.print(inputs[j], BIN);
      Serial.print(" ");
      SPI.transfer(inputs[j]);
    }

    Serial.print("\n");

    digitalWrite(latchPin, HIGH);
  }

  Serial.print("\n");
}