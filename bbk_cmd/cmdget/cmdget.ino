void setup()
{
  Serial.begin(115200);
  Serial.println("gps03SoftwareSerial_uno_ok3");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GetShow2();
  //-------------------------------------------------------------------------
}

static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available()>0)
  {
    char c = Serial.read();
    SerialExp(c);    
  }
  return true;
  //-------------------------------------------------------------------------
}