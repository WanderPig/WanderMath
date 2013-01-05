//////////////////////////////////////////////////////////////////
//
// name: Matrix4X3.h
// func: 4X3矩阵的定义
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.19	
//
///////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>

#include "Matrix4X3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "CommonMath.h"

using namespace std;

//////////////////////////////////////////////////////////////////
//
// 成员函数
//
///////////////////////////////////////////////////////////////////

Matrix4X3::Matrix4X3()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    
	tx = 0.0f; ty = 0.0f; tz = 0.0f;
}
// Matrix4X3::Reset
//
// 将矩阵重置

void Matrix4X3::Reset()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    
	tx = 0.0f; ty = 0.0f; tz = 0.0f;
}

// Matrix4X3::ZeroTranslation
//
// 将变换部分重置

void Matrix4X3::ZeroTranslation()
{
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetTranslation
//
// 用一个Vector改变变换部分

void Matrix4X3::SetTranslation(const Vector3D &v)
{
	tx = v.x; ty = v.y; tz = v.z;
}

// Matrix4X3::SetupTranslation
//
// 用一个Vector初始化一个变换

void Matrix4X3::SetupTranslation(const Vector3D &v)
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    
	tx = v.x; ty = v.y; tz = v.z;
}

void Matrix4X3::SetRotate(float _m11, float _m12, float _m13,
						  float _m21, float _m22, float _m23,
						  float _m31, float _m32, float _m33)
{
	m11 = _m11; m12 = _m12; m13 = _m13;
	m21 = _m21; m22 = _m22; m23 = _m23;
	m31 = _m31; m32 = _m32; m33 = _m33;
}
//-----------------------------------------------------------------------------------/

void Matrix4X3::SetupLocalToParent(const Point3D &pos, const EulerAngles &angles)
{
	// 从本地坐标转换到父坐标
	// 先对物体自身进行旋转，再平移到物体在世界的坐标位置
	// 平移部分就是物体的坐标
    
	// 得到sin值和cos值
    
	float sh, sp, sb;
	float ch, cp, cb;
    
	SinCos(sh, ch, angles.heading);
	SinCos(sp, cp, angles.pitch);
	SinCos(sb, cb, angles.bank);
    
	// 建立矩阵，object->intertial
    
	m11 = ch*cb + sh*sp*sb;
	m12 = sb * cp;
	m13 = -sh*cb + ch*sp*sb;
    
	m21 = -ch*sb + sh*sp*cb;
	m22 = cb * cp;
	m23 = sb*sh + ch*sp*cb;
    
	m31 = sh * cp;
	m32 = -sp;
	m33 = ch * cp;
    
	tx = pos.x;
	ty = pos.y;
	tz = pos.z;
}

//------------------------------------------------------------------------------------/

void Matrix4X3::SetupParentToLocal(const Point3D &pos, const EulerAngles &angles)
{
	// 从父坐标转换到本地坐标
	// 先对物体进行平移到物体原点（即世界坐标的反向），再进行逆向的旋转
	// 由于平移在先，平移部分需要与旋转部分相乘
    
	// 得到sin值和cos值
    
	float sh, sp, sb;
	float ch, cp, cb;
    
	SinCos(sh, ch, angles.heading);
	SinCos(sp, cp, angles.pitch);
	SinCos(sb, cb, angles.bank);
    
	// 建立矩阵，intertial->object
    
	m11 = ch*cb + sh*sp*sb;
	m12 = -ch*sb + sh*sp*cb;
	m13 = sh * cp;
    
	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;
    
	m31 = -sh*cb + ch*sp*sb;
	m32 = sb*sh + ch*sp*cb;
	m33 = ch * cp;
    
	tx = -(pos.x*m11 + pos.y*m21 + pos.z*m31);
	ty = -(pos.x*m12 + pos.y*m22 + pos.z*m32);
	tz = -(pos.x*m13 + pos.y*m23 + pos.z*m33);
}

//--------------------------------------------------------------/

void Matrix4X3::SetupRotate(const EulerAngles &angles)
{
	// 用欧拉角构造旋转部分
    
	float sh, sp, sb;
	float ch, cp, cb;
    
	SinCos(sh, ch, angles.heading);
	SinCos(sp, cp, angles.pitch);
	SinCos(sb, cb, angles.bank);
    
	// 建立矩阵
    
	m11 = ch*cb + sh*sp*sb;
	m12 = sb * cp;
	m13 = -sh*cb + ch*sp*sb;
    
	m21 = -ch*sb + sh*sp*cb;
	m22 = cb * cp;
	m23 = sb*sh + ch*sp*cb;
    
	m31 = sh * cp;
	m32 = -sp;
	m33 = ch * cp;
}

//----------------------------------------------------------------/

void Matrix4X3::SetupRotate(int axis, float theta)
{
	// 建立对坐标轴旋转的矩阵
	// axis参数对应：1->x轴 2->y轴 3->z轴
	// theat参数表示旋转角度，用左手法则判断正方向
    
	float s,c;
	SinCos(s,c,theta);
    
	switch(axis)
	{
        case 1:	// 绕x轴旋转
            
            m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m21 = 0.0f; m22 = c;	m23 = s;
            m31 = 0.0f; m32 =-s;	m33 = c;
            break;
            
        case 2: // 绕y轴旋转
            
            m11 = c;	m12 = 0.0f;	m13 = -s;
            m21 = 0.0f;	m22 = 1.0f;	m23 = 0.0f;
            m31 = s;	m32 = 0.0f;	m33 = c;
            break;
            
        case 3: // 绕z轴旋转
            
            m11 = c;	m12 = s;	m13 = 0.0f;
            m21 = -s;	m22 = c;	m23 = 0.0f;
            m31 = 0.0f;	m32 = 0.0f;	m33 = 1.0f;
            break;
            
        default:
            
            assert(false);
            break;
	}
    
	// 重置平移
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupRotate
//
// 建立对任意轴旋转
// 旋转轴为单位向量
// 平移部分置为零

void Matrix4X3::SetupRotate(const Vector3D &axis, float theta)
{
	// 检查旋转轴是否为单位向量
    
	assert(fabs(axis*axis - 1.0f) < 0.01f);
    
	float s,c;
    
	SinCos(s, c, theta);
    
	// 计算一些需要的常量
	
	float a = 1.0f - c;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;
    
	// 建立矩阵
    
	m11 = ax*axis.x + c;
	m12 = ax*axis.y + axis.z*s;
	m13 = ax*axis.z - axis.y*s;
    
	m21 = ay*axis.x - axis.z*s;
	m22 = ay*axis.y + c;
	m23 = ay*axis.z + axis.x*s;
    
	m31 = ax*axis.x + axis.y*s;
	m32 = ax*axis.y - axis.x*s;
	m33 = ax*axis.z + c;
    
	tx = ty = tz = 0;
    
}

// Matrix4X3::FromQuaternion
//
// 用四元数建立矩阵

void Matrix4X3::FromQuaternion(const Quaternion &q)
{
	// 预先计算好2倍的变量
    
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;
	float ww = 2.0f * q.w;
    
	// 填入矩阵
    
	m11 = 1.0f - yy*q.y - zz*q.z;
	m12 = xx*q.y + ww*q.z;
	m13 = xx*q.z - ww*q.x;
    
	m21 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m23 = yy*q.z + ww*q.x;
    
	m31 = xx*q.z + ww*q.y;
	m32 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupScale
//
// 用一个Vector3D(k,k,k)的向量来放大缩小

void Matrix4X3::SetupScale(const Vector3D &s)
{
	m11 = s.x;  m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = s.y;  m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = s.z;
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupScaleAlongAxis
//
// 沿着一个轴进行缩放
// axis为单位向量

void Matrix4X3::SetupScaleAlongAxis(const Vector3D &axis, float t)
{
	// 检查axis是否为单位向量
    
	assert(fabs(axis*axis - 1.0f) < 0.01f);
    
	// 初始化一些常用变量
    
	float a = t - 1.0f;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;
    
	// 建立矩阵
    
	m11 = ax*axis.x + 1.0f;
	m22 = ay*axis.y + 1.0f;
	m33 = az*axis.z + 1.0f;
    
	m12 = m21 = ax * axis.y;
	m13 = m31 = ax * axis.z;
	m23 = m32 = ay * axis.z;
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupShear
//
// 建立切变矩阵
// 切变是把坐标系扭转的变换
// axis = 1 代表 对y,z进行变换
// axis = 2 代表 对x,z进行变换
// axis = 3 代表 对x,y进行变换

void Matrix4X3::SetupShear(int axis, float s, float t)
{
	switch(axis)
	{
        case 1:
            
            m11 = 1.0f; m12 = s;	m13 = t;
            m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
            m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
            break;
            
        case 2:
            
            m11 = 1.0f; m12 = 0.0f;	m13 = 0.0f;
            m21 = s;	m22 = 1.0f; m23 = t;
            m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
            break;
            
        case 3:
            
            m11 = 1.0f; m12 = 0.0f;	m13 = 0.0f;
            m21 = 0.0f;	m22 = 1.0f; m23 = 0.0f;
            m31 = s;	m32 = t;	m33 = 1.0f;
            break;
            
        default:
            
            assert(false);
            
            break;
            
	}
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupProject 
//
// 建立向一个过原点的任意平面投影矩阵

void Matrix4X3::SetupProject(const Vector3D &n)
{
	assert(fabs(n*n - 1.0f) < 0.01f);
    
	m11 = 1.0f - n.x*n.x;
	m22 = 1.0f - n.y*n.y;
	m33 = 1.0f - n.z*n.z;
    
	m12 = m21 = -n.x*n.y;
	m13 = m31 = -n.x*n.z;
	m23 = m32 = -n.y*n.z;
    
	tx = ty = tz = 0.0f;
}

// Matrix4X3::SetupReflect
//
// 建立镜像矩阵
// axis = 1 代表 对x = k平面镜像
// axis = 2 代表 对y = k平面镜像
// axis = 3 代表 对z = k平面镜像

void Matrix4X3::SetupReflect(int axis, float a)
{
	switch(axis)
	{
        case 1:
            
            m11 = - 1.0f; m12 = 0.0f; m13 = 0.0f;
            m21 = 0.0f;	  m22 = 1.0f; m23 = 0.0f;
            m31 = 0.0f;	  m32 = 0.0f; m33 = 1.0f;
            
            tx = 2.0f * a;
            ty = 0.0f;
            tz = 0.0f;
            
            break;
            
        case 2:
            
            m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f;
            m21 = 0.0f;	m22 = -1.0f; m23 = 0.0f;
            m31 = 0.0f; m32 = 0.0f;  m33 = 1.0f;
            
            tx = 0.0f;
            ty = 2.0f * a;
            tz = 0.0f;
            
            break;
            
        case 3:
            
            m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m21 = 0.0f;	m22 = 0.0f; m23 = 0.0f;
            m31 = 0.0f;	m32 = 0.0f; m33 = -1.0f;
            
            tx = 0.0f;
            ty = 0.0f;
            tz = 2.0f * a;
            
            break;
            
        default:
            
            assert(false);
            
            break;
	}
}

// Matrix4X3::SetupReflect
//
// 对任意经过原点且垂直于n的平面进行镜像

void Matrix4X3::SetupReflect(const Vector3D &n)
{
	assert(fabs(n*n - 1.0f) <0.01f);
    
	float ax = -2.0f * n.x;
	float ay = -2.0f * n.y;
	float az = -2.0f * n.z;
    
	m11 = 1.0f + ax*n.x;
	m22 = 1.0f + ay*n.y;
	m33 = 1.0f + az*n.z;
    
	m12 = m21 = ax * n.y;
	m13 = m31 = ax * n.z;
	m23 = m32 = ay * n.z;
    
	tx = ty = tz = 0.0f;
}
/////////////////////////////////////////////////
//
// 非成员函数
//
/////////////////////////////////////////////////

Matrix4X3 operator *(const Matrix4X3 &m, float v)
{
	Matrix4X3 tm;
    
	tm.m11 = m.m11*v;
	tm.m12 = m.m12*v;
	tm.m13 = m.m13*v;
    
	tm.m21 = m.m21*v;
	tm.m22 = m.m22*v;
	tm.m23 = m.m23*v;
    
	tm.m31 = m.m31*v;
	tm.m32 = m.m32*v;
	tm.m33 = m.m33*v;
    
	tm.tx = m.tx*v;
	tm.ty = m.ty*v;
	tm.tz = m.tz*v;
    
	return tm;
	
}

Matrix4X3 operator +(const Matrix4X3 &m1, Matrix4X3 m2)
{
	Matrix4X3 tm;
    
	tm.m11 = m1.m11 + m2.m11;
	tm.m12 = m1.m12 + m2.m12;
	tm.m13 = m1.m13 + m2.m13;
    
	tm.m21 = m1.m21 + m2.m21;
	tm.m22 = m1.m22 + m2.m22;
	tm.m23 = m1.m23 + m2.m23;
    
	tm.m31 = m1.m31 + m2.m31;
	tm.m32 = m1.m32 + m2.m32;
	tm.m33 = m1.m33 + m2.m33;
    
	tm.tx = m1.tx + m2.tx;
	tm.ty = m1.ty + m2.ty;
	tm.tz = m1.tz + m2.tz;
    
	return tm;
}

Matrix4X3 operator -(const Matrix4X3 &m1, Matrix4X3 m2)
{
	Matrix4X3 tm;
    
	tm.m11 = m1.m11 - m2.m11;
	tm.m12 = m1.m12 - m2.m12;
	tm.m13 = m1.m13 - m2.m13;
    
	tm.m21 = m1.m21 - m2.m21;
	tm.m22 = m1.m22 - m2.m22;
	tm.m23 = m1.m23 - m2.m23;
    
	tm.m31 = m1.m31 - m2.m31;
	tm.m32 = m1.m32 - m2.m32;
	tm.m33 = m1.m33 - m2.m33;
    
	tm.tx = m1.tx - m2.tx;
	tm.ty = m1.ty - m2.ty;
	tm.tz = m1.tz - m2.tz;
    
	return tm;
}


Vector3D operator *(const Vector3D &p, const Matrix4X3 &m)
{
	return Vector3D(p.x*m.m11 + p.y*m.m21 + p.z*m.m31 + m.tx,
					p.x*m.m12 + p.y*m.m22 + p.z*m.m32 + m.ty,
					p.x*m.m13 + p.y*m.m23 + p.z*m.m33 + m.tz);
}

Vector3D &operator *=(Vector3D &p, const Matrix4X3 &m)
{
	p = p * m;
	return p;
}

Matrix4X3 operator *(const Matrix4X3 &a, const Matrix4X3 &b)
{
	Matrix4X3 tm;
	
	tm.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
	tm.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	tm.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
    
	tm.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	tm.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	tm.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
    
	tm.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
	tm.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
	tm.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;
    
	tm.tx = a.tx*b.m11 + a.ty*b.m21 + a.tz*b.m31 + b.tx;
	tm.ty = a.tx*b.m12 + a.ty*b.m22 + a.tz*b.m32 + b.ty;
	tm.tz = a.tx*b.m13 + a.ty*b.m23 + a.tz*b.m33 + b.tz;
    
	return tm;
}

Matrix4X3 &operator *=(Matrix4X3 &a, const Matrix4X3 &b)
{
	a = a * b;
    
	return a;
}

float Determinant(const Matrix4X3 &m)
{
	return (m.m11 * (m.m22*m.m33 - m.m23*m.m32) +
			m.m12 * (m.m23*m.m31 - m.m21*m.m33) +
			m.m13 * (m.m21*m.m32 - m.m22*m.m31));
}

Matrix4X3 Inverse(const Matrix4X3 &m)
{
	float det = Determinant(m);
    
	// 如果是零矩阵，则矩阵没有逆
    
	assert(fabs(det) > 0.000001f);
    
	float oneOverDet = 1.0f / det;
    
	Matrix4X3 tm;
    
	tm.m11 = (m.m22*m.m33 - m.m23*m.m32) * oneOverDet;
	tm.m12 = (m.m13*m.m32 - m.m12*m.m33) * oneOverDet;
	tm.m13 = (m.m12*m.m23 - m.m13*m.m22) * oneOverDet;
    
	tm.m21 = (m.m23*m.m31 - m.m21*m.m33) * oneOverDet;
	tm.m22 = (m.m11*m.m33 - m.m13*m.m31) * oneOverDet;
	tm.m23 = (m.m13*m.m21 - m.m11*m.m23) * oneOverDet;
    
	tm.m31 = (m.m21*m.m32 - m.m22*m.m31) * oneOverDet;
	tm.m32 = (m.m12*m.m31 - m.m11*m.m32) * oneOverDet;
	tm.m33 = (m.m11*m.m22 - m.m12*m.m21) * oneOverDet;
    
	// 计算平移的逆
    
	tm.tx = -(m.tx*tm.m11 + m.ty*tm.m21 + m.tz*tm.m31);
	tm.ty = -(m.tx*tm.m12 + m.ty*tm.m22 + m.tz*tm.m32);
	tm.tz = -(m.tx*tm.m13 + m.ty*tm.m23 + m.tz*tm.m33);
    
	return tm;
}

// GetTranslation
//
// 得到矩阵的平移部分

Vector3D GetTranslation(const Matrix4X3 &m)
{
	return Vector3D(m.tx, m.ty, m.tz);
}

Vector3D GetPosFromParentToLocalMatrix(const Matrix4X3 &m)
{
	return Vector3D(-(m.tx*m.m11 + m.ty*m.m12 + m.tz*m.m13),
				    -(m.tx*m.m21 + m.ty*m.m22 + m.tz*m.m23),
				    -(m.tx*m.m31 + m.ty*m.m32 + m.tz*m.m33));
}
Vector3D GetPosFromLocalToParentMatrix(const Matrix4X3 &m)
{
	return Vector3D(m.tx, m.ty, m.tz);
}