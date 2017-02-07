#include <ESP8266WiFi.h>

#define ssid "******"  // network name
#define password "******" // password

void setup()
{
   Serial.begin(115200);
   Serial.println();

   Serial.printf("Connecting to %s ", ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(500);
      Serial.print(".");
   }
   Serial.println(" connected");
}


void loop()
{
   String time = getTime();
   Serial.println(time);
   delay(5000);
}

String getTime() {

   WiFiClient client;
   while (!client.connect("google.com", 80)) {
      Serial.println("connection failed, retrying...");
      delay(5000);
   }

   client.print(String("GET /") + " HTTP/1.1\r\n" +
              "Connection: close\r\n" +
              "\r\n"
            );

   while (client.connected())
   {
      if (client.available())
      {
         if (client.read() == '\n') {
            if (client.read() == 'D') {
               if (client.read() == 'a') {
                  if (client.read() == 't') {
                     if (client.read() == 'e') {
                        if (client.read() == ':') {
                          client.read();
                          String theDate = client.readStringUntil('\r');
                          client.stop();
                          return theDate;
                        }
                     }
                  }
               }
            }
         }
      }
   }
   return "NULL";
}
