//////////////////////////////////////////////////////////////////
//
//	name:	Vector3D.h
//	func:	此头文件用于三维向量的运算
//	disc:	来源于3D Math Primer for Graphics and Game Development
//
///////////////////////////////////////////////////////////////////

#ifndef Vector3D_H
#define Vector3D_H


#include <cassert>
#include <cmath>
#include <iostream>
#include "CommonMath.h"

using namespace std;

typedef class Vector3D
{
public:
	Vector3D()
	{
        
	}
    
	~Vector3D()
	{
        
	}
    
	Vector3D(const Vector3D &v):x(v.x), y(v.y), z(v.z){}
    
	Vector3D(float nx, float ny, float nz):x(nx), y(ny), z(nz){}
    
	Vector3D &operator = (const Vector3D &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
    
	void Init(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}
	void Normalize()
	{
		float magOver1 = 1.0f / sqrt(x*x + y*y + z*z);
        
		x *= magOver1;
		y *= magOver1;
		z *= magOver1;
	}
    
	// 快速计算该点到原点的距离
    
	float FastDistance()
	{
		return FastDistance3D(x, y, z);
	}
	//  重载操作符
    
	bool operator == (const Vector3D &v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}
    
	bool operator != (const Vector3D &v) const
	{
		return !(*this == v);
	}
    
	Vector3D operator - (const Vector3D &v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
    
	Vector3D operator + (const Vector3D &v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
    
	Vector3D operator * (float a) const
	{
		return Vector3D(a * x, a * y, a * z);
	}
    
	Vector3D operator / (float a) const
	{
		assert(a != 0);
		float tmp = 1.0f / a;
        
		return Vector3D(x * tmp, y * tmp, z *tmp);
	}
    
	Vector3D &operator += (const Vector3D &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
    
	Vector3D &operator -= (const Vector3D &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
    
	Vector3D &operator *= (float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}
    
	Vector3D &operator /= (float a)
	{
		assert( a != 0);
		float tmp = 1.0f / a;
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}
    
	// 两向量点积
    
	float operator * (const Vector3D &v) const
	{
		return (x*v.x + y*v.y + z*v.z);
	}
    
	
public:
	float x;
	float y;
	float z;
}Point3D, *Vector3DPtr, *Point3DPtr;


// 计算两个向量叉乘

inline Vector3D CrossProduct(const Vector3D &v1, const Vector3D &v2)
{
	return Vector3D(v1.y*v2.z - v2.y*v1.z,
				    v1.z*v2.x - v2.z*v1.x,
				    v1.x*v2.y - v2.x*v1.y);
    
}

// 数乘向量

inline Vector3D operator *(float k, Vector3D &v)
{
	return Vector3D(k*v.x, k*v.y, k*v.z);
}

inline float GetDistance(const Point3D &p1, const Point3D &p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	float dz = p2.z - p1.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

inline float GetMag(const Vector3D &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// 输出向量

inline ostream &operator << (ostream &ost,const Vector3D &v)
{
	ost<<v.x<<" "<<v.y<<" "<<v.z;
	return ost;
}

#endif