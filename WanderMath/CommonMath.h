//////////////////////////////////////////////////////////////////
//
// name: CommonMath.h
// func: 声明通用的数学函数和常数
// date: 2010.10.2	
//
///////////////////////////////////////////////////////////////////

#ifndef COMMONMATH_H
#define COMMONMATH_H

///////////////////////////////////////////////////////////////////
//
// 常量
//
///////////////////////////////////////////////////////////////////

#include <cmath>
#include <stdlib.h>
using namespace std;

const float KPI       = 3.14159265f;
const float K2PI      = 2 * KPI;
const float KPIOVER2  = KPI / 2.0f; 
const float K1OVERPI  = 1.0f / KPI;
const float K1OVER2PI = 1.0f / K2PI;
const float FZERO     = 0.0001f;


///////////////////////////////////////////////////////////////////
//
// 全局变量
//
///////////////////////////////////////////////////////////////////

// 游戏开始时用BuildSinCosTable()初始化

extern float g_sinTable[361];
extern float g_cosTable[361];

///////////////////////////////////////////////////////////////////
//
// 宏
//
///////////////////////////////////////////////////////////////////

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 
#endif

#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
#endif

#ifndef SWAP
#define SWAP(a,b,t) {t=a; a=b; b=t;}
#endif




///////////////////////////////////////////////////////////////////
//
// 内联函数
//
///////////////////////////////////////////////////////////////////



inline float AngToRad(float ang)
{
	return ang * KPI / 180.0f;
}

inline float RadToAng(float rad)
{
	return rad * 180.0f / KPI;
}

//将一个角化到-PI到PI之间

inline float WrapPI(float theta)
{
	theta += KPI;
    
	//floor(x) 求不大于X的最大数
    
	theta -= floor(theta * K1OVER2PI) * K2PI;
	theta -= KPI;
	return theta;
}

//安全的求反角函数，可以防止超出边界

inline float SafeAcos(float x)
{
	if (x <= -1.0f)
	{
		return KPI;
	}
    
	if (x > 1.0f)
	{
		return 0.0f;
	}
    
	return acos(x);
}

//同时计算SIN和COS

inline void SinCos(float &outSin, float &outCos, float theta)
{
	outCos = cos(theta);
	outSin = sin(theta);
}

// 返回0-1
inline float RandFloat()
{
    return rand() / (RAND_MAX + 1.0f);
}

// -1到1
inline float RandClamped()
{
    return RandFloat() - RandFloat();
}

///////////////////////////////////////////////////////////////////
//
// 全局函数
//
///////////////////////////////////////////////////////////////////

// 建立sin cos查询表

extern void BuildSinCosTable();

// 快速查询sin,cos值,使用前必须先初始化表

extern float FastSin(float angle);
extern float FastCos(float angle);

// 快速计算2D和3D中点到原点的距离，2D的误差有3.5%，3D有8%
// 此公式推导原理不明白

extern int FastDistance2D(int x, int y);
extern float FastDistance3D(float fx, float fy, float fz);



#endif