/*
1.Tricycle三轮小车
2.MEGA2560
3.Serial  是log输出
4.Serial1 是RC遥控命令输入输出
5.
*/

float cm = 0;

void setup() {
  //-----------------------------
  log_setup();
  APC220_setup();
  //-----------------------------
  //IR_Setup(53, 51, 49);
  BKMOTO_Init(22, 24, 26, 28, 30, 32);
  Interrupt_setIn();//车轮码盘中断
  //-----------------------------
  lg("$JML,CAR,SAN,0,0,0,0,0,0;");lg();
  //-----------------------------
  lg("Moto_Run_Init()");lg();
  Moto_Run_Init();  
  lg("Moto_Run_Show()");lg();
  Moto_Run_Show();  
  //-----------------------------
}
void loop() {
  //---------------------------------
  //IR_Loop();  IR_Show(false);
  //---------------------------------
  Moto_Run_loop();
  delay(50);
  //---------------------------------
  //---------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    APC220_Feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

