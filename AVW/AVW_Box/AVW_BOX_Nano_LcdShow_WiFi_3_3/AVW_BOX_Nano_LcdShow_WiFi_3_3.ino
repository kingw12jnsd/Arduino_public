/*===================================================================
1.电量测量盒子
2.AcMeter_60A
//=================================================================*/
//===================================================================
void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_WiFi ...");
  //------------------------------------------------
  wifi_Init(true); lewei_time_init();
  //------------------------------------------------
}
void loop() {
  //---------------------------------
  RunTimeLoop();
  Lewei_Loop();
  //---------------------------------
}
//===============================================
static void smartDelayAvw(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //myAvw_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
static void smartDelayWifi(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    wfs_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
