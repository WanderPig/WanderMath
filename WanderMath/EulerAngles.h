//////////////////////////////////////////////////////////////////
//
// name:	EulerAngles.h
// func:	利用欧拉角定位方向
// disc:	来源于3D Math Primer for Graphics and Game Development
//
///////////////////////////////////////////////////////////////////

#pragma once

// 声明

class Quaternion;
class Matrix4X3;
class RotationMatrix;

// 欧拉角类

class EulerAngles
{
public:
    
	EulerAngles();
	EulerAngles(float h, float p, float b):heading(h),pitch(p),bank(b){}
	
	void Init(float h, float p, float b)
	{
		heading = h; pitch = p; bank = b;
	}
	
	// 归零
    
	void Zero()
	{
		heading = pitch = bank = 0.0f;
	}
    
	// 将角度标准化 化到-PI到PI
    
	void Canonize();
    
	// 用一个由物体坐标系向惯性坐标系转化的四元数初始化欧拉角
    
	void FromObjectToInertialQuaternion(const Quaternion &q);
    
	// 用一个由惯性坐标系向物体坐标系转化的四元数初始化欧拉角
    
	void FromInertialToObjectQuaternion(const Quaternion &q);
    
	// 用一个由物体坐标系向世界坐标系转化的4X3矩阵初始化欧拉角
    
	void FromObjectToWorldMatrix(const Matrix4X3 &m);
    
	// 用一个由世界坐标系向物体坐标系转化的4X3矩阵初始化欧拉角
    
	void FromWorldToObjectMatrix(const Matrix4X3 &m);
    
	// 用一个旋转矩阵初始化欧拉角
	void FormRotationMatrix(const RotationMatrix &m);
public:
	// 航向
    
	float heading;
    
	// 俯仰
    
	float pitch;
    
	// 左右倾斜	
    
	float bank;
};