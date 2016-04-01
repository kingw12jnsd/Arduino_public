//===================================================================
#define LENG 32
byte pBuf[LENG];
//攀藤G5的数据格式
typedef struct _G5_type { //0x42;0x4d;
  //------------------------------------------------
  int len;    //[0][1]=2*13+2 帧长度
  //------------------------------------------------
  //标准颗粒物浓度（CF=1）
  int cf10;   //[2][3]=PM1.0=ug/m3
  int cf25;   //[4][5]=PM2.5=ug/m3
  int cf1X;   //[6][7]=PM10 =ug/m3
  //------------------------------------------------
  //大气环境下
  int pm10;   //[8][9]  =PM1.0=ug/m3
  int pm25;   //[10][11]=PM2.5=ug/m3
  int pm1X;   //[12][13]=PM10 =ug/m3
  //------------------------------------------------
  //0.1升空气中xxum直径颗粒物个数
  unsigned int um03;   //[14][15]=0.3um
  int um05;   //[16][17]=0.5um
  int um10;   //[18][19]=1.0um
  int um25;   //[20][21]=2.5um
  int um50;   //[22][23]=5.0um
  int um1X;   //[24][25]=10.0um
  //------------------------------------------------
  int vers;   //[26]版本号
  int errs;   //[27]错误号
  int chek;   //[28][29]校验和
  //------------------------------------------------
} G5_type;
G5_type g;
void G5Feed(byte c) {
  //------------------------------------------------
  static int state = 0;
  static int count = 0;
  //------------------------------------------------
  if (0x42 == c) state = 1;
  if (0x4d == c && state == 1) {
    state = 2;
    count = -1;
  }
  //------------------------------------------------
  pBuf[count++] = c;//lg(c);
  //------------------------------------------------
  if (count == 30) G5Exp();
  //------------------------------------------------
}
unsigned int G5Val(int a, int b) {
  unsigned int v = pBuf[a] << 8;
  if (b > 0) v += pBuf[b];
  return v;
}
void G5Exp() {
  //------------------------------------------------
  g.len = G5Val(0, 1);     //[0][1]=2*13+2 帧长度
  //------------------------------------------------
  //标准颗粒物浓度（CF=1）
  g.cf10 = G5Val(2, 3);    //[2][3]=PM1.0=ug/m3
  g.cf25 = G5Val(4, 5);    //[4][5]=PM2.5=ug/m3
  g.cf1X = G5Val(6, 7);    //[6][7]=PM10 =ug/m3
  //------------------------------------------------
  //大气环境下
  g.pm10 = G5Val(8, 9);     //[8][9]  =PM1.0=ug/m3
  g.pm25 = G5Val(10, 11);   //[10][11]=PM2.5=ug/m3
  g.pm1X = G5Val(12, 13);   //[12][13]=PM10 =ug/m3
  //------------------------------------------------
  //0.1升空气中xxum直径颗粒物个数
  g.um03 = G5Val(14, 15);   //[14][15]=0.3um
  g.um05 = G5Val(16, 17);   //[16][17]=0.5um
  g.um10 = G5Val(18, 19);   //[18][19]=1.0um
  g.um25 = G5Val(20, 21);   //[20][21]=2.5um
  g.um50 = G5Val(22, 23);   //[22][23]=5.0um
  g.um1X = G5Val(24, 25);   //[24][25]=10.0um
  //------------------------------------------------
  g.vers = G5Val(26, -1);   //[26]版本号
  g.errs = G5Val(27, -1);   //[27]错误号
  g.chek = G5Val(28, 29);   //[28][29]校验和
  //------------------------------------------------
  G5_Show();
  //------------------------------------------------
}
void G5_Show() {
  //------------------------------------------------
  lg(); lg(F("-----------------------------")); lg();
  lg(F("American standard")); lg();
  lg(F("pm1.0 = ")); lg(g.cf10); lg(F(" ug/m3")); lg();
  lg(F("pm2.5 = ")); lg(g.cf25); lg(F(" ug/m3")); lg();
  lg(F("pm10. = ")); lg(g.cf1X); lg(F(" ug/m3")); lg();
  //------------------------------------------------
  lg(F("China standard")); lg();
  lg(F("pm1.0 = ")); lg(g.pm10); lg(F(" ug/m3")); lg();
  lg(F("pm2.5 = ")); lg(g.pm25); lg(F(" ug/m3")); lg();
  lg(F("pm10. = ")); lg(g.pm1X); lg(F(" ug/m3")); lg();
  //------------------------------------------------
  lg(F("0.1 litres of air content")); lg();
  lg(F("0.3um = ")); lg(g.um03); lg();
  lg(F("0.5um = ")); lg(g.um05); lg();
  lg(F("1.0um = ")); lg(g.um10); lg();
  lg(F("2.5um = ")); lg(g.um25); lg();
  lg(F("5.0um = ")); lg(g.um50); lg();
  lg(F("10.um = ")); lg(g.um1X); lg();
  //------------------------------------------------
  lg();
  lg(F("vers = ")); lg(g.vers); lg(" ");
  lg(F("errs = ")); lg(g.errs); lg(" ");
  lg(F("chek = ")); lg(g.chek); lg(" ");
  //------------------------------------------------
  int sum = 0;
  for(int i=2;i<30;i++){
    sum +=pBuf[i]%256;
  }
  lg(sum);lg(" ");
  lg(sum%256);lg(" ");
  sum = 0x100-sum%256;
  lg(sum);
  lg();
  //------------------------------------------------
}

