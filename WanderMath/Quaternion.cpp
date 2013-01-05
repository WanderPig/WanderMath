//////////////////////////////////////////////////////////////////
//
// name: Quaternion.cpp
// func: 利用四元数表示角位移
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.17	
//
///////////////////////////////////////////////////////////////////

#include "Quaternion.h"
#include "CommonMath.h"
#include "Vector3D.h"
#include "EulerAngles.h"

#include <assert.h>

// 初始化全局变量gQuaternionIdentity

const Quaternion gQuaternionIdentity = {1.0f, 0.0f, 0.0f, 0.0f};

/////////////////////////////////////////////////////////////////////
//
// 成员函数
//
/////////////////////////////////////////////////////////////////////

// Quaternion::Zero
//
// 将成员值为零

void Quaternion::Zero()
{
	w = x = y = z = 0.0f;
}

// Quaternion::SetRotateX
// Quaternion::SetRotateY
// Quaternion::SetRotateZ
// Quaternion::SetRotateAxis
//
// 建立一个关于某个轴旋转的四元数

void Quaternion::SetRotateX(float theta)
{
	// 计算角度的一半
    
	float halfTheta = theta * .5f;
    
	// 设置值
    
	w = cos(halfTheta);
	x = sin(halfTheta);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::SetRotateY(float theta)
{
    
	float halfTheta = theta * .5f;
    
	w = cos(halfTheta);
	x = 0.0f;
	y = sin(halfTheta);
	z = 0.0f;
}

void Quaternion::SetRotateZ(float theta)
{
	float halfTheta = theta * .5f;
    
	w = cos(halfTheta);
	x = 0.0f;
	y = 0.0f;
	z = sin(halfTheta);
}

void Quaternion::SetRotateAxis(const Vector3D &axis, float theta)
{
	// 轴必须是标准化的
    
	assert(fabs(GetMag(axis) - 1.0f) < .01f);
    
	// 计算半角以及半角的sin值
    
	float halfTheta = theta * .5f;
	float sinHalfTheta = sin(halfTheta);
    
	// 赋值
    
	w = cos(halfTheta);
	x = axis.x * sinHalfTheta;
	x = axis.y * sinHalfTheta;
	x = axis.z * sinHalfTheta;
}

// Quaternion::SetRotateInertialToObject
// Quaternion::SetRotateObjectToInertial
//
// 用欧拉角建立惯性坐标系与物理坐标系的相互转化（旋转空间）四元数

void Quaternion::SetRotateInertialToObject(const EulerAngles &orientation)
{
	// 计算各半角的sin 和 cos 值 
    
	float sh, sp, sb;
	float ch, cp, cb;
	
	SinCos(sh, ch, orientation.heading * .5f);
	SinCos(sp, cp, orientation.pitch * .5f);
	SinCos(sb, cb, orientation.bank * .5f);
    
	// 赋值
    
	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = -ch*sp*sb + sh*cp*cb;
	z = -sh*sp*cb + ch*cp*sb;
}

void Quaternion::SetRotateObjectToInertial(const EulerAngles &orientation)
{
	// 计算各半角的sin 和 cos 值 
    
	float sh, sp, sb;
	float ch, cp, cb;
	
	SinCos(sh, ch, orientation.heading * .5f);
	SinCos(sp, cp, orientation.pitch * .5f);
	SinCos(sb, cb, orientation.bank * .5f);
    
	// 赋值
    
	w = ch*cp*cb + sh*sp*sb;
	x = -ch*sp*cb - sh*cp*sb;
	y = ch*sp*sb - sh*cp*cb;
	z = sh*sp*cb - ch*cp*sb;
}

// Quaternion::operator *
//
// 完成四元数的叉乘，返回结果

Quaternion Quaternion::operator *(const Quaternion &q) const
{
	Quaternion ret;
    
	ret.w = w*q.w - x*q.x - y*q.y - z*q.z;
	ret.x = w*q.x + x*q.w + z*q.y - y*q.z;
	ret.y = w*q.y + y*q.w + x*q.z - z*q.x;
	ret.z = w*q.z + z*q.w + y*q.x - x*q.y;
    
	return ret;
}

// Quaternion::operator *=
//
// 完成四元数的叉乘及赋值，返回结果，利用已有的叉乘函数

Quaternion Quaternion::operator *=(const Quaternion &q)
{
	*this = (*this) * q;
    
	return *this;
}

// Quaternion::Normalize
//
// 将四元数标准化，即模为1

void Quaternion::Normalize()
{
	float mag = (float)sqrt(w*w + x*x + y*y + z*z);
    
	if(mag > 0.0f)
	{
		//标准化
        
		float OneOverMag = 1.0f / mag;
        
		w *= OneOverMag;
		x *= OneOverMag;
		y *= OneOverMag;
		z *= OneOverMag;
	}
	else
	{
		//在Release阶段只是简单的归零
        
		assert(false);
        
		Zero();
	}
}

// Quaternion::GetRatateAngle
//
// 获取旋转的角度

float Quaternion::GetRatateAngle() const
{
	return (SafeAcos(w) * 2.0f);
}

// Quaternion::GetRAtateAxis
//
// 要获得向量，必须得到sinθ/2 再用x,y,z的值除以它，即得到向量 

Vector3D Quaternion::GetRAtateAxis() const
{
	// 得到sinθ/2 的平方
    
	float sinThetaOver2Sq = 1.0f - w*w;
    
	if (sinThetaOver2Sq < 0.0f)
	{
		// 此时四元数的值不精确，返回一个任意值
        
		return Vector3D(1.0f, 0.0f, 0.0f);
	}
    
	// 得到参数 sinθ/2 的倒数
    
	float para = 1.0f / sqrt(sinThetaOver2Sq);
    
	return Vector3D(x*para, y*para, z*para);
}

/////////////////////////////////////////////////////////////////
//
// 非成员函数
//
/////////////////////////////////////////////////////////////////

// DotProduct
//
// 点积

float DotProduct(const Quaternion &a, const Quaternion &b)
{
	return (a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z);
}

// Slerp
//
// 执行圆弧线性插值

Quaternion Slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
	// 检查 t 是否超过范围
    
	if (t <= 0.0f) return q0;
	if (t >= 1.0f) return q1;
    
	// 计算点积以得到两个四元数表示的夹角的余弦
    
	float cosOmega = DotProduct(q0, q1);
    
	// 如果是负值，则使用-q。 q与-q代表相同的旋转
	// 但是会产生不同的插值
    
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;
    
	if (cosOmega < 0.0f)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}
    
	// 两个四元数应该是单元四元数，因此点积应该小于1
    
	assert(cosOmega < 1.1f);
    
	// 计算插值分数
    
	float k0, k1;
    
	if (cosOmega > 0.9999f)
	{
		// 此时两个四元数非常相近，因此只执行普通线性插值
		// 防止0被除
        
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		// 通过cos值计算sin
        
		float sinOmega = sqrt(1.0f - cosOmega*cosOmega);
        
		// 计算Omega角
        
		float omega = atan2(sinOmega, cosOmega);
        
		// 计算sin的倒数
        
		float oneOverSinOmega = 1.0f / sinOmega;
        
		// 计算插值参数
        
		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}
    
	Quaternion ret;
    
	ret.x = k0*q0.x + k1*q1x;
	ret.y = k0*q0.y + k1*q1y;
	ret.z = k0*q0.z + k1*q1z;
	ret.w = k0*q0.w + k1*q1w;
    
	return ret;
}

// Conjugate
//
// 对四元数进行取反操作

Quaternion Conjugate(const Quaternion &q)
{
	Quaternion ret;
    
	ret.w = q.w;
	ret.x = -q.x;
	ret.y = -q.y;
	ret.z = -q.z;
    
	return ret;
}

// pow
//
// 四元数的指数操作

Quaternion Pow(const Quaternion &q, float exp)
{
	// 检查四元数的值，防止0被除
    
	if (fabs(q.w) > .9999f)
	{
		return q;
	}
    
	// 得到半角的值
    
	float alpha = acos(q.w);
    
	// 得到新的值
    
	float newAlpha = alpha * exp;
    
	// 计算新的w的值
    
	Quaternion ret;
    
	ret.w = cos(newAlpha);
    
	//得到参数 新的sin与原sin的比值，并计算x,y,z
    
	float para = sin(newAlpha) / sin(alpha);
    
	ret.x = para * q.x;
	ret.y = para * q.y;
	ret.z = para * q.z;
    
	return ret;
}