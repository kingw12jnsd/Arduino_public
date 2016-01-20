//===================================================================
void setup() {
  //-------------------------------------
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Log_setup();
  GpuClear();
  //-------------------------------------
  APC220_setup();
  //-------------------------------------
  Timer_setup();
  //-------------------------------------
}
void loop() {
  //-------------------------------------
  APC220_Feed();
  Timer_loop();
  //-------------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    APC220_Feed();
    Timer_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===================================================================