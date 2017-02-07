// Nguyen Hai Duong
// Jan 5 2017
//
// DS1302_Serial_Easy (C)2010 Henning Karlsen
// Adopted for DS1302RTC library by Timur Maksimov 2014
//
// A quick demo of how to use my DS1302-library to
// quickly set and read time & date information
// DS1302 :  CE pin    -> Arduino Digital 4
//          I/O pin   -> Arduino Digital 5
//          SCLK pin  -> Arduino Digital 6


#include <Time.h>
#include <DS1302RTC.h>

// Set pins:  CE/Reset, IO/Data, CLK
DS1302RTC RTC(5, 13, 12);

// time setting : seconds/minutes/hours/day of week/day/month/(year-1970)
tmElements_t tm_set = {1,40,16,4,5,1,2017-1970};

void PrintDateTime(tmElements_t tm);

void setup()
{
   // Setup Serial connection
   Serial.begin(115200);

   Serial.println("DS1302RTC Read Test");
   Serial.println("-------------------");

   Serial.println("RTC module activated");
   Serial.println();
   delay(500);

   if (RTC.haltRTC()) {
      Serial.println("The DS1302 is stopped.  Setting default time.");
      // Setting time and date
      if(RTC.set(makeTime(tm_set)) == 0) { // Success
         Serial.print("RTC set to: ");
         PrintDateTime(tm_set);
      } else {
         Serial.println("RTC set error ");
      }
   }

   if (!RTC.writeEN()) {
      Serial.println("The DS1302 is write protected. This normal.");
      Serial.println();
   }

}

void loop()
{
   tmElements_t tm;

   Serial.print("UNIX Time: ");
   Serial.print(RTC.get());
   Serial.print(" ");

   if (! RTC.read(tm)) {
      PrintDateTime(tm);
   } else {
      Serial.println("DS1302 read error!  Please check the circuitry.");
      Serial.println();
      delay(1000);
   }

   // Wait one second before repeating :)
   delay (1000);
}

void print2digits(int number) {
   if (number >= 0 && number < 10)
      Serial.write('0');
   Serial.print(number);
}

void PrintDateTime(tmElements_t tm) {
   Serial.print("Time = ");
   print2digits(tm.Hour);
   Serial.write(':');
   print2digits(tm.Minute);
   Serial.write(':');
   print2digits(tm.Second);
   Serial.print(", Date (D/M/Y) = ");
   Serial.print(tm.Day);
   Serial.write('/');
   Serial.print(tm.Month);
   Serial.write('/');
   Serial.print(tmYearToCalendar(tm.Year));
   Serial.print(", DoW = ");
   Serial.print(dayStr(tm.Wday));
   Serial.println();
}
