//=====================================================
void setup() {
  //------------------------------------------
  int d[4] = {2, 3, 4, 5};//选位
  int p[8] = {6, 7, 8, 9, 10, 11, 12, 13};//数码段
  Tube4_Init(d, p);
  Tube_set(-1, 0, 3, 4, 2);
  //------------------------------------------
}
void loop() {
  //------------------------------------------
  Tube4_loop();
  //------------------------------------------
}
