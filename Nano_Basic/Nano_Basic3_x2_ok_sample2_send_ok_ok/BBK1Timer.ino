//===================================================================
#include "Timer.h"//时间操作系统头文件
Timer timerLoop;//时间类
//===================================================================
void Timer_setup() {
  Timer_work();//设置时间运行
}
void Timer_loop() {
  timerLoop.update();//时间操作系统运行
}
//===================================================================
