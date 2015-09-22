//------------------------------------------------------------------
time_t loctime = 0,utctime = 0;
int YY,MD,DD,HT,MT,ST;//year,month,day,hour,min,second
float WW,JJ,HH,VV,FX;//lat,long,high,speed,fangxiang
//----------------------------------------------------------------
int SN,SR;//sat_number,sat_hdop
bool KK;//GPS_Location_flag
char KT;//GPS_Location_type
//----------------------------------------------------------------
char sDate[12],tDate[32],sTime[12];//YMDHMS
char sLats[12],sLons[12],sHigh[8],sSped[8],sFans[8];//WJHVF
char cLock[2],cType[2],sGpsn[4],sRads[8],sSeal[8];//KK;KT;SN;SR;HZ;
//------------------------------------------------------------------
void GpsValueRun(){
  //----------------------------------------------------------------
  YY = gps.date.year();
  MD = gps.date.month();
  DD = gps.date.day();
  HT = gps.time.hour();
  MT = gps.time.minute();
  ST = gps.time.second();
  Serial.println(gps.date.year());
  Serial.println(gps.time.second());
  //----------------------------------------------------------------
  setTime( HT,MT,ST,DD,MD,YY ); 
  //----------------------------------------------------------------
  utctime = now();
  loctime = utctime + 8*3600;
  Serial.println(utctime);
  Serial.println(loctime);
  //----------------------------------------------------------------
  YY = year(loctime);
  MD = month(loctime);
  DD = day(loctime);
  HT = hour(loctime);
  MT = minute(loctime);
  ST = second(loctime);
  //----------------------------------------------------------------
  KK = gps.fixhave;
  KT = gps.fixtype;
  WW = gps.location.lat();
  JJ = gps.location.lng(); 
  //----------------------------------------------------------------
  HH = gps.altitude.meters();
  FX = gps.course.deg();
  VV = gps.speed.kmph();
  SN = gps.satellites.value();
  SR = gps.hdop.value();
  //----------------------------------------------------------------
}
void GpsStringRun(){
  //----------------------------------------------------------------
  //dtostrf(KK,1,0,cLock);
  //dtostrf(KT,1,0,cType);
  sprintf(cLock,"%02d",KK);
  sprintf(cType,"%02d",KT);
  //----------------------------------------------------------------
  //sprintf(sDate,"%02d/%02d/%02d",YY,MD,DD);  
  sprintf(sDate,"%02d/%02d",MD,DD);
  sprintf(sTime,"%02d:%02d:%02d",HT,MT,ST);
  sprintf(tDate,"%02d/%02d/%02d %02d:%02d:%02d",YY,MD,DD,HT,MT,ST);
  //----------------------------------------------------------------
  dtostrf(WW,3,6,sLats);
  dtostrf(JJ,3,6,sLons);
  dtostrf(HH,3,1,sHigh);
  dtostrf(VV,3,1,sSped);
  dtostrf(FX,3,1,sFans);
  dtostrf(SN,2,0,sGpsn);
  dtostrf(SR,3,0,sRads);
  //----------------------------------------------------------------
}

static bool feedgps()
{
  //----------------------------------------------------------------
  while (GpsSerial.available())
  {
    if (gps.encode(GpsSerial.read()))
      return true;
  }
  return false;
  //----------------------------------------------------------------
}




