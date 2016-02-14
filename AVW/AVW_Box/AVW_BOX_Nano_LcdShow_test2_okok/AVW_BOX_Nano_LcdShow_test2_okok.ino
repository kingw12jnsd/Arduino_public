/*===================================================================
1.电量测量盒子
2.AcMeter_60A
//=================================================================*/
//===================================================================
void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_b ...");
  //------------------------------------------------
  AVW_Setup();
  //------------------------------------------------
}
void loop() {
  //---------------------------------
  AVW_Loop();
  //---------------------------------
  lgFeed();myAvw_loop();
  //---------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); myAvw_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
