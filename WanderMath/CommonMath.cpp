//////////////////////////////////////////////////////////////////
//
// name: CommonMath.h
// func: 定义通用的数学函数
// date: 2010.10.2	
//
///////////////////////////////////////////////////////////////////

#include "CommonMath.h"
#include <cmath>

using namespace std;



float g_sinTable[361];
float g_cosTable[361];

void BuildSinCosTable()
{
	for (int ang=0; ang<=360; ang++)
	{
		float theta = AngToRad((float)(ang));
        
		g_sinTable[ang] = sin(theta);
		g_cosTable[ang] = cos(theta);
	}
}
//--------------------------------------------------/

float FastSin(float angle)
{
	// 将角度转化到0-359范围之内
    
	angle = fmodf(angle, 360.0f);
    
	if (angle < 0)
	{
		angle += 360.0f;
	}
    
	// 将角度分解为整数部分和小数部分
    
	int angleInt = (int)angle;
	float angleFra = angle - angleInt;
    
	// 采用线性插值原理
    
	return (g_sinTable[angleInt] + angleFra * (g_sinTable[angleInt+1] - g_sinTable[angleInt]));
}
//-----------------------------------------------------------------------------------------/

float FastCos(float angle)
{
	// 原理同FastSin
    
	angle = fmodf(angle, 360.0f);
    
	if (angle < 0)
	{
		angle += 360.0f;
	}
    
	int angleInt = (int)angle;
	float angleFra = angle - angleInt;
    
	return (g_cosTable[angleInt] + angleFra * (g_cosTable[angleInt+1] - g_cosTable[angleInt]));
}

//-------------------------------------------------------------------------------------------------/

int FastDistance2D(int x, int y)
{
	x = abs((float)x);
	y = abs((float)y);
    
	// compute the minimum of x,y
	int mn = (x < y) ? x : y;
    
	// return the distance
	return(x+y-(mn>>1)-(mn>>2)+(mn>>4));
}

//--------------------------------------------------------------------------/

float FastDistance3D(float fx, float fy, float fz)
{
	int temp;  // used for swaping
	int x,y,z; // used for algorithm
    
	// make sure values are all positive
	x = (int)(fabs(fx) * 1024);
	y = (int)(fabs(fy) * 1024);
	z = (int)(fabs(fz) * 1024);
    
	// sort values
	if (y < x) SWAP(x,y,temp);
    
	if (z < y) SWAP(y,z,temp);
    
	if (y < x) SWAP(x,y,temp);
    
	int dist = (z + 11 * (y >> 5) + (x >> 2) );
    
	// compute distance with 8% error
	return((float)(dist >> 10));
}