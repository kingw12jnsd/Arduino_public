//======================================
typedef struct IMU_tt {
  //----------------------------------------------------------
  bool    readys;         //是否校准
  //----------------------------------------------------------
  //测量值
  int     accADC[3];      //加速度-int16_t
  int     gyroADC[3];     //重力
  int     magADC[3];      //磁力
  //----------------------------------------------------------
  //物理值
  float   accRaw[3];      //原始加速度m/s^2
  float   gyroRaw[3];     //原始重力rad/s
  float   magRaw[3];      //原始磁力
  //----------------------------------------------------------
  float   accb[3];        //滤波后值
  float   gyro[3];        //
  float   magb[3];        //
  //----------------------------------------------------------
  //平均校准值
  float   accOffset[3];   //加速度m/s^2
  float   gyroOffset[3];  //重力
  //----------------------------------------------------------
  float   accbReal[3];    //校准后值
  float   gyroReal[3];    //
  float   magbReal[3];    //
  //----------------------------------------------------------
  float   q[4];           //四元素
  //----------------------------------------------------------
  float   roll;           //横滚deg
  float   pitch;          //俯仰
  float   yaw;            //航向
  float   rollRad;        //横滚rad
  float   pitchRad;       //俯仰
  float   yawRad;         //航向
  //----------------------------------------------------------
} imu_t;
//============================================================================
