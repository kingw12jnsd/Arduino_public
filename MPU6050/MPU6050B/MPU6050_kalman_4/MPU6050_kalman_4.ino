

void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_WiFi ...");
  MPU6050_setup();
  Kalman_setup();
  //------------------------------------------------
}

void loop() {
  //------------------------------------------------
  Kalman_loop(); Kalman_show();
  //------------------------------------------------
  delay(10);
}
