#include "Utilities.h"
#include <hgevector.h>
#include <stdlib.h>
#include <math.h>


void Trace( Pos* pos,const Pos& dst,float spd)
{
	if(!((*pos)==dst))
	{
		hgeVector v( dst.x - pos->x , dst.y - pos->y);
		v.Normalize();
		if(!(abs(dst.x-pos->x) < spd && abs(dst.y-pos->y) < spd))
		{
			pos->x += v.x*spd;
			pos->y += v.y*spd;
		}
		else
		{
			//Trace(pos, dst, spd/2.0f);
			*pos = dst;
		}
	}
}

void Rotate(Pos* inPos, Pos* outPos, float angle)
{	
	float a = cos(angle);
	float b = -sin(angle);
	float c = sin(angle);
	outPos->x = inPos->x*a+inPos->y*c;
	outPos->y = inPos->x*b+inPos->y*a;
}


bool CollidePiontInRound(float roundx, float roundy, float r,
				  float x, float y) 
{
	if (abs(roundx - x) * abs(roundx - x)
		+ abs(roundy - y) * abs(roundy - y) > abs(r) * abs(r))
		return false;
	else
		return true;
}

//pt1 pt2是椭圆所在矩形的两个点 
//cter 椭圆中心点
//pnt  判断点
bool CollidePiontInEllipse(Pos pt1, Pos pt2, Pos cter, Pos pnt)
{
	float   fRX=(pt2.x-pt1.x)/2.f;     
	float   fRY=(pt2.y-pt1.y)/2.f; 
	if(pow(pnt.x-cter.x,2)+pow(pnt.y-cter.y,2)*(fRX/fRY)*(fRX/fRY) <= fRX*fRX) //在椭圆内部
		return true;
	return false;
}