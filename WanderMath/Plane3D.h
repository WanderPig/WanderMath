#ifndef PLANE3D_H
#define PLANE3D_H

#include "Vector3D.h"
class Plane3D
{
public:
	void Init(const Point3D &p, const Vector3D nv, bool isNorm)
	{
		p0 = p;
		v = nv;
		if(isNorm)
		{
			v.Normalize();
		}
	}
    
public:
	Point3D p0;
	Vector3D v;
};

#endif