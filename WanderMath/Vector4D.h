//////////////////////////////////////////////////////////////////
//
//	name:	Vector4D.h
//	func:	此头文件用于四维向量的运算
//
///////////////////////////////////////////////////////////////////

#ifndef Vector4D_H
#define Vector4D_H

#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

typedef class Vector4D
{
public:
    
	Vector4D(){}
    
	~Vector4D(){}
    
	Vector4D(const Vector4D &v):x(v.x), y(v.y), z(v.z), w(v.w){}
    
	Vector4D(float nx, float ny, float nz, float nw):x(nx), y(ny), z(nz), w(nw){}
    
	Vector4D &operator = (const Vector4D &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
    
	void Init(float nx, float ny, float nz, float nw)
	{
		x = nx;
		y = ny;
		z = nz;
		w = nw;
	}
    
	bool operator == (const Vector4D &v) const
	{
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}
    
	bool operator != (const Vector4D &v) const
	{
		return !(*this == v);
	}
    
	Vector4D operator - (const Vector4D &v) const
	{
		return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
	}
    
	Vector4D operator + (const Vector4D &v) const
	{
		return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
	}
    
	Vector4D operator * (float a) const
	{
		return Vector4D(a * x, a * y, a * z, a * w);
	}
    
	Vector4D operator / (float a) const
	{
		assert(a != 0);
		float tmp = 1.0f / a;
        
		return Vector4D(x * tmp, y * tmp, z *tmp, w * tmp);
	}
    
	Vector4D &operator += (const Vector4D &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
    
	Vector4D &operator -= (const Vector4D &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
    
	Vector4D &operator *= (float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}
    
	Vector4D &operator /= (float a)
	{
		assert( a != 0);
		float tmp = 1.0f / a;
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}
    
	// 两向量点积
    
	float operator * (const Vector4D &v) const
	{
		return (x*v.x + y*v.y + z*v.z);
	}
    
	
public:
	float x;
	float y;
	float z;
	float w;
}Point4D;



//// 计算两个向量叉乘
//
//inline Vector4D CrossProduct(const Vector4D &v1, const Vector4D &v2)
//{
//	return Vector4D(v1.x*v2.z - v2.y*v1.z,
//				   v1.z*v2.x - v2.z*v1.x,
//				   v1.x*v2.y - v2.x*v1.y,
//				   );
//				   
//}
//
//// 数乘向量
//
//inline Vector4D operator *(float k, Vector4D &v)
//{
//	return Vector4D(k*v.x, k*v.y, k*v.z);
//}
//
//inline float GetDistance(const Point4D &p1, const Point4D &p2)
//{
//	float dx = p2.x - p1.x;
//	float dy = p2.y - p1.y;
//	float dz = p2.z - p1.z;
//	return sqrt(dx*dx + dy*dy + dz*dz);
//}
//
//inline float GetMag(const Vector4D &v)
//{
//	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
//}
//
//// 输出向量
//
//inline ostream &operator << (ostream &ost,const Vector4D &v)
//{
//	ost<<v.x<<" "<<v.y<<" "<<v.z;
//	return ost;
//}



#endif