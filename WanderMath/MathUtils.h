//
//  MathUtils.h
//  Cannon
//
//  Created by wangdi on 12-12-6.
//
//

#ifndef Cannon_MathUtils_h
#define Cannon_MathUtils_h

#include "Vector2D.h"
#include "CommonMath.h"

inline double multiply(Point2D p1, Point2D p2, Point2D p0)

{
    
	return((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));
    
}

inline bool IsLineInsert(Point2D ptLine1Begin, Point2D ptLine1End,
						 Point2D ptLine2Begin, Point2D ptLine2End)
{
	return((max(ptLine1Begin.x,ptLine1End.x)>=min(ptLine2Begin.x,ptLine2End.x))&&
           
           (max(ptLine2Begin.x,ptLine2End.x)>=min(ptLine1Begin.x,ptLine1End.x))&&
           (max(ptLine1Begin.y,ptLine1End.y)>=min(ptLine2Begin.y,ptLine2End.y))&&
           (max(ptLine2Begin.y,ptLine2End.y)>=min(ptLine1Begin.y,ptLine1End.y))&&
           (multiply(ptLine2Begin,ptLine1End,ptLine1Begin)*multiply(ptLine1End,ptLine2End,ptLine1Begin)>=0)&&
           (multiply(ptLine1Begin,ptLine2End,ptLine2Begin)*multiply(ptLine2End,ptLine1End,ptLine2Begin)>=0));
}

inline bool IsLineInsertSquare(Point2D ptLineBegin, Point2D ptLineEnd, Point2D ptLeftUp, Point2D ptRightBottom)
{
	if(IsLineInsert(ptLineBegin, ptLineEnd, ptLeftUp, Point2D(ptRightBottom.x, ptLeftUp.y)) ||
	   IsLineInsert(ptLineBegin, ptLineEnd, Point2D(ptRightBottom.x, ptLeftUp.y), ptRightBottom) ||
	   IsLineInsert(ptLineBegin, ptLineEnd, ptRightBottom, Point2D(ptLeftUp.x, ptRightBottom.y)) ||
	   IsLineInsert(ptLineBegin, ptLineEnd, Point2D(ptLeftUp.x, ptRightBottom.y), ptLeftUp)
	   )
	{
		return true;
	}
    
	return false;
}

#endif
