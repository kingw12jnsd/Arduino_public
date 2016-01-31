//===================================================================
#include <PID_v1.h>
//===================================================================
int PidCtR, PidCtL;
//---------------------------------------------------------
double rSetpoint, rSpeed, rOutput;
double lSetpoint, lSpeed, lOutput;
//---------------------------------------------------------
//double Kp = 0.9, Ki = 0.12, Kd = 0;//251
//double Kp = 285, Ki = 12, Kd = 0; //285,12,0
double Kp = 383.5, Ki = 24.5, Kd = 0.8; //285,12,0:1.0
//$FF7F7F7F00FF,3835,0245,0008*
//$FF7F7F7F00FF,3834,0232,0008*
//---------------------------------------------------------
PID rPID(&rSpeed, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSpeed, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
//---------------------------------------------------------
void PID_Init() { //PID初始化
  //---------------------------------------------------------
  lg(F("PID_Init()..."));
  //rSetpoint = 0.5;  lSetpoint = 0.4;
  rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  lg(Kp);lg(",");lg(Ki);lg(",");lg(Kd);lg("...");
  lg("ok"); lg();
  //---------------------------------------------------------
}
//===================================================================
void Car_PID_Set(double p, double i, double d) {
  //---------------------------------------------------------
  Kp = p; Ki = i; Kd = d;
  lg(Kp); lg("="); lg(Ki); lg("="); lg(Kd); lg();
  //---------------------------------------------------------
  rPID.SetTunings(Kp, Ki, Kd);
  lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
}
//===================================================================
void Car_Pid_Loop() {
  //---------------------------------------------------------
  int fr = PidCtR >= 0 ? 1 : -1;
  int fl = PidCtL >= 0 ? 1 : -1;
  //---------------------------------------------------------
  rSetpoint = abs(PidCtR) * carSpeedMax / 255;
  lSetpoint = abs(PidCtL) * carSpeedMax / 255;
  //---------------------------------------------------------
  rSpeed = wr.sNow; rPID.Compute(); //wr.runx(rOutput * fr);
  lSpeed = wl.sNow; lPID.Compute(); //wl.runx(lOutput * fl);
  //---------------------------------------------------------
  //Car_SetVt(rOutput * fr, lOutput * fl);
  Car_SetVt( PidCtR, PidCtL);
  //---------------------------------------------------------
}
//===================================================================
void Car_Pid_Test(int N) { //10ms运行一次
  //---------------------------------------------------------
  lg(F("Car_loop()...")); lg();  smartDelay(500);
  //---------------------------------------------------------
  for (int i = 0; i < N; i++) {
    //---------------------------------------------------------
    rPID.SetTunings(Kp, Ki, Kd);
    lPID.SetTunings(Kp, Ki, Kd);
    //---------------------------------------------------------
    rSpeed = wr.sNow; rPID.Compute(); wr.runx(rOutput);
    //---------------------------------------------------------
    Car_Run_Show(); smartDelay(loopMS);
    //---------------------------------------------------------
  }
  //---------------------------------------------------------
  wr.runs(0);
  //---------------------------------------------------------
}
void Car_Run_Show() {
  //---------------------------------------------------------
  for (int i = 0; i < 5; i++) {
    lg(rSetpoint);
    lg(","); lg(rSpeed);
    lg(","); lg(rOutput);
    lg();
  }
  //---------------------------------------------------------
}
//===================================================================
/*
2．PID调试一般原则
a.在输出不振荡时，增大比例增益P。
b.在输出不振荡时，减小积分时间常数Ti。
c.在输出不振荡时，增大微分时间常数Td。
3．一般步骤
a.确定比例增益P
确定比例增益P 时，首先去掉PID的积分项和微分项，一般是令Ti=0、Td=0（具体见PID的参数设定说明），使PID为纯比例调节。
输入设定为系统允许的最大值的60%~70%，由0逐渐加大比例增益P，直至系统出现振荡；再反过来，从此时的比例增益P逐渐减小，直至系统振荡消失，记录此时的比例增益P，
设定PID的比例增益P为当前值的60%~70%。比例增益P调试完成。
b.确定积分时间常数Ti
比例增益P确定后，设定一个较大的积分时间常数Ti的初值，然后逐渐减小Ti，直至系统出现振荡，之后在反过来，逐渐加大Ti，直至系统振荡消失。
记录此时的Ti，设定PID的积分时间常数Ti为当前值的150%~180%。积分时间常数Ti调试完成。
c.确定积分时间常数Td
积分时间常数Td一般不用设定，为0即可。若要设定，与确定 P和Ti的方法相同，取不振荡时的30%。
d.系统空载、带载联调，再对PID参数进行微调，直至满足要求
http://www.geek-workshop.com/thread-704-1-1.html 我的自平衡小车D4——PID控制器——第一次的直立行走
http://www.geek-workshop.com/thread-23-1-1.html
*/