void setup() {
  //--------------------------------------------
  lgsetup("Morse Code Exp!");
  Blink_Init(13);
  //--------------------------------------------
  //Morse_Test(0);
  //--------------------------------------------
  
  //--------------------------------------------
}
void loop() {
  smartDelay(1000);
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================