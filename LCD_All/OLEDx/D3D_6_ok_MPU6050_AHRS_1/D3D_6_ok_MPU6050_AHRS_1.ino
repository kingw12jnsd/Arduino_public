#include "MyObj.h"
#include "bIMU.h"
void setup() {
  //------------------------------------------------
  lgsetup(F("AVW_BOX_Nano_WiFi ..."));
  //------------------------------------------------
  oled_Init();
  MPU6050_setup();
  //------------------------------------------------
  D3D_load();
  //------------------------------------------------
}
void loop() {
  //----------------------------------------
  IMU_loop();IMU_show();
  D3D_loop_run();
  //----------------------------------------
  delay(20);
  //----------------------------------------
}