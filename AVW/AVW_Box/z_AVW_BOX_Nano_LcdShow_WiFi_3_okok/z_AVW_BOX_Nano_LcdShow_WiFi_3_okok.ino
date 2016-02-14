/*===================================================================
1.电量测量盒子
2.AcMeter_60A
//=================================================================*/
//===================================================================
void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_WiFi ...");
  //------------------------------------------------
  LCD1602_setup(); LCD1602_Clear();
  LCD1602_Show(0, 0, F("AVW_BOX_NanoWiFi!"));
  //------------------------------------------------
  AVW_Setup();
  //------------------------------------------------
  wifi_Init(false); lewei_time_init();
  //------------------------------------------------
  RunTimeLoop();
  BufferClear(); myAvw_Ask(); smartDelayAvw(200);
  AVW_Exp(); AVW_Show(); LCD_Show_AVW();
  Lewei_Report(); lewei_time_exp();
  //------------------------------------------------
}
void loop() {
  //---------------------------------
  AVW_Loop();
  LCD_Loop();
  RunTimeLoop();
  Lewei_Loop();
  //---------------------------------
}
//===============================================
static void smartDelayAvw(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    myAvw_loop();
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
