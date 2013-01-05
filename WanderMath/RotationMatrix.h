//////////////////////////////////////////////////////////////////
//
// name: RotationMatrix.h
// func: 旋转矩阵的定义
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.18	
// ps:   默认情况下，矩阵为inertial->object的转换
//
///////////////////////////////////////////////////////////////////

#pragma once

class Vector3D;
class Quaternion;
class EulerAngles;


class RotationMatrix
{
public:
    
	// 将成员值为重置
    
	void Reset();
    
	// 用一个定向建立矩阵
    
	void Setup(const EulerAngles &orientation);
    
	// 用一个表示定向的四元数建立矩阵
    
	void FromInertialToObjectQuaternion(const Quaternion &q);
	void FromObjectToInertialQuaternion(const Quaternion &q);
    
	// 进行旋转
    
	Vector3D InertialToObject(const Vector3D &v);
	Vector3D ObjectToInertial(const Vector3D &v);
    
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	
};
