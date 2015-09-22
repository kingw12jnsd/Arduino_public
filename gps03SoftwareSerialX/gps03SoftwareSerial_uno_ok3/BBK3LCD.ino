unsigned long ShowTime = millis(), ShowTimeKey = 1000;//5s
void GpsasdfasdfShow() 
{
  //-------------------------------------------------------------------------
  if( millis() - ShowTime < ShowTimeKey) return; 
   ShowTime = millis();
  //-------------------------------------------------------------------------
  GpsSetValue();
  StrReport();
  //GpsLCDShow();
  //-------------------------------------------------------------------------
}



void GpsLCDShow(){
  //-------------------------------------------------------------------------
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(gs.sDate);
  Serial.println(gs.sTime);
  Serial.println(gs.sLats);
  Serial.println(gs.sLons);
  Serial.print("h=");
  Serial.println(gs.sHigh);
  Serial.print("s=");
  Serial.println(gs.sSped);
  Serial.print("f=");
  Serial.println(gs.sFans);  
  Serial.print("n=");
  Serial.println(gs.sGpsn);
  Serial.print("r=");
  Serial.println(gs.sRads);
  Serial.print("gps.sentencesWithFix()=");
  Serial.println(gps.sentenceHasFix);
  //-------------------------------------------------------------------------
}
