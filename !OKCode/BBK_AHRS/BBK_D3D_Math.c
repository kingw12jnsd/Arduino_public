 // 由旋转矩阵创建四元数
  inline CQuaternion(const _Matrix4& m)
  {
   float tr, s, q[4];
   int i, j, k;
   
   int nxt[3] = {1, 2, 0 };
   // 计算矩阵轨迹
   tr = m._11 + m._22 + m._33;
   
   // 检查矩阵轨迹是正还是负
   if(tr>0.0f)
   {
    s = sqrt(tr + 1.0f);
    this->w = s / 2.0f;
    s = 0.5f / s;
    this->x = (m._23 - m._32) * s;
    this->y = (m._31 - m._13) * s;
    this->z = (m._12 - m._21) * s;
   }
   else
   {
    // 轨迹是负
    // 寻找m11 m22 m33中的最大分量
    i = 0;
    if(m.m[1][1]>m.m[0][0]) i = 1;
    if(m.m[2][2]>m.m[i][i]) i = 2;
    j = nxt[i];
    k = nxt[j];
    
    s = sqrt((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + 1.0f);
    q[i] = s * 0.5f;
    if( s!= 0.0f) s = 0.5f / s;
    q[3] = (m.m[j][k] - m.m[k][j]) * s;
    q[j] = (m.m[i][j] - m.m[j][i]) * s;
    q[k] = (m.m[i][k] - m.m[k][i]) * s;
    this->x = q[0];
    this->y = q[1];
    this->z = q[2];
    this->w = q[3];
   }
  };

  // 由欧拉角创建四元数
  inline CQuaternion(const _Vector3& angle)
  {
   float cx = cos(angle.x/2);
   float sx = sin(angle.x/2);
   float cy = cos(angle.y/2);
   float sy = sin(angle.y/2);
   float cz = cos(angle.z/2);
   float sz = sin(angle.z/2);

   this->w = cx*cy*cz + sx*sy*sz;
   this->x = sx*cy*cz - cx*sy*sz;
   this->y = cx*sy*cz + sx*cy*sz;
   this->z = cx*cy*sz - sx*sy*cz;
  };

  // 给定角度和轴创建四元数
  inline CQuaternion(_Vector3 anxi, const float& angle)
  {
   CVector3 t;
   t.x = anxi.x;
   t.y = anxi.y;
   t.z = anxi.z;
   t.Normalize();
   float cosa = cos(angle);
   float sina = sin(angle);
   this->w = cosa;
   this->x = sina * t.x;
   this->y = sina * t.y;
   this->z = sina * t.z;
  };

// 由旋转四元数推导出矩阵
  inline CMatrix4 GetMatrixLH()
  {
   CMatrix4 ret;
   float xx = x*x;
   float yy = y*y;
   float zz = z*z;
   float xy = x*y;
   float wz = w*z;
   float wy = w*y;
   float xz = x*z;
   float yz = y*z;
   float wx = w*x;

   ret._11 = 1.0f-2*(yy+zz);
   ret._12 = 2*(xy-wz);
   ret._13 = 2*(wy+xz);
   ret._14 = 0.0f;

   ret._21 = 2*(xy+wz);
   ret._22 = 1.0f-2*(xx+zz);
   ret._23 = 2*(yz-wx);
   ret._24 = 0.0f;

   ret._31 = 2*(xy-wy);
   ret._32 = 2*(yz+wx);
   ret._33 = 1.0f-2*(xx+yy);
   ret._34 = 0.0f;

   ret._41 = 0.0f;
   ret._42 = 0.0f;
   ret._43 = 0.0f;
   ret._44 = 1.0f;

   return ret;
  };
  inline CMatrix4 GetMatrixRH()
  {
   CMatrix4 ret;
   float xx = x*x;
   float yy = y*y;
   float zz = z*z;
   float xy = x*y;
   float wz = -w*z;
   float wy = -w*y;
   float xz = x*z;
   float yz = y*z;
   float wx = -w*x;

   ret._11 = 1.0f-2*(yy+zz);
   ret._12 = 2*(xy-wz);
   ret._13 = 2*(wy+xz);
   ret._14 = 0.0f;

   ret._21 = 2*(xy+wz);
   ret._22 = 1.0f-2*(xx+zz);
   ret._23 = 2*(yz-wx);
   ret._24 = 0.0f;

   ret._31 = 2*(xy-wy);
   ret._32 = 2*(yz+wx);
   ret._33 = 1.0f-2*(xx+yy);
   ret._34 = 0.0f;

   ret._41 = 0.0f;
   ret._42 = 0.0f;
   ret._43 = 0.0f;
   ret._44 = 1.0f;

   return ret;
  };

  // 由四元数返回欧拉角
  inline CVector3 GetEulerAngle()
  {
   CVector3 ret;

   float test = y*z + x*w;
   if (test > 0.4999f)
   { 
    ret.z = 2.0f * atan2(y, w);
    ret.y = PIOver2;
    ret.x = 0.0f;
    return ret;
   }
   if (test < -0.4999f)
   { 
    ret.z = 2.0f * atan2(y, w);
    ret.y = -PIOver2;
    ret.x = 0.0f;
    return ret;
   }
   float sqx = x * x;
   float sqy = y * y;
   float sqz = z * z;
   ret.z = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
   ret.y = asin(2.0f * test);
   ret.x = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);
      
   return ret;
  };