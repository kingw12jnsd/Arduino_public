//===================================================================
#include "ax.h"
//Timer t;//时间类
//float timeKey = 20; //滤波法采样时间间隔毫秒
//===================================================================
void setup() {
  //-------------------------------------
  lgsetup("MPU6050_IMU");
  MPU6050_setup();
  //-------------------------------------
  //int tickEvent1 = t.every(timeKey, getAngle); //本语句执行以后timeChange毫秒执行回调函数getangle
  //int tickEvent2 = t.every(200, MPU6050_show) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
  //int tickEvent2 = t.every(20, IMU_loop) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
  //-------------------------------------
}
void loop() {
  //t.update();//时间操作系统运行
  IMU_loop();
  delay(20);
}
//===================================================================
