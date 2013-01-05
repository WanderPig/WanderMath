//////////////////////////////////////////////////////////////////
//
// name: Matrix4X3.h
// func: 4X4矩阵的定义
// date: 2010.10.6
//
///////////////////////////////////////////////////////////////////



#ifndef MATRIX4X4_H
#define MATRIX4X4_H


class Matrix4X4
{
public:
    
	// 旋转部分
    
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
    
	// 平移部分
    
	float tx, ty, tz, tw;
};

#endif