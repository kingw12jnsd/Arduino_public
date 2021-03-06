//======================================
typedef struct CEulerAngle {
  float x;//Pitch
  float y;//Yaw
  float z;//Roll
} CEulerAngle;
typedef struct CQuaternion {
  float w;
  float x;
  float y;
  float z;
} CQuaternion;
//======================================
typedef struct Vertex {
  int  location[3];
} MyVertex;
typedef struct Edge {
  int  connection[2];
} MyEdge;
typedef struct Object {
  int numv;
  int nume;
  MyVertex* v;//顶点
  MyEdge* e;//边缘（顶点连接线）
  CQuaternion quat;//Quaternions四元数姿态
  float offset[3];//位置(偏移)
} MyObject;
//======================================
typedef struct IMU_tt{
  //----------------------------------------------------------
  bool caliPass;
  bool readys;         //是否校准
  //----------------------------------------------------------
  int accADC[3];      //加速度-int16_t
  int gyroADC[3];     //重力
  int magADC[3];      //磁力
  //----------------------------------------------------------
  float   accRaw[3];      //原始加速度m/s^2
  float   gyroRaw[3];     //原始重力rad/s
  float   magRaw[3];      //原始磁力
  //----------------------------------------------------------
  float   accOffset[3];   //上次的加速度m/s^2
  float   gyroOffset[3];  //上次的重力
  //----------------------------------------------------------
  float   accb[3];        //滤波后值,filted, in body frame
  float   accg[3];        //滤波后值
  float   gyro[3];        //滤波后值
  //----------------------------------------------------------
  float   DCMgb[3][3];
  //----------------------------------------------------------
  float   q[4];           //四元素
  float   roll;           //横滚deg
  float   pitch;          //俯仰
  float   yaw;            //航向
  float   rollRad;        //横滚rad
  float   pitchRad;       //俯仰
  float   yawRad;         //航向
  //----------------------------------------------------------
} imu_t;
//======================================
//enum{ROLL,PITCH,YAW};
#define M_PI_F 3.1415926
#define CONSTANTS_ONE_G         9.80665f    /* m/s^2    */
#define CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C   1.225f      /* kg/m^3   */
#define CONSTANTS_AIR_GAS_CONST       287.1f      /* J/(kg * K)   */
#define CONSTANTS_ABSOLUTE_NULL_CELSIUS     -273.15f    /* 癈      */
#define CONSTANTS_RADIUS_OF_EARTH     6371000     /* meters (m)   */
//======================================
#define IMU_SAMPLE_RATE         200.0f
#define IMU_FILTER_CUTOFF_FREQ  30.0f
//#undef  USE_SW_IMU
//校准时间
#define ACC_CALC_TIME  3000//ms
#define GYRO_CALC_TIME   3000000l //us
//======================================
