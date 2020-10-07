#include <SPI.h>
#include "FrameBuffer.h"

const int dataPin = D7;
const int clockPin = D5;
const int latchPin = D0;
FrameBuffer buff;

uint8_t currentLayer = 0;
long lastMillis = 0;

void setup()  {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  Serial.begin(115200);

  buff = FrameBuffer();
  // buff.setPixel(true, 0, 0, 0);
  // buff.setPixel(true, 1, 1, 1);
  // buff.setPixel(true, 2, 2, 2);
  // buff.setPixel(true, 3, 3, 3);
  // buff.setHorizontalLayer(true, 3);
}

void loop() {
  if (millis() - lastMillis > 100) {
    buff.clear();
    buff.setHorizontalLayer(true, currentLayer);
    currentLayer = (currentLayer + 1) % NUMBER_OF_LAYERS;

    lastMillis = millis();
  }

  render();
}


void render() {
  for (int layer = 0; layer < NUMBER_OF_LAYERS; layer++) {
    digitalWrite(latchPin, LOW);
    std::vector<uint8_t> inputs = buff.TranslateLayerFromBitset(layer);

    Serial.printf("layer: %d ", layer);

    for (int j = 0; j < inputs.size(); j++){
      Serial.print(inputs[j], BIN);
      Serial.print(" ");
      SPI.transfer(inputs[j]);
    }

    Serial.print("\n");

    digitalWrite(latchPin, HIGH);
  }

  Serial.print("\n");
}