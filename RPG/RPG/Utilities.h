
#include "StdAfx.h"

void Trace( Pos* pos,const Pos& dst,float spd);

void Rotate(Pos* inPos, Pos* outPos, float angle);


/**
* 点与圆的碰撞
* @param roundx 圆心横坐标
* @param roundy 圆心纵坐标
* @param r	             圆半径
* 
* @param x 点的横坐标
* @param y 点的纵坐标
* @return 碰撞返回true，否则返回false
*/
bool CollidePiontInRound(float roundx, float roundy, float r,
				  float x, float y);

/**
* 点与椭圆的碰撞
*/
bool CollidePiontInEllipse(Pos pt1, Pos pt2, 
						   Pos cter, //椭圆中心点
						   Pos pnt);

