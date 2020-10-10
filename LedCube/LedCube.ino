#include <SPI.h>
#include "FrameBuffer.h"

#include <ESP8266WiFi.h>

const char* ssid = "D IOT";
const char* password = "93a8mely";

const int dataPin = D7;
const int clockPin = D5;
const int latchPin = D0;
FrameBuffer buff;

 uint8_t currentLayer = 0;
 uint8_t dir = 1;
long lastMillis = 0;

//WiFiServer server(80);

void setup()  {
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);

  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  Serial.begin(115200);

  buff = FrameBuffer();

  // Start the server
//  server.begin();

//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//
//  // Start the server
//  server.begin();
//  Serial.println("Server started");
//
//  // Print the IP address
//  Serial.println(WiFi.localIP());
  // buff.setPixel(true, 0, 2, 0);
  // buff.setPixel(true, 1, 1, 1);
  // buff.setPixel(true, 2, 2, 2);
  // buff.setPixel(true, 3, 3, 3);
  // buff.setHorizontalLayer(true, 3);

//  buff.drawLine(true, -2, 0, 0, 0, 0, 3);
//  buff.drawLine(true, 0, 3, 0, 0, 3, 3);
//  buff.drawLine(true, 3, 3, 0, 3, 3, 3);
//  buff.drawLine(true, 3, 0, 0, 3, 0, 3);
//  buff.drawLine(true, 0, 0, 0, 0, 3, 0);
//  buff.drawLine(true, 3, 0, 0, 3, 3, 0);
//  buff.drawLine(true, 0, 0, 0, 3, 0, 0);
//  buff.drawLine(true, 0, 3, 0, 3, 3, 0);
//  buff.drawLine(true, 0, 0, 3, 0, 3, 3);
//  buff.drawLine(true, 0, 0, 3, 3, 0, 3);
//  buff.drawLine(true, 3, 0, 3, 3, 3, 3);
//  buff.drawLine(true, 0, 3, 3, 3, 3, 3);
}

void loop() {
//  buff.drawLine(true, 0, 0, 0, 0, 0, 3);
//  buff.drawLine(true, 0, 3, 0, 0, 3, 3);
//  buff.drawLine(true, 3, 3, 0, 3, 3, 3);
//  buff.drawLine(true, 3, 0, 0, 3, 0, 3);
//  buff.drawLine(true, 0, 0, 0, 0, 3, 0);
//  buff.drawLine(true, 3, 0, 0, 3, 3, 0);
//  buff.drawLine(true, 0, 0, 0, 3, 0, 0);
//  buff.drawLine(true, 0, 3, 0, 3, 3, 0);
//  buff.drawLine(true, 0, 0, 3, 0, 3, 3);
//  buff.drawLine(true, 0, 0, 3, 3, 0, 3);
//  buff.drawLine(true, 3, 0, 3, 3, 3, 3);
//  buff.drawLine(true, 0, 3, 3, 3, 3, 3);
//    buff.setAll(true);

  if (millis() - lastMillis > 150) {
   
     for(uint8_t layer = 0; layer < NUMBER_OF_LAYERS; layer++) {
       if (layer <= currentLayer) {
         buff.setHorizontalLayer(true, layer);
       } else {
         buff.setHorizontalLayer(false, layer);
       }
     }

     if (currentLayer == 3) {
       dir = -1;
     }

     if (currentLayer == 0) {
       dir = 1;
     }

     currentLayer = (currentLayer + dir);

    lastMillis = millis();
  }
  render();

//  // Check if a client has connected
//  WiFiClient client = server.available();
//  if (!client) {
////    Serial.println("failure to comply");
//    return;
//  }
//  
//  // Wait until the client sends some data
//  Serial.println("new client");
//  while(!client.available()){
//    delay(1);
//  }
//  
//  // Read the first line of the request
//  String req = client.readStringUntil('\r');
//  Serial.println(req);
//  client.flush();
//
// 
//  
//  client.flush();
//
//  // Prepare the response
//  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nOK</html>\n";
//
//  // Send the response to the client
//  client.print(s);
//  delay(1);
//  Serial.println("Client disonnected");

}


void render() {
  for (int layer = 0; layer < NUMBER_OF_LAYERS; layer++) {
    digitalWrite(latchPin, LOW);
    std::vector<uint8_t> inputs = buff.TranslateLayerFromBitset(layer);

    // Serial.printf("layer: %d ", layer);

    for (int j = inputs.size() - 1; j >=0 ; j--){
      // Serial.print(inputs[j], BIN);
      // Serial.print(" ");
      SPI.transfer(inputs[j]);
    }

    // Serial.print("\n");

    digitalWrite(latchPin, HIGH);
  }

  // Serial.print("\n");
}
