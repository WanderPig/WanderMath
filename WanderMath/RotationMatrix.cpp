//////////////////////////////////////////////////////////////////
//
// name: RotationMatrix.cpp
// func: 旋转矩阵的实现
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.18	
// ps:   默认情况下，矩阵为inertial->object的转换
//
///////////////////////////////////////////////////////////////////

#include "RotationMatrix.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "EulerAngles.h"
#include "CommonMath.h"

// RotationMatrix::Reset
//
// 将矩阵重置

void RotationMatrix::Reset()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

// CRotation::Setup
//
// 用欧拉角建立旋转矩阵

void RotationMatrix::Setup(const EulerAngles &orientation)
{
	// 得到sin值和cos值
    
	float sh, sp, sb;
	float ch, cp, cb;
    
	SinCos(sh, ch, orientation.heading);
	SinCos(sp, cp, orientation.pitch);
	SinCos(sb, cb, orientation.bank);
    
	// 建立矩阵
    
	m11 = ch*cb + sh*sp*sb;
	m12 = -ch*sb + sh*sp*cb;
	m13 = sh * cp;
    
	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;
    
	m31 = -sh*cb + ch*sp*sb;
	m32 = sb*sh + ch*sp*cb;
	m33 = ch * cp;
}

// RotationMatrix::FormObjectToInertialQuaternion
// RotationMatrix::FromInertialToObjectQuaternion
//
// 用旋转四元数转化为旋转矩阵

void RotationMatrix::FromObjectToInertialQuaternion(const Quaternion &q)
{
	// 将数据按照公式填入矩阵
    
	m11 = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);
	m12 = 2.0f * (q.x*q.y + q.w*q.z);
	m13 = 2.0f * (q.x*q.z - q.w*q.y);
    
	m21 = 2.0f * (q.x*q.y - q.w*q.z);
	m22 = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);
	m23 = 2.0f * (q.y*q.z + q.w*q.x);
    
	m31 = 2.0f * (q.x*q.z + q.w*q.y);
	m32 = 2.0f * (q.y*q.z - q.w*q.x);
	m33 = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);
}

void RotationMatrix::FromInertialToObjectQuaternion(const Quaternion &q)
{
	m11 = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);
	m12 = 2.0f * (q.x*q.y - q.w*q.z);
	m13 = 2.0f * (q.x*q.z + q.w*q.y);
    
	m21 = 2.0f * (q.x*q.y + q.w*q.z);
	m22 = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);
	m23 = 2.0f * (q.y*q.z - q.w*q.x);
    
	m31 = 2.0f * (q.x*q.z - q.w*q.y);
	m32 = 2.0f * (q.y*q.z + q.w*q.x);
	m33 = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);
}

// RotationMatrix::InertialToObject
//
// 旋转一个向量从惯性坐标系到物体坐标系（旋转空间）

Vector3D RotationMatrix::InertialToObject(const Vector3D &v)
{
	return Vector3D(m11*v.x + m21*v.y + m31*v.z,
					m12*v.x + m22*v.y + m32*v.z,
					m13*v.x + m23*v.y + m33*v.z);
}

// RotationMatrix::ObjectToInertial
//
// 旋转一个向量从物体坐标系到惯性坐标系（旋转物体）
// 假设矩阵是正交的，与上边的不同时将矩阵转置

Vector3D RotationMatrix::ObjectToInertial(const Vector3D &v)
{
	return Vector3D(m11*v.x + m12*v.y + m12*v.z,
					m21*v.x + m22*v.y + m23*v.z,
					m31*v.x + m32*v.y + m33*v.z);
}
