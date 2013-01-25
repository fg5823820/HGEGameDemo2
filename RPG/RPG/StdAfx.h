#pragma once

#include <stdio.h>
#include <math.h>
#include <hge.h>
#include <vector>
//#include <hgecollision.h>


#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	576
#define NONE			-1

#define SCRIPTNAME		"ResScript.txt"		//�ű���
#define GAMEICON		"dust.ico"			//ͼ����
#define LOGNAME			"hgeRPG.log"		//LOG�ļ���
#define TITLE			"RPGTest"			//������

template<class T> void Delete(T& t)
{
	if (t)
	{
		delete t;
		t = 0;
	}
}

struct Pos
{
	Pos():x(0),y(0){}
	Pos(float _x,float _y):x(_x),y(_y){}
	bool operator == (const Pos& pos)const//Լ��
	{
		return (abs(x-pos.x) < 0.1f && abs(y-pos.y) < 0.1f);
	}
	float x;
	float y;
};


