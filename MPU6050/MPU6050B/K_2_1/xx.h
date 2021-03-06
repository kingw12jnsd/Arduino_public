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
