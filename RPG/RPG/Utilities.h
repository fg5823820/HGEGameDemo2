
#include "StdAfx.h"

void Trace( Pos* pos,const Pos& dst,float spd);

void Rotate(Pos* inPos, Pos* outPos, float angle);


/**
* ����Բ����ײ
* @param roundx Բ�ĺ�����
* @param roundy Բ��������
* @param r	             Բ�뾶
* 
* @param x ��ĺ�����
* @param y ���������
* @return ��ײ����true�����򷵻�false
*/
bool CollidePiontInRound(float roundx, float roundy, float r,
				  float x, float y);

/**
* ������Բ����ײ
*/
bool CollidePiontInEllipse(Pos pt1, Pos pt2, 
						   Pos cter, //��Բ���ĵ�
						   Pos pnt);

