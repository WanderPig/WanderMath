//////////////////////////////////////////////////////////////////
//
// name:	EulerAngles.cpp
// func:	欧拉角类
// disc:	来源于3D Math Primer for Graphics and Game Development
//
///////////////////////////////////////////////////////////////////

#include "EulerAngles.h"
#include "CommonMath.h"
#include "Quaternion.h"
#include "Matrix4X3.h"
#include "RotationMatrix.h"

EulerAngles::EulerAngles()
{
	heading = pitch = bank = 0.0f;
}
// EulerAngles::canonize
//	
// 用于标准化一组欧拉角，结果为将 pitch 控制在 -PI/2 到 PI/2 之间
// 并检查万向节锁，调整后将 bank 和 heading 控制在 -PI 到 PI 之间

void EulerAngles::Canonize()
{
	// 将pitch转化到 -PI 到 PI
    
	pitch = WrapPI(pitch);
    
	// 将pitch转化到 -PI/ 2到 PI/2
    
	if (pitch < -KPIOVER2)
	{
		pitch = -KPI - pitch;
		heading += KPI;
		bank += KPI;
	}
	else if(pitch > KPIOVER2)
	{
		pitch = KPI - pitch;
		heading += KPI;
		bank += KPI;
	}
    
	// 检查万向节锁
    
	if (fabs(pitch) > KPIOVER2 - FZERO)
	{
		// 万向节锁生效
        
        heading += bank;
        bank = 0;
	}
	else
	{
		bank = WrapPI(bank);
	}
    
	heading = WrapPI(heading);
    
}

// EulerAngles::FromObjectToInertialQuaternion
//
// 用一个由物体坐标系向惯性坐标系转化的四元数初始化欧拉角

void EulerAngles::FromObjectToInertialQuaternion(const Quaternion &q)
{
	// p的sin值
    
	float sp = -2.0f * (q.y*q.z - q.w*q.x);
    
	if (fabs(sp) >= 0.9999f)
	{
		// p为2/π，bank值为零，值计算pitch
        
		pitch = KPIOVER2 * sp;
		heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		// 此时已经排除万向节锁，正常赋值、
        
		pitch = asin(sp);
		heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

// EulerAngles::FromObjectToInertialQuaternion
//
// 用一个由惯性坐标系向物体坐标系转化的四元数初始化欧拉角

void EulerAngles::FromInertialToObjectQuaternion(const Quaternion &q)
{
	float sp = -2.0f * (q.y*q.z + q.w*q.x);
    
	if (fabs(sp) >= 0.9999f)
	{
		pitch = KPIOVER2 * sp;
		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sp);
		heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

// EulerAngles::FromObjectToWorldMatrix
//
// 用一个由物体坐标系向世界坐标系转化的4X3矩阵初始化欧拉角

void EulerAngles::FromObjectToWorldMatrix(const Matrix4X3 &m)
{
	float sp = -m.m32;
    
	if(fabs(sp) >= 0.9999f)
	{
		pitch = KPIOVER2 * sp;
		heading = atan2(-m.m23, m.m11);
		bank = 0.0f;
	}
	else
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}
}

// EulerAngles::FromWorldToObjectMatrix
//
// 用一个由世界坐标系向物体坐标系转化的4X3矩阵初始化欧拉角

void EulerAngles::FromWorldToObjectMatrix(const Matrix4X3 &m)
{
	float sp = -m.m23;
    
	if (fabs(sp) >= 0.9999f)
	{
		pitch = KPIOVER2 * sp;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

// EulerAngles::FormRotationMatrix
// 
// 用一个旋转矩阵初始化欧拉角
void EulerAngles::FormRotationMatrix(const RotationMatrix &m)
{
	float sp = -m.m23;
    
	if (fabs(sp) >= 0.9999f)
	{
		pitch = KPIOVER2 * sp;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}