void setup() {
  //--------------------------------------------------
  //!!!必须不然硬件烧毁!!!
  pinMode(9, INPUT);  pinMode(12, INPUT);
  //--------------------------------------------
  lgsetup("8x8 LED Matrix Test!Net Line");
  //wifi_Init(true, true, false); //lg,AP,test
  //--------------------------------------------
  RGB8X8_setup();
  //--------------------------------------------
  //Set_Weather();
  //--------------------------------------------
}
void loop() {
  //RGB8X8_loop();
  //--------------------------------------------
  r_n(300); r_s(300); r_n(300); r_s(300); r_n(300); r_s(300);
  //--------------------------------------------
  delay(300);r_love(300);delay(300);
  //--------------------------------------------
  r_t();
  //--------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); wfs_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
