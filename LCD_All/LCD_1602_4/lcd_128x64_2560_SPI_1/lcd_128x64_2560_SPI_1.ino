/*
  LCD  Arduino
  PIN1 = GND
  PIN2 = 5V
  RS(CS) = 8;
  RW(SID)= 9;
  EN(CLK) = 3;
  PIN15 PSB = GND;
*/

#include "LCD12864RSPI.h"
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

unsigned char bbk_wwws[] = "www.commsat.com";
unsigned char bbk_jtwx[] = {0xBE, 0xC5, 0xCC, 0xEC, 0xCE, 0xA2, 0xD0, 0xC7}; //九天微星
unsigned char bbk_wj[] = {0xCE, 0xB3, 0xBE, 0xAD, 0xA3, 0xBA}; //纬经
unsigned char bbk_zt[] = {0xD7, 0xCB, 0xCC, 0xAC, 0xA3, 0xBA}; //姿态
unsigned char bbk_ws[] = {0xCE, 0xC2, 0xCA, 0xAA, 0xA3, 0xBA}; //温湿
unsigned char logo0[] = {//笑脸
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF,
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFE, 0x00,
  0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x00,
  0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00,
  0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,
  0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xF0, 0x00, 0x00,
  0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00,
  0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00,
  0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x40, 0x00,
  0x00, 0x80, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x78, 0x03, 0xF8, 0x00,
  0x07, 0xF0, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x07, 0xFE, 0x00,
  0x0F, 0xFC, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0xBF, 0x00,
  0x3F, 0x7E, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x3E, 0x0F, 0x80,
  0x7C, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x7C, 0x07, 0xC0,
  0xF8, 0x0F, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x01, 0xE1,
  0xF0, 0x03, 0xC3, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0xF0, 0x01, 0xE1,
  0xE0, 0x03, 0xC3, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0xE0, 0x00, 0xE1,
  0xC0, 0x01, 0xC3, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0C, 0x00,
  0x0C, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x1E, 0x00,
  0x1E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x1F, 0x00,
  0x3E, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x07, 0x80,
  0xF8, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x03, 0xE1,
  0xF0, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x01, 0xFF,
  0xE0, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xFF,
  0x80, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x3F,
  0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
  0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00,
  0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xF0, 0x00, 0x00,
  0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,
  0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00,
  0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x00,
  0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00,
  0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFE, 0x00,
  0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF,
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  LCDA.Initialise(38,40,42); // 屏幕初始化
  delay(100);
}

void loop() {
  LCDA.CLEAR();//清屏
  unsigned char wjs[] = " 3997,11632";
  unsigned char zts[] = " 128 111 100";
  unsigned char wsd[] = " 39.5C H16%";
  delay(100);  LCDA.DisplayString(0, 2, bbk_jtwx, AR_SIZE(bbk_jtwx)); //第一行第三格开始
  //delay(100);LCDA.DisplayString(1, 0, bbk_wwws, AR_SIZE(bbk_wwws)); //第二行第一格开始
  delay(100);  LCDA.DisplayString(1, 0, bbk_wj, AR_SIZE(bbk_wj)); LCDA.DisplayString(1, 2, wjs, AR_SIZE(wjs));
  delay(100);  LCDA.DisplayString(2, 0, bbk_zt, AR_SIZE(bbk_zt)); LCDA.DisplayString(2, 2, zts, AR_SIZE(zts));
  delay(100);  LCDA.DisplayString(3, 0, bbk_ws, AR_SIZE(bbk_ws)); LCDA.DisplayString(3, 2, wsd, AR_SIZE(wsd));


  delay(5000); LCDA.CLEAR();//清屏
  delay(100);  LCDA.DrawFullScreen(logo0);
  delay(5000);
}
