//////////////////////////////////////////////////////////////////
//
// name: Quaternion.h
// func: 利用四元数表示角位移
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.17	
//
///////////////////////////////////////////////////////////////////

#pragma once

class Vector3D;
class EulerAngles;


class Quaternion
{
public:
    
	// 将成员置为零
    
	void Zero();
    
	// 绕x, y, z 以及任意轴旋转函数
    
	void SetRotateX(float theta);
	void SetRotateY(float theta);
	void SetRotateZ(float theta);
	void SetRotateAxis(const Vector3D &axis, float theta);
    
	// 很据已知欧拉角建立惯性坐标系和物体坐标系相互转化的四元数
    
	void SetRotateObjectToInertial(const EulerAngles &orientation);
	void SetRotateInertialToObject(const EulerAngles &orientation);
    
	// 叉乘重载*号
    
	Quaternion operator *(const Quaternion &q) const;
	Quaternion operator *=(const Quaternion &q);
    
	// 置模为1
    
	void Normalize();
    
	// 返回旋转角和旋转轴
    
	float GetRatateAngle() const;
	Vector3D GetRAtateAxis() const;
    
public:
	float w;
	float x;
	float y;
	float z;
};

// 全局声明

extern const Quaternion gQuaternionIdentity;

// 点积

extern float DotProduct(const Quaternion &a, const Quaternion &b);

// 线性插值

extern Quaternion Slerp(const Quaternion &q0, const Quaternion &q1, float t);

// 取共轭数 表示相反的旋转

extern Quaternion Conjugate(const Quaternion &q);

// 四元数指数运算

extern Quaternion Pow(const Quaternion &q, float exp);