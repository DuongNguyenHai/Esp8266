// Nguyen Hai Duong
// Dec 10 2016

// Feature :
// 1. Auto reconnect connection (its default of Library)
// 2. Catch event WiFi connected and disconnected
//
// Library : ESP8266 as Arduino
// Program was modified from example of ESP8266 Library (https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/generic-examples.md)
// Reference :
// https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/readme.md#quick-start

#include <ESP8266WiFi.h>

#define ssid "******"  // WiFi name
#define password "******" // password

WiFiEventHandler gotIpEventHandler, disconnectedEventHandler; // inital event handle

void setup() {

  Serial.begin(115200);
  Serial.println();

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
  {
    Serial.println("WiFi disconnected");
  });

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

}

void loop() {
  delay(5000);
}
