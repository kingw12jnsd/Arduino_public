/*===================================================================
1.电量测量盒子
2.AcMeter_60A
//=================================================================*/
//===================================================================
void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_b ...");
  //------------------------------------------------
  LCD1602_setup(); LCD1602_Clear(); LCD1602_Show(0, 0, F("AVW_Nano_WiFi!"));  
  //------------------------------------------------
  AVW_Setup();
  //------------------------------------------------
}
void loop() {
  //---------------------------------
  AVW_Loop();
  LCD_Loop(true);
  RunTimeLoop();
  //---------------------------------
  lgFeed();
  //---------------------------------
}
