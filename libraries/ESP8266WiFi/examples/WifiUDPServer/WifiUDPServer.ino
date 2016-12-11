// Nguyen Hai Duong
// Dec 10 2016

// Feauture :
// 1. Auto reconnect connection
//    In case the connection is lost, ESP8266 will automatically reconnect to the last used access point, once it is again available. (its default of ESP8266 Station)
// 2. Set static IP
// 3. Create a server use UDP protocol
//
// Library : ESP8266 as Arduino
// Program was modified from example of ESP8266 (https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/udp-examples.md)
// Reference :
// https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/readme.md#quick-start

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;         // Use WiFiClient class to create UDP connections
#define port 8888
#define ssid "******"  // WiFi name
#define password "******" // password

IPAddress ip_static(192, 168, 0, 13);
IPAddress ip_gateway(192,168,0,1);
IPAddress ip_subnet(255,255,255,0);

char incomingPacket[255];  // buffer for incoming packets
char  replyPacekt[] = "Hi there! Got the message :-)";

void setup() {

  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  // DHCP was used by default. To set static ip use config line below.
  // bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000);
  WiFi.config(ip_static, ip_gateway, ip_subnet); // set static ip. ignore this line to use DHCP

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(port);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), port);
}

void loop() {

  int packetSize = Udp.parsePacket();

  if (packetSize) {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacekt);
    Udp.endPacket();
  }
}
