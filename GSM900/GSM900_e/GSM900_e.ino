#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LCD5110_Graph.h>
//-------------------------------------------------------------------------
LCD5110 myGLCD(3,4,5,6,7);
extern uint8_t SmallFont[];
//-------------------------------------------------------------------------
TinyGPSPlus gps;
SoftwareSerial	GpsSerial(10, 13); // RX, TX
SoftwareSerial	mySerial(11,12);
//-------------------------------------------------------------------------
//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(50);
  BBKLCDShow();  delay(1000); 
  UpdLCDShow();  delay(1000); 
  //-------------------------------------------------------------------------
  Serial.begin(115200);
  GpsSerial.begin(4800);
  delay(1000); 
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 500;//5s
//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  NoowTime = millis();
  //-------------------------------------------------------------------------
  feedgps();
  //-------------------------------------------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    //-------------------------------------------------------------------------
    GpsValueRun();
    GpsLCDShow();
    SerialShow();
    //-------------------------------------------------------------------------
  }
  //-------------------------------------------------------------------------
}
