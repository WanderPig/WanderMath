//////////////////////////////////////////////////////////////////
//
// name: Matrix4X3.h
// func: 4X3矩阵的定义
// disc: 来源于3D Math Primer for Graphics and Game Development
// date: 2010.9.18	
// ps:   4x3矩阵不同于旋转矩阵，它有更大的通用性，因此不在用
//		 旋转矩阵中的惯性坐标系与物体坐标系来描述，而用目标坐
//		 标系与源坐标系，而且其旋转有一定的方向性，因此需要指明方向
//
///////////////////////////////////////////////////////////////////

#pragma once

class Vector3D;
class EulerAngles;
class Quaternion;
class RotationMatrix;

typedef Vector3D Point3D;
#include <fstream>
using namespace std;

class Matrix4X3
{
public:
    
	// 重置矩阵
    
	Matrix4X3();
    
	void Reset();
    
	void WriteFile(char *fileName)
	{
		ofstream ofs(fileName, ios::app);
		ofs<<m11<<"  "<<m12<<"  "<<m13<<endl;
		ofs<<m21<<"  "<<m22<<"  "<<m23<<endl;
		ofs<<m31<<"  "<<m32<<"  "<<m33<<endl;
		ofs<<tx<<"  "<<ty<<"  "<<tz<<endl;
		ofs.close();
	}
    
	// 直接访问矩阵平移部分函数
    
	void ZeroTranslation();
	void SetTranslation(const Vector3D &v);
	void SetupTranslation(const Vector3D &v);
	void SetRotate(float _m11, float _m12, float _m13,
				   float _m21, float _m22, float _m23,
				   float _m31, float _m32, float _m33);
    
	// 建立一个矩阵进行本地空间和父空间之间的转化
	// 假定矩阵指定的空间可方向在本地空间之内
	// 用欧拉角或者一个旋转矩阵建立
	// 欧拉角用弧度表示
    
	void SetupLocalToParent(const Point3D &pos, const EulerAngles &angles);
	void SetupParentToLocal(const Point3D &pos, const EulerAngles &angles);
    
    
	// 建立一个物体相对于本地坐标轴的转换
    
	void SetupRotate(const EulerAngles &angles);
    
	// 建立一个关于坐标轴旋转的矩阵
    
	void SetupRotate(int axis, float theta);
    
	// 建立一个关于任意轴旋转的矩阵
    
	void SetupRotate(const Vector3D &axis, float theta);
    
	// 用一个四元数建立旋转矩阵
    
	void FromQuaternion(const Quaternion &q);
    
	// 建立一个用于在每个轴上放缩的矩阵
    
	void SetupScale(const Vector3D &s);
    
	// 建立一个用于在任意轴上放缩的矩阵
    
	void SetupScaleAlongAxis(const Vector3D &axis, float t);
    
	// 建立一个剪切矩阵
    
	void SetupShear(int axis, float s, float t);
    
	// 建立一个在一个经过原点的平面上进行投影的矩阵
    
	void SetupProject(const Vector3D &n);
    
	// 建立一个矩阵用于执行与一个坐标系平面平行的平面的镜像
    
	void SetupReflect(int axis, float = 0.0f);
    
	// 建立一个用于执行找到与一个过原点的任意平面的镜像
    
	void SetupReflect(const Vector3D &n);
    
public:
    
	// 旋转部分
    
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
    
	// 平移部分
    
	float tx, ty, tz;
};

// 重载操作符*和*= 用于执行点与矩阵的叉乘以及矩阵之间的叉乘

extern Point3D operator *(const Point3D &p, const Matrix4X3 &m);
extern Matrix4X3 operator *(const Matrix4X3 &m1, const Matrix4X3 &m2);

extern Matrix4X3 operator *(const Matrix4X3 &m, float v);
extern Matrix4X3 operator +(const Matrix4X3 &m1, Matrix4X3 m2);
extern Matrix4X3 operator -(const Matrix4X3 &m1, Matrix4X3 m2);

extern Point3D &operator *=(Point3D &p, const Matrix4X3 &m);
extern Matrix4X3 &operator *=(Matrix4X3 &a, const Matrix4X3 &b);

// 计算矩阵中3X3行列式的值

extern float Determinant(const Matrix4X3 &m);

// 计算矩阵的逆

extern Matrix4X3 Inverse(const Matrix4X3 &m);

// 取出矩阵中的变换部分

extern Vector3D GetTranslation(const Matrix4X3 &m);

// 从矩阵中提取方向向量

extern Vector3D GetPosFromParentToLocalMatrix(const Matrix4X3 &m);
Vector3D GetPosFromLocalToParentMatrix(const Matrix4X3 &m);


