#include <Time.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(4800);
  Serial2.begin(9600);
  while (!Serial) {}
  while (!Serial1) {}
  while (!Serial2) {}
  Serial.println("gps03SoftwareSerial_uno_ok3");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GpsRead();
  GpsSetValue();
  //-------------------------------------------------------------------------
  GpsCheck();
  GpsReport();
  //-------------------------------------------------------------------------
}

void SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial2.available()>0)
  {
    SerialExp(Serial2.read());    
  }
  //-------------------------------------------------------------------------
}

void GpsRead()
{
  //-------------------------------------------------------------------------
  while (Serial1.available())
  {
    gps.encode(Serial1.read());
  }
  //-------------------------------------------------------------------------
}
