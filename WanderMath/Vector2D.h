//////////////////////////////////////////////////////////////////
//
//	Vector2D.h
//
//	此头文件用于二维向量的运算
//
///////////////////////////////////////////////////////////////////

#ifndef Wander_Vector2D_h
#define Wander_Vector2D_h
#include "CommonMath.h"

typedef class Vector2D
{
public:
	Vector2D()
        : x(0)
        , y(0)
	{
	}
    
	~Vector2D()
	{
        
	}
    
	Vector2D(const Vector2D &v):x(v.x), y(v.y){}
    
	Vector2D(float nx, float ny):x(nx), y(ny){}
    
	Vector2D &operator = (const Vector2D &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
    
	void Init(float nx, float ny)
	{
		x = nx;
		y = ny;
	}
    
    void Zero()
    {
        x = y = 0;
    }
    
	void Normalize()
	{
        float down = sqrt(x*x + y*y);
        
        if(down == 0)
        {
            x = y = 0;
            return;
        }
		float magOver1 = 1.0f / down;
        
		x *= magOver1;
		y *= magOver1;
	}
    
    float Length() const 
    {
        return sqrt(x*x +y*y);
    }
    
    float LengthSq() const 
    {
        return x*x + y*y;
    }
    
    void Truncate(float max)
    {
        if(this->Length() > max)
        {
            this->Normalize();
            *this *= max;
        }
    }
    
    inline float ToRad() const
    {
        if(fabs(x) < FZERO)
        {
            if(y > 0)
            {
                return 1.570796f;
            }
            else
            {
                return -1.570796f;
            }
        }
        
        float angle = atanf(y/x);
        
        if(x < 0)
        {
            angle += 3.141592f;
        }
    
        return angle;
    }
    
    inline float ToAngle() const
    {
        return ToRad() * 180 / 3.141592f;
    }
	// 快速计算该点到原点的距离
    
	float FastDistance() const 
	{
		return FastDistance2D(x, y);
	}
	//  重载操作符
    
	bool operator == (const Vector2D &v) const
	{
		return (x == v.x && y == v.y);
	}
    
	bool operator != (const Vector2D &v) const
	{
		return !(*this == v);
	}
    
	Vector2D operator - (const Vector2D &v) const
	{
		return Vector2D(x - v.x, y - v.y);
	}
    
	Vector2D operator + (const Vector2D &v) const
	{
		return Vector2D(x + v.x, y + v.y);
	}
    
	Vector2D operator * (float a) const
	{
		return Vector2D(a * x, a * y);
	}
    
	Vector2D operator / (float a) const
	{
		assert(a != 0);
		float tmp = 1.0f / a;
        
		return Vector2D(x * tmp, y * tmp);
	}
    
	Vector2D &operator += (const Vector2D &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
    
	Vector2D &operator -= (const Vector2D &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
    
	Vector2D &operator *= (float a)
	{
		x *= a;
		y *= a;
		return *this;
	}
    
	Vector2D &operator /= (float a)
	{
		assert( a != 0);
		float tmp = 1.0f / a;
		x *= tmp;
		y *= tmp;
		return *this;
	}
    
	// 两向量点积
    
	float operator * (const Vector2D &v) const
	{
		return (x*v.x + y*v.y);
	}
    
	
public:
	float x;
	float y;
}Point2D, *Vector2DPtr, *Point2DPtr;

// 数乘向量

inline Vector2D operator *(float k, Vector2D &v)
{
	return Vector2D(k*v.x, k*v.y);
}

inline float Vec2Distance(const Point2D &p1, const Point2D &p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	return sqrt(dx*dx + dy*dy);
}

inline float Vec2DistanceSq(const Point2D &p1, const Point2D &p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	return dx*dx + dy*dy;
}


inline float Vec2Magnitute(const Vector2D &v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

inline Vector2D Vec2Perp(const Vector2D &v)
{
    return Vector2D(-v.y, v.x);
}

inline Vector2D Vec2Normalize(const Vector2D &v)
{
    float sq = sqrt(v.x*v.x + v.y*v.y);
    if(fabs(sq) < FZERO)
    {
        return v;
    }
    
    float magOver1 = 1.0f / sq;
    
    return Vector2D(v.x * magOver1, v.y * magOver1);
}

// 输出向量

inline ostream &operator << (ostream &ost,const Vector2D &v)
{
	ost<<v.x<<" "<<v.y;
	return ost;
    
}

#endif
