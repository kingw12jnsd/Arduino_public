//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
MPU6050 accelgyro;//陀螺仪类
float angleRawX, gyroRawGy; //计算后的角度（与x轴夹角）和角速度
int16_t ax, ay, az, gx, gy, gz;//陀螺仪原始数据 3个加速度+3个角速度
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化
}
void MPU6050_loop() {
  //accelgyro.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);
}
void MPU6050_show() {
  for (int i = 0; i < 10; i++) {
    //-------------------------------------
    Serial.print(angleRawX); Serial.print(',');
    Serial.println("");
    //Serial.print(gx/131.00);Serial.print(',');
    //Serial.println(Output);
    //-------------------------------------
  }
}
//===================================================================
void getAngle() {
  //--------------------------------------------------------
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
  angleRawX = atan2(ax, az) * 180 / PI; //计算与x轴夹角
  gyroRawGy = -gy / 131.00; //计算角速度
  //--------------------------------------------------------
}
//===================================================================
